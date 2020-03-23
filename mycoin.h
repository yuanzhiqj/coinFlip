#ifndef MYCOIN_H
#define MYCOIN_H

#include <QPushButton>
#include<QTimer>
class myCoin : public QPushButton
{
    Q_OBJECT
public:
    //explicit myCoin(QWidget *parent = nullptr);
    //参数代表金币或者银币
    myCoin(QString btnImg);

    //金币的属性
    int posX;
    int posY;
    bool flag; //正反标志

    //改变标志的方法
    void changeFlag();
    QTimer* timer1;  //正->反
    QTimer* timer2;  //反->正
    int min = 1;
    int max = 8;
    //执行动画标志
    bool isAnimation = false;

    //重写按下和释放
    void mousePressEvent(QMouseEvent*e);

    //禁用按钮的标志
    bool isWin = false;
signals:

public slots:
};

#endif // MYCOIN_H
