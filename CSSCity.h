/**************************************
Author:林玥
Date:2017/12/19
Update:2018/1/3
Description:省会城市信息存储类
***************************************/
#ifndef CSSCITY_H
#define CSSCITY_H

#include <iostream>
#include <string>
#include <qrect>
#include <QtWidgets/qdesktopwidget.h>
#include <QApplication>
#include "CHPoint.h"
using namespace std;

class CSSCity
{
public:
    CSSCity();
    ~CSSCity();

    string name;//城市名
    string pinyin;//城市拼音首字母，如“哈尔滨”为“heb”
    CHPoint geoPt;//地理坐标

};

#endif // CSSCITY_H
