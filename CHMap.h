/**************************************
Author:胡超
Date:2017/12/23
Update:2018/1/6
Description:地图类，装载图层类
***************************************/
#ifndef CHMAP_H
#define CHMAP_H

#include "CHLayer.h"

class CHMap
{
public:
    CHMap();
    ~CHMap();

    int maxx,maxy,minx,miny;//MBR
    int n;//层数
    vector<f>fills;//绘制信息
    vector<CHLayer* > layers;//图层集

    /* 添加图层
    layer:待添加图层 */
    void AddLayer(CHLayer* layer);

    /* 地图绘制
    maxx,maxy,minx,miny:制图区域MBR */
    void Draw(int maxx,int maxy,int minx,int miny);
};

#endif // CHMAP_H
