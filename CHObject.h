/**************************************
Author:胡超
Date:2017/12/23
Update:2018/1/6
Description:对象类，派生线面的子类
***************************************/
#ifndef CHOBJECT_H
#define CHOBJECT_H

#include <QtOpenGL/QGL>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <vector>
#include <string>
#include "CHPoint.h"

using namespace std;

/* 颜色 */
struct color
{
    int r;
    int g;
    int b;
};

/* 绘制信息 */
struct f
{
    string name;
    int line;
    float width;
    color color1;
    int fill;
    color color2;
};

class CHObject
{
public:
    CHObject();
    virtual ~CHObject();

    int type;//目标类型

    virtual void Draw(f f0,int maxx,int maxy,int minx,int miny) = 0;
    virtual void AddPoint(CHPoint pt) = 0;
};

#endif // CHOBJECT_H
