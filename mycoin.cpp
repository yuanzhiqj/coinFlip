#include "mycoin.h"
#include<QDebug>
//myCoin::myCoin(QWidget *parent) : QWidget(parent)
//{

//}
myCoin::myCoin(QString btnImg)
{
    QPixmap pix;
    bool ret = pix.load(btnImg);
    if(!ret)
    {
        qDebug() << "fail to load btnImg";
        return;
    }
    this->setFixedSize(pix.width(),pix.height());
    this->setStyleSheet("QPushButton{border:0px}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));

    //初始化定时器对象
    timer1 = new QTimer(this);
    timer2 = new QTimer(this);

    //监听翻硬币的信号。并且反转金币
    connect(timer1,&QTimer::timeout,[=](){
        QPixmap pix;
        QString str= QString(":/resource/Coin000%1").arg(this->min++);
        pix.load(str);

        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));

        //翻完后重置
        if(this->min > this->max)
        {
            this->min =1;
            isAnimation = false;
            timer1->stop();
        }
    });
    connect(timer2,&QTimer::timeout,[=](){
        QPixmap pix;
        QString str= QString(":/resource/Coin000%1").arg(this->max--);
        pix.load(str);

        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));

        //翻完后重置
        if(this->max < this->min)
        {
            this->max = 8;
            isAnimation = false;
            timer2->stop();
        }
    });
}

void myCoin::mousePressEvent(QMouseEvent* e)
{
    if(this->isAnimation || this->isWin)
        return;
    else
    {
        QPushButton::mousePressEvent(e);
    }
}

void myCoin::changeFlag()
{
    if(this->flag)
    {
        timer1->start(30);
        isAnimation = true;
        this->flag = false;
    }
    else
    {
        timer2->start(30);
        isAnimation = true;
        this->flag = true;
    }
}
