/**************************************
Author:ºú³¬
Date:2017/12/23
Update:2018/1/6
Description:openGL»æÍ¼Àà
***************************************/
#ifndef MYOPENGLWIDGET_H
#define MYOPENGLWIDGET_H

#include <QtOpenGL/QGL>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QToolTip>
#include <QLineEdit>
#include <QPushButton>
#include "CSSSpatialIndex.h"
#include "CHPoint.h"
#include "CFile.h"
using namespace std;

class QOpenGLShaderProgram;

class MyOpenGLWidget: public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit MyOpenGLWidget(QWidget* parent = 0);
    ~MyOpenGLWidget();

    CFile* file;
    CSSSpatialIndex* sidx;

    void initializeGL();
    void paintGL();
    void resizeGL(int width,int height);

private:
    QToolTip* toolTip;

};

#endif // MYOPENGLWIDGET_H
