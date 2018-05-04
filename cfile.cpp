#include "CFile.h"

CFile::CFile(const char* readFilePath1,const char* readFilePath2,
             const char* readFilePath3)
{
    this->readFilePath1 = readFilePath1;
    this->readFilePath2 = readFilePath2;
    this->readFilePath3 = readFilePath3;
    this->map = new CHMap();
}

CFile::~CFile()
{
    //析构成员变量citySet
    for(list<CSSCity* >::iterator iter = citySet.begin();iter != citySet.end();iter++)
    {
        if((*iter) != 0x00)
        {
            delete *iter;
            *iter = 0x00;
        }
    }
    citySet.clear();

    //析构成员变量map
    if(map != 0x00)
    {
        delete map;
        map = 0x00;
    }
}


/// <summary>
/// 读取图形绘制文件
/// </summary>
void CFile::FileOpenDat()
{
    int x;
    string str;
    ifstream file(readFilePath1);//打开文件
    if(!file)
    {
        cout << false << endl;
        exit(0); //打开文件失败时退出
    }

    //读取MBR
    getline(file,str);
    const char* temp = str.c_str();
    sscanf(temp,"%d,%d",&map->minx,&map->maxy);
    getline(file,str);
    temp = str.c_str();
    sscanf(temp,"%d,%d",&map->maxx,&map->miny);

    //读取层数
    getline(file,str);
    temp = str.c_str();
    sscanf(temp,"%d",&map->n);

    //读取绘制目标
    while(getline(file,str))
    {
        getline(file,str);
        CHLayer *layer = new CHLayer();
        layer->name = str;
        getline(file,str);
        temp = str.c_str();
        sscanf(temp,"%d",&x);
        for(int i = 0;i < x; i++)
        {
            CHPoint point;
            getline(file,str);
            temp = str.c_str();

            if(strcmp(temp,"1") == 0)//目标类型为1（线）
            {
                CHObject* obj = new CHPolyline();
                sscanf(temp,"%d",&((CHPolygon *)obj)->type);
                while(point.x != -99999 && point.y != -99999)
                {
                    getline(file,str);
                    temp = str.c_str();
                    sscanf(temp,"%d,%d",&point.x,&point.y);
                    if(point.x != -99999 && point.y != -99999)
                        obj->AddPoint(point);
                }
                layer->AddObject(obj);
            }
            else if(strcmp(temp,"2") == 0)//目标类型为2（面）
            {
                CHObject *obj = new CHPolygon();
                sscanf(temp,"%d",&((CHPolygon *)obj)->type);
                while(point.x != -99999 && point.y != -99999)
                {
                    getline(file,str);
                    temp = str.c_str();
                    sscanf(temp,"%d,%d",&point.x,&point.y);
                    if(point.x != -99999 && point.y != -99999)
                        obj->AddPoint(point);
                }
                layer->AddObject(obj);
            }
            else
            {
                cout << "Fail to identify object type!" << endl;
                exit(1);
            }
        }
        map->AddLayer(layer);
    }
    file.close();
}


/// <summary>
/// 读取绘制信息文件
/// </summary>
void CFile::FileOpenOpt()
{
    int x;
    string str;
    ifstream file(readFilePath2);               //打开文件
    if(!file)
    {
        cout << false << endl;
        exit(0);                       //打开文件失败时退出
    }

    //读取层数
    getline(file,str);
    const char* temp = str.c_str();
    sscanf(temp,"%d",&x);

    for(int i = 0; i < x; i++)
    {
        getline(file,str);
        f f0;
        color c;
        f0.name = str;
        getline(file,str);
        temp = str.c_str();
        sscanf(temp,"%d",&f0.line);

        if(f0.line == 0)//线型为0（空线）
        {
            getline(file,str);
            temp = str.c_str();
            sscanf(temp,"%d",&f0.fill);
            if(f0.fill != 1)
            {
                cout << "Fail to identify filling type!" << endl;
                exit(1);
            }
            getline(file,str);
            temp = str.c_str();
            sscanf(temp,"%d,%d,%d",&c.r,&c.g,&c.b);
            f0.color2 = c;
        }
        else if(f0.line == 1)//线型为1
        {
            getline(file,str);
            temp = str.c_str();
            sscanf(temp,"%f",&f0.width);
            getline(file,str);
            temp = str.c_str();
            sscanf(temp,"%d,%d,%d",&c.r,&c.g,&c.b);
            f0.color1 = c;
            getline(file,str);
            temp = str.c_str();
            sscanf(temp,"%d",&f0.fill);
            if(f0.fill == 1)
            {
                getline(file,str);
                temp = str.c_str();
                sscanf(temp,"%d,%d,%d",&c.r,&c.g,&c.b);
                f0.color2 = c;
            }
        }
        else
        {
            cout << "Fail to identify line type!" << endl;
            exit(1);
        }
        map->fills.push_back(f0);
    }
    file.close();
}


