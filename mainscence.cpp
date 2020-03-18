#include "mainscence.h"
#include "ui_mainscence.h"
#include<QPainter>
#include<QDebug>
#include<QTimer>
#include"mypushbutton.h"
MainScence::MainScence(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainScence)
{
    ui->setupUi(this);
    //配置主场景
    //设置固定的大小
    setFixedSize(320,588);
    //设置图标
    setWindowIcon(QIcon(":/resource/Coin0001.png"));
    //设置标题
    setWindowTitle("CoinFlip");

    //quit按钮实现
    connect(ui->actionquit,&QAction::triggered,[=](){
        this->close();
    });

    //开始按钮
    MyPushButton* startBtn = new MyPushButton(":/resource/MenuSceneStartButton.png");
    startBtn->setParent(this);
    startBtn->move(this->width()*0.5-startBtn->width()*0.5,this->height()*0.7);
    //实例化选择关卡
    chooseScence = new ChooseLevelScene;
    connect(startBtn,&QPushButton::clicked,[=](){
        //qDebug()<<"click";
        //弹起特效
        startBtn->zoom1();
        startBtn->zoom2();

        //延时进入关卡选择场景并将自身隐藏
        QTimer::singleShot(500,this,[=](){
            this->hide();
            chooseScence->show();
        });
    });

    //监听到选择关卡的返回
    connect(chooseScence,&ChooseLevelScene::chooseScenceBack,[=](){
        chooseScence->hide();
        this->show();
    });

}
void MainScence::paintEvent(QPaintEvent*){
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/resource/PlayLevelSceneBg.png");

    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //左上角图标
    pix.load(":/resource/Title.png");
    pix = pix.scaled(pix.width()*0.5,pix.height()*0.5);
    painter.drawPixmap(10,30,pix);
}
MainScence::~MainScence()
{
    delete ui;
}
