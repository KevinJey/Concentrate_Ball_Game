#ifndef MYSCENCE_H
#define MYSCENCE_H

#include <QObject>
#include <QGraphicsScene>
#include <myitem.h>
class myScence : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit myScence(QGraphicsScene *parent = 0);
    //封装特性 得到当前小球的 横纵坐标
    int getNowx(){return nowx;}
    int getNowy(){return nowy;}
    //
    void setNowx(int x){nowx=x;}
    void setNowy(int y){nowy=y;}
    myitem *items[4][5];
signals:

public slots:

private:
     //myitem类 表示的是每个方框
    int nowx,nowy;
    //当前小球的坐标
};

#endif // MYSCENCE_H
