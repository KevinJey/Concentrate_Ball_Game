#include "mainwindow.h"
#include <QApplication>
#include <QPushButton>
#include <sys/time.h>
#include <QWidget>
#include <iostream>
#include <QDebug>
#include <windows.h>
using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowFlags(w.windowFlags()& ~Qt::WindowMaximizeButtonHint& ~Qt::WindowMinimizeButtonHint);
    w.show();
    return a.exec();
}
