#ifndef CHOOSELEVELSCENE_H
#define CHOOSELEVELSCENE_H

#include <QMainWindow>
#include "playscence.h"
class ChooseLevelScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseLevelScene(QWidget *parent = nullptr);
    //重写绘图事件
    void paintEvent(QPaintEvent *event);
    playScence* play = NULL;
signals:
    //告诉mainscence需要返回
    void chooseScenceBack();
    //游戏场景对象指针

public slots:
};

#endif // CHOOSELEVELSCENE_H
