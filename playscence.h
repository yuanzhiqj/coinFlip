#ifndef PLAYSCENCE_H
#define PLAYSCENCE_H

#include <QMainWindow>
#include "mycoin.h"
class playScence : public QMainWindow
{
    Q_OBJECT
public:
    //explicit playScence(QWidget *parent = nullptr);
    playScence(int levelNum);
    int levelIndex; //内部成员属性 记录所选关卡
    //重写paintEvent事件 画背景图
    void paintEvent(QPaintEvent*);

    int gameArray[4][4];    //二维数组，维护每个关卡的具体数据
    myCoin* coinBtn[4][4];

    //是否胜利
    bool isWin;
signals:
    //需要返回
    void chooseScenceBack();
public slots:
};

#endif // PLAYSCENCE_H
