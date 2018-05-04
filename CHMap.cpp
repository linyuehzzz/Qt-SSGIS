#include "CHMap.h"

CHMap::CHMap()
{

}


CHMap::~CHMap()
{
    //析构成员变量layers
    for(vector<CHLayer* >::iterator iter = layers.begin();iter != layers.end();iter++)
    {
        if((*iter) != 0x00)
        {
            delete *iter;
            *iter = 0x00;
        }
    }
    layers.clear();
}


/// <summary>
/// 添加图层
/// </summary>
/// <param name="layer">待添加图层</returns>
void CHMap::AddLayer(CHLayer* layer)
{
    layers.push_back(layer);
}


/// <summary>
/// 地图绘制
/// </summary>
/// <param name="maxx,maxy,minx,miny">制图区域MBR</returns>
void CHMap::Draw(int maxx,int maxy,int minx,int miny)
{
    for(int i = 0; i < n; i++)
    {
        f f0;
        CHLayer *layer = layers.at(i);
        string name0 = layer->name;
        for(int j = 0; j < fills.size(); j++)
        {
            f0 = fills.at(j);
            if(f0.name == name0)
                break;
        }
        layer->Draw(f0,maxx,maxy,minx,miny);
    }
}