/// <summary>
/// 获取省会城市数据集
/// </summary>
void CFile::GetCitySet()
{
    ReadTxtFile();
    GetPinYin();
}


/// <summary>
/// 读取省会城市文件
/// </summary>
void CFile::ReadTxtFile()
{
    ifstream in(readFilePath3);
    if(!in)
    {
        fputs("Can't open the file!",stderr);
        return ;
    }

    CSSCity* city = NULL;
    string str;
    int size;

    while(getline(in, str)) //每次把一个记录读到str1中
    {
        city = new CSSCity();
        size = str.size();
        StringToRecord(city,str,size);
        citySet.push_back(city);
    }
    in.close();
}


/// <summary>
/// 将字符串转换为单条记录
/// </summary>
/// <param name="city">转换后的单条城市信息记录</returns>
/// <param name="str">待转换字符串</param>
/// <param name="size">字符串长度</param>
void CFile::StringToRecord(CSSCity* city,string str,int size)
{
    string name,s;
    int x,y;
    int i;
    int pos,count;//字符串第一个字母的位置和字符串长度

    //读取name
    i=0;
    pos = 0;
    count = 0;
    while(str.at(i)!= ' ')
    {
       count++;
       i++;
    }
    name.assign(str, pos, count);
    city->name = name;

    //读取geoPt.x
    i++;
    pos += count + 1;
    count = 0;
    while(str.at(i)!=' ')
    {
       count++;
       i++;
    }
    s.assign(str, pos, count);
    x = atoi(s.c_str());
    city->geoPt.x = x;

    //读取geoPt.y
    i++;
    pos += count + 1;
    count = size - pos;
    s.assign(str, pos, count);
    y = atoi(s.c_str());
    city->geoPt.y = y;
}


/// <summary>
/// 将省会城市数据集和用户输入的城市名转换为城市拼音首字母缩写
/// </summary>
void CFile::GetPinYin()
{
    CSSCity* city;
    for(list<CSSCity* >::iterator iter = citySet.begin(); iter != citySet.end();iter++)
    {
        city = (*iter);
        city->pinyin = GetFirstLetters(city->name);
    }
}


/// <summary>
/// 根据汉字区域码获取拼音声母
/// </summary>
char Convert(wchar_t n)
{
    CONVERT(0xB0A1, 0xB0C4, n, 'a');
    CONVERT(0XB0C5, 0XB2C0, n, 'b');
    CONVERT(0xB2C1, 0xB4ED, n, 'c');
    CONVERT(0xB4EE, 0xB6E9, n, 'd');
    CONVERT(0xB6EA, 0xB7A1, n, 'e');
    CONVERT(0xB7A2, 0xB8c0, n, 'f');
    CONVERT(0xB8C1, 0xB9FD, n, 'g');
    CONVERT(0xB9FE, 0xBBF6, n, 'h');
    CONVERT(0xBBF7, 0xBFA5, n, 'j');
    CONVERT(0xBFA6, 0xC0AB, n, 'k');
    CONVERT(0xC0AC, 0xC2E7, n, 'l');
    CONVERT(0xC2E8, 0xC4C2, n, 'm');
    CONVERT(0xC4C3, 0xC5B5, n, 'n');
    CONVERT(0xC5B6, 0xC5BD, n, 'o');
    CONVERT(0xC5BE, 0xC6D9, n, 'p');
    CONVERT(0xC6DA, 0xC8BA, n, 'q');
    CONVERT(0xC8BB, 0xC8F5, n, 'r');
    CONVERT(0xC8F6, 0xCBF0, n, 's');
    CONVERT(0xCBFA, 0xCDD9, n, 't');
    CONVERT(0xCDDA, 0xCEF3, n, 'w');
    CONVERT(0xCEF4, 0xD188, n, 'x');
    CONVERT(0xD1B9, 0xD4D0, n, 'y');
    CONVERT(0xD4D1, 0xD7F9, n, 'z');
    return '\0';
}


/// <summary>
/// 提取单个汉字词的拼音首字母缩写
/// </summary>
/// <param name="name">待转换城市名称</param>
/// <returns>城市名称拼音首字母缩写</returns>
string CFile::GetFirstLetters(string name)
{
    string pinyin;
    wchar_t wchr = 0;

    for (unsigned int i = 0 , j = 0; i < name.length() / 2 ; i++)
    {
        wchr = (name[j++] & 0xff) << 8; // 高字节
        wchr |= (name[j++] & 0xff);        // 低字节
        pinyin.append(1,Convert(wchr));
    }
    return pinyin;
}
