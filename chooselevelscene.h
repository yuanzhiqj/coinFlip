#ifndef CHOOSELEVELSCENE_H
#define CHOOSELEVELSCENE_H

#include <QMainWindow>

class ChooseLevelScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseLevelScene(QWidget *parent = nullptr);
    //重写绘图事件
    void paintEvent(QPaintEvent *event);
signals:
    //告诉mainscence需要返回
    void chooseScenceBack();
public slots:
};

#endif // CHOOSELEVELSCENE_H
