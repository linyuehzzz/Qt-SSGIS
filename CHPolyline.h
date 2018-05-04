/**************************************
Author:胡超
Date:2017/12/23
Update:2018/1/6
Description:数据类，存储线数据
***************************************/
#ifndef CHPOLYLINE_H
#define CHPOLYLINE_H

#include "CHObject.h"

class CHPolyline: public CHObject
{
public:
    CHPolyline();
    ~CHPolyline();

    vector<CHPoint > points;//折线坐标点集

    /* 添加点坐标
    pt:待添加点坐标 */
    void AddPoint(CHPoint pt);

    /* 折线绘制
    f0:目标绘制信息
    maxx,maxy,minx,miny:制图区域MBR */
    void Draw(f f0,int maxx,int maxy,int minx,int miny);
};

#endif // CHPOLYLINE_H
