/**************************************
Author:胡超
Date:2017/12/23
Update:2018/1/6
Description:图层类，装载对象类
***************************************/
#ifndef CHLAYER_H
#define CHLAYER_H

#include "CHObject.h"

class CHLayer
{
public:
    CHLayer();
    ~CHLayer();

    string name;//层名
    vector<CHObject* > objects;//层内目标集

    /* 添加目标
    layer:待添加目标 */
    void AddObject(CHObject* obj);

    /* 图层绘制
    f0:图层绘制信息
    maxx,maxy,minx,miny:制图区域MBR */
    void Draw(f f0,int maxx,int maxy,int minx,int miny);

};

#endif // CHLAYER_H
