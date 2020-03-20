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
}
