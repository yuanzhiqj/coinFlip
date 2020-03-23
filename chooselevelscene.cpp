#include "chooselevelscene.h"
#include<QMenuBar>
#include<QPainter>
#include<QDebug>
#include<QTimer>
#include<QSound>
#include"mypushbutton.h"
#include<QLabel>
ChooseLevelScene::ChooseLevelScene(QWidget *parent) : QMainWindow(parent)
{
    //配置选择关卡场景
    this->setFixedSize(320,588);
    //设置图标
    this->setWindowIcon(QPixmap(":/resource/Coin0001.png"));
    //设置标题
    this->setWindowTitle("Choose level");
    //菜单栏创建
    QMenuBar* bar = menuBar();
    setMenuBar(bar);
    //创建开始菜单
    QMenu* startMenu = bar->addMenu("menu");
    //创建退出菜单项
    QAction* quitAction = startMenu->addAction("quit");
    connect(quitAction,&QAction::triggered,[=](){
        this->close();
    });

    //音效
    QSound* chooseSound = new QSound(":/resource/TapButtonSound.wav",this);
    QSound* backSound = new QSound(":/resource/BackButtonSound.wav",this);

    //返回按钮
    MyPushButton*backBtn = new MyPushButton(":/resource/BackButton.png",":/resource/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width()-backBtn->width(),this->height()-backBtn->height());

    //点击Back，返回上一页
    connect(backBtn,&MyPushButton::clicked,[=](){
       //qDebug()<<"clicked back";
       //主场景需要监听该事件，所以我们发送一个信号
        QTimer::singleShot(200,this,[=](){
            emit this->chooseScenceBack();
        });
    });

    //创建选择关卡按钮
    for(int i = 0; i < 20; i++)
    {
        MyPushButton* menuBtn = new MyPushButton(":/resource/LevelIcon.png");
        menuBtn->setParent(this);
        menuBtn->move(25+i%4*70,130+i/4*70);
        //监听点击事件
        connect(menuBtn,&MyPushButton::clicked,[=](){
            //qDebug()<<i+1;
            //播放音效
            chooseSound->play();
            //进入到游戏场景

            this->hide(); //选关场景隐藏
            play = new playScence(i+1);
            play->setGeometry(this->geometry());
            play->show();

            //监听到返回信号
            connect(play,&playScence::chooseScenceBack,[=](){
                this->setGeometry(play->geometry());
                backSound->play();
                delete play;
                play=NULL;
                this->show();
            });
        });

        QLabel* label = new QLabel;
        label->setParent(this);
        label->setFixedSize(menuBtn->width(),menuBtn->height());
        label->setText(QString::number(i+1));
        label->move(25+i%4*70,130+i/4*70);
        //对齐
        label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        //设置鼠标穿透
        label->setAttribute(Qt::WA_TransparentForMouseEvents);
    }
}

void ChooseLevelScene::paintEvent(QPaintEvent*){
    //加载背景
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/resource/OtherSceneBg.png");

    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //加载标题
    pix.load(":/resource/Title.png");
    painter.drawPixmap((this->width()-pix.width())*0.5,30,pix.width(),pix.height(),pix);
}
