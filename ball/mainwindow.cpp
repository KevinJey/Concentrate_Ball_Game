#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QProgressBar>
#include <QString>
#include <QLabel>
#include <myScence.h>
#include <QDebug>
#include <QTimer>
#include<QKeyEvent>
#include <QTime>
#include <QDialog>
#include <iostream>
#include <QDebug>
#include <QMessageBox>
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    this->flag = 0; //表示进度条的取值范围的状态标志位
    //分别是状态栏和方向选择的信号关联的QTimer
    this->proTime = new QTimer();
    this->picTime = new QTimer();
    //设置connect访问时间间隔
    this->proTime->start(1000); //设置访问时间为1s
    connect(this->proTime,SIGNAL(timeout()),this,SLOT(updatePro()));
    this->picTime->start(5000); //设置访问时间为5s
    connect(this->picTime,SIGNAL(timeout()),this,SLOT(updateChose()));

    this->sc = new myScence(); //新建一个场景


    this->ui->myGraphicsView->setScene(sc); //myGraphicsView


    //四个方向
    this->nowShine = 0;//闪烁的图标从第一个位置开始

    this->ui->leftLabel->setStyleSheet("border-image: url(:/new/prefix1/cl);");

    //使这个窗口具有获取捕捉键盘事件的能力
    this->grabKeyboard();
}

MainWindow::~MainWindow() //析构函数
{
   // delete bar;
    delete sc;
    delete picTime;
    delete proTime;
    delete ui;
}
//此函数已不用
void MainWindow::on_pushButton_clicked()
{
    QString am=ui->progressBar->text();
    QDialog *dialog = new QDialog();
    QLabel *intentionLabel = new QLabel(dialog);

    intentionLabel->setText(am);

 //   qDebug()<<am<<endl;
    dialog->setModal(true);
    dialog->show();
    dialog->resize(50,50);
}

void MainWindow::on_Gobutton_clicked()//按下指令框的确认按钮后
{/*
   // QString Order =
    QString inputOrder = this->ui->InputEdit->text();
    if(inputOrder.isEmpty()==true){
        QString Title="警告";
        QString strInfomation = "输入操作为空!跳过当前选择！";
        QMessageBox::warning(this,Title,strInfomation);
        MainWindow::updateChose();
        return ;
    }
    QString ChooseSignal("X");
    QString NotSignal("Z");
    qDebug()<<inputOrder;
    if(QString::localeAwareCompare(ChooseSignal,inputOrder)==0){
        QString Title="提示";
        QString strInfomation = "您选择了该移动操作";
        QMessageBox::information(this,Title,strInfomation,QMessageBox::Ok,QMessageBox::NoButton);
        moveTo();
        flag = 2;
    }else if(QString::localeAwareCompare(inputOrder,NotSignal)==0){
        QString Title="提示";
        QString strInfomation = "您未选中该操作,并跳过此次选择";
        QMessageBox::information(this,Title,strInfomation,QMessageBox::Ok,QMessageBox::NoButton);
        MainWindow::updateChose();
        flag = 1;
    }else{
        flag = 0;QString Title="提示";
        QString strInfomation = "您未输入 X , Z 或 空.未选中该操作！";
        QMessageBox::information(this,Title,strInfomation,QMessageBox::Ok,QMessageBox::NoButton);
    }
 //   if(flag!=2) ;*/
}


