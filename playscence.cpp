#include "playscence.h"
#include<QDebug>
#include<QMenuBar>
#include<QPainter>
#include"mypushbutton.h"
#include<QTimer>
#include<QLabel>
#include"mycoin.h"
#include"dataconfig.h"
#include<QPropertyAnimation>
#include<QSound>
//playScence::playScence(QWidget *parent) : QMainWindow(parent)
//{

//}

playScence::playScence(int levelNum)
{
    //qDebug() << levelNum;
    this->levelIndex = levelNum;

    //初始化游戏场景
    //设置固定大小
    this->setFixedSize(320,588);
    //设置图标
    this->setWindowIcon(QPixmap(":/resource/Coin0001.png"));
    //设置标题
    this->setWindowTitle("gameScence");

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
    QSound* flipSound = new QSound(":/resource/ConFlipSound.wav",this);
    QSound* winSound = new QSound(":/resource/LevelWinSound.wav",this);

    //返回按钮
    MyPushButton*backBtn = new MyPushButton(":/resource/BackButton.png",":/resource/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width()-backBtn->width(),this->height()-backBtn->height());

    //点击Back，返回上一页
    connect(backBtn,&MyPushButton::clicked,[=](){
       //qDebug()<<"clicked back";
       //主场景需要监听该事件，所以我们发送一个信号
        QTimer::singleShot(200,this,[=](){
            //qDebug()<<levelNum;
            emit this->chooseScenceBack();
        });
    });

    //显示当前关卡数
    QLabel* label = new QLabel;
    label->setParent(this);
    QFont font;
    font.setFamily("黑体");
    font.setPointSize(10);
    label->setFont(font);
    QString str1 = QString("Leavel: %1").arg(this->levelIndex);
    label->setText(str1);
    label->setGeometry(30,this->height()-50,120,50);

    dataConfig config;
    //初始化每个关卡的二维数组
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            this->gameArray[i][j] = config.mData[this->levelIndex][i][j];
        }
    }

    //胜利图片加载但是未显示
    QLabel* winLabel = new QLabel;
    QPixmap tmpPix;
    tmpPix.load(":/resource/LevelCompletedDialogBg.png");
    winLabel->setGeometry(0,0,tmpPix.width(),tmpPix.height());
    winLabel->setPixmap(tmpPix);
    winLabel->setParent(this);
    winLabel->move((this->width()-tmpPix.width())*0.5,-tmpPix.height());
    //显示金币背景图案
    //创建金币的背景图片
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4;j++)
        {
            QLabel* label = new QLabel;
            label->setGeometry(0,0,50,50);
            label->setPixmap(QPixmap(":/resource/BoardNode.png"));
            label->setParent(this);
            label->move(57+i*50,200+j*50);

            //创建金币
            QString str;
            if(this->gameArray[i][j] == 1)
            {
                str=":/resource/Coin0001.png";
            }
            else
            {
                str=":/resource/Coin0008.png";
            }
            myCoin* coin = new myCoin(str);
            coin->setParent(this);
            coin->move(59+i*50,204+j*50);

            //金币属性赋值
            coin->posX = i;
            coin->posY = j;
            coin->flag = this->gameArray[i][j];

            //将进步放入到二维数组中，便于维护
            coinBtn[i][j] = coin;

            //点击金币翻转
            connect(coin,&myCoin::clicked,[=](){
                flipSound->play();
                //当点击时，其它金币按钮禁用
                for(int i = 0; i < 4; i++)
                {
                    for(int j = 0; j < 4; j++)
                        this->coinBtn[i][j]->isWin=true;
                }
                coin->changeFlag();
                this->gameArray[i][j] = this->gameArray[i][j]==0?1:0;
                //翻转周围金币 延时
                QTimer::singleShot(300,this,[=](){
                    if(coin->posX+1<4)
                    {
                        coinBtn[coin->posX+1][coin->posY]->changeFlag();
                        this->gameArray[coin->posX+1][coin->posY] = this->gameArray[coin->posX+1][coin->posY]==0?1:0;
                    }
                    if(coin->posX-1 >=0)
                    {
                        coinBtn[coin->posX-1][coin->posY]->changeFlag();
                        this->gameArray[coin->posX-1][coin->posY] = this->gameArray[coin->posX-1][coin->posY]==0?1:0;
                    }
                    if(coin->posY+1<4)
                    {
                        coinBtn[coin->posX][coin->posY+1]->changeFlag();
                        this->gameArray[coin->posX][coin->posY+1] = this->gameArray[coin->posX][coin->posY+1]==0?1:0;
                    }
                    if(coin->posY-1>=0)
                    {
                        coinBtn[coin->posX][coin->posY-1]->changeFlag();
                        this->gameArray[coin->posX][coin->posY-1] = this->gameArray[coin->posX][coin->posY+1]==0?1:0;
                    }

                    //解除其它金币的禁用
                    for(int i = 0; i < 4; i++)
                    {
                        for(int j = 0; j < 4; j++)
                            this->coinBtn[i][j]->isWin=false;
                    }

                    //判断是否胜利
                    this->isWin = true;
                    for(int i = 0; i < 4; i++)
                    {
                        for(int j = 0; j < 4; j++)
                        {
                            if(coinBtn[i][j]->flag == false)
                            {
                                this->isWin = false;
                                break;
                            }
                        }
                    }
                    if(this->isWin == true)
                    {
                        qDebug() << "win";
                        //将所有按钮禁用
                        for(int i = 0; i < 4; i++)
                        {
                            for(int j = 0; j < 4; j++)
                            {
                                coinBtn[i][j]->isWin=true;
                            }
                        }
                        winSound->play();
                        //显示胜利图片
                        QPropertyAnimation* animation = new QPropertyAnimation(winLabel,"geometry");
                        //设置时间间隔
                        animation->setDuration(1000);
                        //设置开始位置
                        animation->setStartValue(QRect(winLabel->x(),winLabel->y(),winLabel->width(),winLabel->height()));
                        //设置结束位置
                        animation->setEndValue(QRect(winLabel->x(),winLabel->y()+114,winLabel->width(),winLabel->height()));
                        //设置缓和曲线
                        animation->setEasingCurve(QEasingCurve::OutBounce);
                        //执行动画
                        animation->start();
                    }
                });

            });
        }
    }
}

void playScence::paintEvent(QPaintEvent*){
    //加载背景
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/resource/PlayLevelSceneBg.png");

    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //左上角图标
    pix.load(":/resource/Title.png");
    pix = pix.scaled(pix.width()*0.5,pix.height()*0.5);
    painter.drawPixmap(10,30,pix);
}

