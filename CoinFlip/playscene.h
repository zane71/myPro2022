#ifndef PLAYSCENE_H
#define PLAYSCENE_H
#include<QPaintEvent>
#include <QMainWindow>
#include"mycoin.h"
class Playscene : public QMainWindow
{
    Q_OBJECT
public:
    //explicit Playscene(QWidget *parent = nullptr);
    Playscene(int levelNum);
    int levelIndex;
    void paintEvent(QPaintEvent*);
    MyCoin * coinBtn[4][4];

    int gameArray[4][4];//二维数组维护每关关卡的具体数据


    bool m_isWin=false;//是否胜利的标志

    //void paintEvent(QPaintEvent *e);




signals:
    void palyback();
    //void playtochoose();//写一个信号

    void gotoNext(int index);//下一关

};

#endif // PLAYSCENE_H
