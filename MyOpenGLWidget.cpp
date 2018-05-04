#include "MyOpenGLWidget.h"

MyOpenGLWidget::MyOpenGLWidget(QWidget* parent):QOpenGLWidget(parent)
{
    this->file = new CFile("D:/Lydia/c++/SSGIS/src/china.dat","D:/Lydia/c++/SSGIS/src/china.opt",
                                         "D:/Lydia/c++/SSGIS/src/chnCity.txt");
    file->GetCitySet();
}

MyOpenGLWidget::~MyOpenGLWidget()
{
    if(file != 0x00)
    {
        delete file;
        file = 0x00;
    }
}

void MyOpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(1.0f,1.0f,1.0f,0.0f);
}

void MyOpenGLWidget::paintGL()
{
    file->FileOpenDat();
    file->FileOpenOpt();
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    file->map->Draw(file->map->maxx,file->map->maxy,
                    file->map->minx,file->map->miny);
}

void MyOpenGLWidget::resizeGL(int width ,int height)
{
    glViewport(0,0,width,height);
    glMatrixMode(GL_PROJECTION);

}

