#include "CFile.h"
#include "MainWindow.h"
#include <QMainWindow>
#include <QtGui>
#include <QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();
    a.connect(&a, SIGNAL( lastWindowClosed() ), &a, SLOT( quit()));
    return a.exec();
}
