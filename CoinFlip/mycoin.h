#ifndef MYCOIN_H
#define MYCOIN_H

#include <QPushButton>

class MyCoin : public QPushButton
{
    Q_OBJECT
public:
//    explicit MyCoin(QWidget *parent = nullptr);
    MyCoin(QString coinImg);

    //coin attribute
    int posX;
    int posY;
    bool flag=false;


    //改变标志的方法
       void changeFlag();
       QTimer *time1;//正面翻反面的定时器
       QTimer *time2;//反面翻正面的定时器
       int min=1;//最小图片
       int max=8;//最大图片

       //执行动画的标志
       bool isAnimation=false;


       //重写按下和释放
       void mousePressEvent(QMouseEvent *e);
      //  MyCoin * coinBtn[4][4];
       bool isWin=false;

signals:

};

#endif // MYCOIN_H
