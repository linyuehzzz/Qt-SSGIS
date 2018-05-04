#include "CHPolygon.h"

CHPolygon::CHPolygon()
{

}

CHPolygon::~CHPolygon()
{

}


/// <summary>
/// 添加点坐标
/// </summary>
/// <param name="layer">待添加点坐标</returns>
void CHPolygon::AddPoint(CHPoint pt)
{
    points.push_back(pt);
}


/// <summary>
/// 多边形绘制
/// </summary>
/// <param name="f0">目标绘制信息</returns>
/// <param name="maxx,maxy,minx,miny">制图区域MBR</returns>
void CHPolygon::Draw(f f0,int maxx,int maxy,int minx,int miny)
{
    if(f0.line == 1)
    {
        GLfloat r = ((float)f0.color1.r)/255;
        GLfloat g = ((float)f0.color1.g)/255;
        GLfloat b = ((float)f0.color1.b)/255;
        glColor3f(r,g,b);
        glLineWidth(f0.width);
        glBegin(GL_LINE_STRIP);
        for(int m = 0; m < points.size(); m++)
        {
            CHPoint point = points.at(m);
            int width = maxx - minx;
            int height = maxy - miny;
            float x = (float)(point.x - minx)/ width * 2 - 1;
            float y = (float)(point.y - miny)/ height * 2 - 1;
            glVertex2f(x,y);
        }
        glEnd();
    }
    if(f0.fill == 1)
    {
        if(type == 2)
        {
            float r = ((float)f0.color2.r)/255;
            float g = ((float)f0.color2.g)/255;
            float b = ((float)f0.color2.b)/255;
            glColor3f(r,g,b);
            glBegin(GL_POLYGON);
            for(int m = 0; m < points.size(); m++)
            {
                CHPoint point = points.at(m);
                int width = maxx - minx;
                int height = maxy - miny;
                float x = (float)(point.x - minx)/width * 2 - 1;
                float y = (float)(point.y - miny)/height * 2 - 1;
                glVertex2f(x,y);
            }
            glEnd();
        }
    }
}


