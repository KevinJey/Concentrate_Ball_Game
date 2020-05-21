#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProgressBar>
#include <myScence.h>
#include <QTime>
#include <QTimer>
//这是主窗口头文件
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
    //计时器和ProgressBar的更新信号
    void updateChose();
    void updatePro();
    void on_pushButton_clicked();
    void on_Gobutton_clicked();

private:
    Ui::MainWindow *ui;  //界面
    int flag; //当前输入的标志位 用于控制ProgressBar的进度条
    myScence *sc; //视图场景
    QTimer *picTime; //为图片设置的QTimer
    QTimer *proTime;//为progressBar设置的QTimer 5s改变一次
    int nowShine;//现在闪烁的方向图标
    void moveTo();//移动动作
    bool judge(int x,int y); //判断当前小球的坐标是否出界

protected:
    //用于捕捉键盘时间的两个函数 一个用于识别按下 一个用于识别松开
    virtual void keyPressEvent(QKeyEvent *ev);
    virtual void keyReleaseEvent(QKeyEvent *ev);
};

#endif // MAINWINDOW_H
