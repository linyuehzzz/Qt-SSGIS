#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent),ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    string text = "搜索";
    string holderText = GB2312ToUTF_8(text.c_str(),text.length());
    ui->lineEdit->setPlaceholderText(QString::fromStdString(holderText));
    ui->label->setVisible(false);

    nidx = new CSSNameIndex();
    nidx->CreateTrie(ui->myGLWidget->file->citySet);

    sidx = new CSSSpatialIndex();
    sidx->CreateQuadTree(ui->myGLWidget->file->citySet);
}


MainWindow::~MainWindow()
{
    delete ui;

    if(nidx != 0x00)
    {
        delete nidx;
        nidx = 0x00;
    }

    if(sidx != 0x00)
    {
        delete sidx;
        sidx = 0x00;
    }
}


/// <summary>
/// 单击搜索按钮，执行属性到图的查询操作
/// </summary>
void MainWindow::on_pushButton_clicked()
{
    QString str = ui->lineEdit->text();
    QByteArray ba = str.toLocal8Bit();
    char* ch = ba.data();
    ui->myGLWidget->file->strPinyin = ui->myGLWidget->file->GetFirstLetters(ch);
    if(nidx->Search((ui->myGLWidget->file->strPinyin.c_str())))
    {
        CHPoint geoPt = nidx->cityResult->geoPt;
        int width = ui->myGLWidget->file->map->maxx - ui->myGLWidget->file->map->minx;
        int height = ui->myGLWidget->file->map->maxy - ui->myGLWidget->file->map->miny;
        int wcWidth = ui->myGLWidget->width();
        int wcHeight = ui->myGLWidget->height();
        int x,y;
        x = (double)(geoPt.x - ui->myGLWidget->file->map->minx)/width * wcWidth;
        y = (double)(ui->myGLWidget->file->map->maxy - geoPt.y)/height * wcHeight;

        ui->label->setGeometry((x-16),(y-32),32,32);
        ui->label->setVisible(true);
    }
}


/// <summary>
/// 单击图上点，执行图到属性的查询操作
/// </summary>
void MainWindow::mousePressEvent(QMouseEvent *e)
{
    CHPoint pt;
    e->globalX();
    pt.x = e->x();
    pt.y = e->y();
    int width = ui->myGLWidget->file->map->maxx - ui->myGLWidget->file->map->minx;
    int height = ui->myGLWidget->file->map->maxy - ui->myGLWidget->file->map->miny;
    int wcWidth = ui->myGLWidget->width();
    int wcHeight = ui->myGLWidget->height();
    CHPoint geoPt;
    int a =(int)((double)pt.x / wcWidth * width);
    int b =(int)((double)pt.y / wcHeight * height);
    geoPt.x = a + ui->myGLWidget->file->map->minx;
    geoPt.y = ui->myGLWidget->file->map->maxy - b;

    int r = 100;
    if (sidx->CheckCircle(geoPt, r))
    {
        string pOut = GB2312ToUTF_8(sidx->cityResult->name.c_str(),sidx->cityResult->name.length());
        QToolTip::showText(e->globalPos(), QString::fromStdString(pOut));
    }
}


/// <summary>
/// 字符转码，用于中文正确显示
/// </summary>
/// <param name="pText">待转换字符串</param>
/// <param name="pLen">字符串长度</param>
/// <returns>转换后字符串</returns>
string MainWindow::GB2312ToUTF_8(const char *pText, int pLen)
{
    string pOut;
    char buf[4];
    int nLength = pLen * 3;
    char* rst = new char[nLength + 1];

    memset(buf, 0, 4);
    memset(rst, 0, nLength);

    int i = 0;
    int j = 0;
    while (i < pLen)
    {
        //如果是英文直接复制就可以
        if (*(pText + i) >= 0)
        {
            rst[j++] = pText[i++];
        }
        else
        {
            wchar_t pbuffer;
            Gb2312ToUnicode(&pbuffer, pText + i);

            UnicodeToUTF_8(buf, &pbuffer);

            unsigned short int tmp = 0;
            tmp = rst[j] = buf[0];
            tmp = rst[j + 1] = buf[1];
            tmp = rst[j + 2] = buf[2];

            j += 3;
            i += 2;
        }
    }
    rst[j] = '\0';

    //返回结果
    pOut = rst;
    delete[] rst;
    rst = 0x00;
    return pOut;
}


/// <summary>
/// Gb2312转为Unicode
/// </summary>
void MainWindow::Gb2312ToUnicode(wchar_t* pOut, const char *gbBuffer)
{
    MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, gbBuffer, 2, pOut, 1);
    return;
}


/// <summary>
/// Unicode转为UTF-8
/// </summary>
void MainWindow::UnicodeToUTF_8(char* pOut, wchar_t* pText)
{
    // 注意 WCHAR高低字的顺序,低字节在前，高字节在后
    char* pchar = (char *)pText;

    pOut[0] = (0xE0 | ((pchar[1] & 0xF0) >> 4));
    pOut[1] = (0x80 | ((pchar[1] & 0x0F) << 2)) + ((pchar[0] & 0xC0) >> 6);
    pOut[2] = (0x80 | (pchar[0] & 0x3F));

    return;
}

