#include "CSSNameIndex.h"

CSSNameIndex::CSSNameIndex()
{
    pRoot = new CSSNameIndexNode();//注意字典树的根不存放字符
}


CSSNameIndex::~CSSNameIndex()
{
    Destory(pRoot);
}


/// <summary>
/// 创建字典树
/// </summary>
/// <param name="citySet">省会城市数据集</param>
void CSSNameIndex::CreateTrie(list<CSSCity* > citySet)
{
    CSSCity* city;
    for(list<CSSCity* >::iterator iter = citySet.begin(); iter != citySet.end();iter++)
    {
        city = (*iter);
        Insert(city);
    }
}


/// <summary>
/// 插入一条城市记录
/// </summary>
/// <param name="city">待插入城市记录</param>
void CSSNameIndex::Insert(CSSCity* city)
{
    string pinyin = city->pinyin;
    transform(pinyin.begin(),pinyin.end(),pinyin.begin(),tolower);//大写变小写
    const char* str = pinyin.c_str();

    int index;
    CSSNameIndexNode* pLoc = pRoot;
    for (int i = 0;str[i];i++)
    {
        index = str[i] - 'a';//如果区分大小写，可以扩展

        if(index < 0 || index > MaxBranchNum)//不执行插入
        {
            cout << "Fail to identify a word.\n";
            exit(0);
        }

        if (0x00 == pLoc->nextBranch[index])//该单词的前缀不存在，要生成该结点
        {
            pLoc->nextBranch[index] = new CSSNameIndexNode();
        }
        pLoc = pLoc->nextBranch[index];
    }
    if (0x00 != pLoc->word)//单词已经出现过
    {
        exit(0);
    }
    else    //单词没有出现过，应该插入单词
    {
        pLoc->word = new char[strlen(str) + 1];
        strcpy(pLoc->word,str);
        pLoc->city = city;
    }
}


/// <summary>
/// 查找一条城市记录
/// </summary>
/// <param name="str">待查询城市名</param>
/// <returns>城市屏幕坐标</returns>
bool CSSNameIndex::Search(const char* str)
{
    int index = -1;;
    CSSNameIndexNode* pLoc = pRoot;
    while(pLoc && *str)
    {
        index = *str - 'a';//如果区分大小写，可以扩展

        if(index < 0 || index > MaxBranchNum)//不是一个单词，不执行插入
        {
            cout << "Fail to identify a word.\n";
            exit(0);
        }

        pLoc = pLoc->nextBranch[index];
        str++;
    }
    if (pLoc && pLoc->word)//条件成立，找到该单词
    {
        cityResult = pLoc->city;
        return true;
    }
    else
    {
        cout << "Cannot find this city.\n";
        return false;
    }
}


/// <summary>
/// 销毁Trie树
/// </summary>根节点</param>
void CSSNameIndex::Destory(CSSNameIndexNode* pRoot)
{
    if (0x00 == pRoot)
    {
        return;
    }
    for (int i = 0;i < MaxBranchNum;i++)
    {
        Destory(pRoot->nextBranch[i]);
    }
    if(pRoot->word != 0x00)
    {
        delete[] pRoot->word;
        pRoot->word = 0x00;
    }
    delete pRoot;//销毁结点
    pRoot = 0x00;
}
