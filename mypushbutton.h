#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QMainWindow>
#include <QObject>
#include <QPushButton>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    //explicit MyPushButton(QWidget *parent = nullptr);
    //构造函数 参数1:正常显示的图片 参数2:按下显示的图片，默认无
    MyPushButton(QString normalImg,QString pressImg="");

    QString normalImgPath;
    QString pressImgPath;

    //弹跳特效
    void zoom1();   //向下跳
    void zoom2();   //向上跳

    //重写按钮按下和释放
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
signals:

public slots:
};

#endif // MYPUSHBUTTON_H
