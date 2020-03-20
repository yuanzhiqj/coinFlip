#ifndef MYCOIN_H
#define MYCOIN_H

#include <QPushButton>

class myCoin : public QPushButton
{
    Q_OBJECT
public:
    //explicit myCoin(QWidget *parent = nullptr);
    //参数代表金币或者银币
    myCoin(QString btnImg);
signals:

public slots:
};

#endif // MYCOIN_H
