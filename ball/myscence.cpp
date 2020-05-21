#include "myScence.h"
#include <myitem.h>
myScence::myScence(QGraphicsScene *parent) : QGraphicsScene(parent)
{
    //在构造函数中初始化主场景
    for(int i=0;i<4;i++){
        for(int j=0;j<5;j++){
            this->items[i][j] = new myitem();
            if(i==2 && j==3){
                 QSize picSize(66,67);
                this->items[i][j]->setPixmap(QPixmap(":/new/prefix1/blockB").scaled(picSize));
            }
            this->items[i][j]->setPos(0+ j*66,0 + i*67);
            this->addItem(this->items[i][j]);
        }
    }
    this->nowx=2;
    this->nowy=3;
}
