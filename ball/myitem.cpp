#include "myitem.h"
#include <QPixmap>
#include <QSize>
myitem::myitem()
{
    QPixmap pic;
    pic.load(":/new/prefix1/bolckA");
    QSize picSize(66,67);
    QPixmap tmpPic = pic.scaled(picSize);
    this->setPixmap(tmpPic);
    //为每个方框进行初始化
}
