#include "CHLayer.h"

CHLayer::CHLayer()
{

}

CHLayer::~CHLayer()
{
    //析构成员变量objects
    for(vector<CHObject* >::iterator iter = objects.begin();iter != objects.end();iter++)
    {
        if((*iter) != 0x00)
        {
            delete *iter;
            *iter = 0x00;
        }
    }
    objects.clear();
}


/// <summary>
/// 添加目标
/// </summary>
/// <param name="obj">待添加目标</returns>
void CHLayer::AddObject(CHObject* obj)
{
    objects.push_back(obj);
}


/// <summary>
/// 图层绘制
/// </summary>
/// <param name="f0">图层绘制信息</returns>
/// <param name="maxx,maxy,minx,miny">制图区域MBR</returns>
void CHLayer::Draw(f f0,int maxx,int maxy,int minx,int miny)
{
    for(unsigned int i = 0;i < objects.size(); i++)
    {
         CHObject* obj = objects.at(i);
         obj->Draw(f0,maxx,maxy,minx,miny);
    }
}




