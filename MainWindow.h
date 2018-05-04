/**************************************
Author:胡超、林?（字符转码函数来自胡琦）
Date:2017/12/23
Update:2018/1/6
Description:窗口类
***************************************/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include <QtGui>
#include <QMainWindow>
#include <QMessageBox>
#include "CSSSpatialIndex.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    /* 单击搜索按钮，执行属性到图的查询操作 */
    void on_pushButton_clicked();

protected:
    /* 单击图上点，执行图到属性的查询操作 */
    void mousePressEvent(QMouseEvent *);

private:
    Ui::MainWindow *ui;
    CSSNameIndex* nidx;
    CSSSpatialIndex* sidx;

    /* 字符转码，来自胡琦 */
    string GB2312ToUTF_8(const char *pText, int pLen);
    void Gb2312ToUnicode(wchar_t* pOut, const char *gbBuffer);
    void UnicodeToUTF_8(char* pOut, wchar_t* pText);
};

#endif // MAINWINDOW_H
