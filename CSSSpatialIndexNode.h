/**************************************
Author:林?
Date:2017/12/20
Update:2018/1/3
Description:四叉树结点类
***************************************/
#ifndef CSSSPATIALINDEXNODE_H
#define CSSSPATIALINDEXNODE_H

#include "CSSCity.h"

class CSSSpatialIndexNode
{
public:
    CSSSpatialIndexNode();
    ~CSSSpatialIndexNode();

    CHPoint pos;//节点地理坐标
    CSSCity* city;//相应的城市信息指针

    /* 指向四个象限的指针 */
    CSSSpatialIndexNode* NW;
    CSSSpatialIndexNode* NE;
    CSSSpatialIndexNode* SE;
    CSSSpatialIndexNode* SW;

    int LN;
    int LS;
    int LE;
    int LW;
};

#endif // CSSSPATIALINDEXNODE_H