void MainWindow::updateChose(){ // 对方向选择的更新
    if(this->nowShine%6 == 0){
        //左恢复
        qDebug()<<this->nowShine;
        this->ui->leftLabel->setStyleSheet("border-image: url(:/new/prefix1/left);");
        this->ui->rightLabel->setStyleSheet("border-image: url(:/new/prefix1/cr);");
        this->nowShine++;
    }else if(this->nowShine%6==1){
        //右恢复
        this->ui->rightLabel->setStyleSheet("border-image: url(:/new/prefix1/right);");
        this->ui->upLabel->setStyleSheet("border-image: url(:/new/prefix1/cu);");
        this->nowShine++;
    }else if(this->nowShine%6 == 2){
        //上恢复
        this->ui->upLabel->setStyleSheet("border-image: url(:/new/prefix1/up);");
        this->ui->downLabel->setStyleSheet("border-image: url(:/new/prefix1/cd);");

        this->nowShine++;
    }else if(this->nowShine%6 == 3){
        //下恢复
        this->ui->downLabel->setStyleSheet("border-image: url(:/new/prefix1/down);");
        this->ui->upleftLabel->setStyleSheet("border-image: url(:/new/prefix1/chooseleftup.png);");
        this->nowShine++;
    }else if(this->nowShine%6 == 4){
        this->ui->upleftLabel->setStyleSheet("border-image: url(:/new/prefix1/leftup.png);");
        this->ui->rightdownLabel->setStyleSheet("border-image: url(:/new/prefix1/chooserightdown.png);");
        this->nowShine++;
    }else if(this->nowShine%6 == 5){
        this->ui->rightdownLabel->setStyleSheet("border-image: url(:/new/prefix1/rightdown.png);");
        this->ui->leftLabel->setStyleSheet("border-image: url(:/new/prefix1/cl);");
        this->nowShine++;
    }
}

void MainWindow::updatePro(){
    int index;

    if(this->flag==1){ //30-60徘徊
        index = ((int)rand())%31 + 30;
        this->ui->progressBar->setValue(index);
    }else if(this->flag==2){ //选中此操作
        index = ((int)rand()%41)+ 60;
        this->ui->progressBar->setValue(index);
   //     this->flag = 0;
    }else{
        index = ((int)rand()%31);
        this->ui->progressBar->setValue(index);
    }
    this->ui->progressBar->update();
    this->ui->NowLine->setText(QString::number(index,10));
}
bool MainWindow::judge(int x,int y){
    if(x<0 || y<0)return false;
    if(x>=4 || y>=5) return false;
    return true;
}

void MainWindow::moveTo(){
    const int fx[]={0,0,-1,1,-1,1};
    const int fy[]={-1,1,0,0,-1,1};

    int dirc;

    dirc=this->nowShine%6; //0 1 2 3 4 5
    int x,y;
    x=this->sc->getNowx();
    y=this->sc->getNowy();
    int nx,ny;
    nx = x + fx[dirc];
    ny = y+ fy[dirc];
    if(this->judge(nx,ny)==true){
        QPixmap pic(":/new/prefix1/bolckA"); //原图
        QPixmap newpic(":/new/prefix1/blockB"); //更新后的圆圈图
        QSize picSize(66,67); //缩放尺寸
        QPixmap tmpPic = pic.scaled(picSize); //缩放
        QPixmap newPictmp = newpic.scaled(picSize);
        this->sc->items[x][y]->setPixmap(tmpPic);
        this->sc->items[x][y]->setPos(0+ 66*y,0 + 67*x);
        this->sc->items[nx][ny]->setPixmap(newPictmp);
        this->sc->items[nx][ny]->setPos(0+ 66*ny,0 + 67*nx);
        this->sc->setNowx(nx);
        this->sc->setNowy(ny);
    }else{
       QString title="警告!";
       QString infor="小球已经越界了!";
       QMessageBox::warning(this,title,infor);
    }
}

//读取键盘键入的事件
void MainWindow::keyPressEvent(QKeyEvent *event){ //键盘按下事件
   if(event->key() == Qt::Key_X){//按下的按键是X
       //this->moveTo();
       return ;
   }

}

void MainWindow::keyReleaseEvent(QKeyEvent *event){
   if(event->key() == Qt::Key_X){ //如果按下的键位是X 则选择
        flag =2;
        this->moveTo();

        return ;
    }else if(event->key() == Qt::Key_Z){//如果是Z 则改变标志位即可
        flag =1;
    }else{
        flag = 0;
    }
}
