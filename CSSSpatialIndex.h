/**************************************
Author:林?
Date:2017/12/20
Update:2018/1/3
Description:空间索引类，利用四叉树（QuadTree）实现图到属性的查询
***************************************/
#ifndef CSSSPATIALINDEX_H
#define CSSSPATIALINDEX_H

#include "CSSIndex.h"
#include "CSSSpatialIndexNode.h"
#include <queue>

class CSSSpatialIndex: public CSSIndex
{
public:
    CSSSpatialIndex();
    ~CSSSpatialIndex();

    /* 创建四叉树
    citySet:省会城市数据集 */
    void CreateQuadTree(list<CSSCity* > citySet);

    /* 查找一条城市记录
    pt:屏幕坐标 */
    bool Search(CHPoint pt,CSSCity* city);

    /* 不精确查找一条城市记录
    pt:屏幕坐标
    r:缓冲区半径 */
    bool CheckCircle(CHPoint pt, int r);

    CSSCity* cityResult;

private:
    CSSSpatialIndexNode* root;//根节点
    CSSSpatialIndexNode* target;//目标点

    /* 插入
    city:待插入城市指针 */
    void Insert(CSSCity* city);

    /* 生成节点
    pos:待插入节点屏幕坐标 */
    CSSSpatialIndexNode* MakeNode(CHPoint pos);

    /* 比较点坐标是否相等
    temp:根节点
    target:目标点 */
    bool IsEqualCoordinates(CSSSpatialIndexNode* temp, CSSSpatialIndexNode* target);

    /* 判断目标点所处象限
    temp:根节点
    target:目标点 */
    CSSSpatialIndexNode* GetQuadrant(CSSSpatialIndexNode* temp, CSSSpatialIndexNode* target);

    /* 将目标点插入相应叶子节点中
    temp:根节点
    target:目标点 */
    void InsertPointInFinalQuadrant(CSSSpatialIndexNode* temp, CSSSpatialIndexNode* target);

    /* 目标点是否落于缓冲区内
    pt:屏幕坐标
    r:缓冲区半径
    target:目标点 */
    bool IsInCircle(CHPoint pt, int r, CSSSpatialIndexNode* target);

    /* 距离计算 */
    int Dist(int x1, int y1, int x2, int y2);

};

#endif // CSSSPATIALINDEX_H
