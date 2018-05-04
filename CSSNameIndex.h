/**************************************
Author:林?
Date:2017/12/19
Update:2018/1/3
Description:专题索引类，利用字典树（Trie）实现属性到图的查询
***************************************/
#ifndef CSSNAMEINDEX_H
#define CSSNAMEINDEX_H

#include "CSSIndex.h"
#include "CSSNameIndexNode.h"

class CSSNameIndex: public CSSIndex
{
public:
    CSSNameIndex();
    ~CSSNameIndex();

    CSSCity* cityResult;//搜索结果

    /* 创建字典树
    citySet:省会城市数据集*/
    void CreateTrie(list<CSSCity* > citySet);

    /* 专题查询
    str:城市拼音首字母*/
    bool Search(const char* str);

private: 
    CSSNameIndexNode* pRoot;//根节点

    /* 插入
    city:待插入城市指针*/
    void Insert(CSSCity* city);

    /* 销毁
    pRoot:根节点*/
    void Destory(CSSNameIndexNode* pRoot);
};

#endif // CSSNAMEINDEX_H
