/**************************************
Author:林?
Date:2017/12/19
Update:2018/1/3
Description:字典树结点类
***************************************/
#ifndef CSSNAMEINDEXNODE_H
#define CSSNAMEINDEXNODE_H

#include "CSSCity.h"

const int MaxBranchNum = 26;//代表26个字母；如果区分大小写，可以扩展到52

class CSSNameIndexNode
{
public:
    CSSNameIndexNode();
    ~CSSNameIndexNode();

    char* word; //节点表示的城市拼音首字母（单词）
    CSSCity* city;//相应的城市信息指针
    CSSNameIndexNode* nextBranch[MaxBranchNum];//指向26个字符节点的指针
};

#endif // CSSNAMEINDEXNODE_H
