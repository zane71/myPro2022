#include "mycoin.h"
#include<QDebug>
#include<QTimer>
//MyCoin::MyCoin(QWidget *parent) : QPushButton(parent)
//{

//}

MyCoin::MyCoin(QString coinImg){
    QPixmap pix;
    if(!pix.load(coinImg)){
        qDebug()<<"load erro";
        return;
    }
    this->setFixedSize(pix.width(),pix.height());
    this->setStyleSheet("QPushButton{border:0px}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));

    time1 = new QTimer(this);
    time2 = new QTimer(this);
    connect(time1,&QTimer::timeout,this,[=](){
        QPixmap pix;
        QString str = QString(":/res/Coin000%1.png").arg(this->min++);
        pix.load(str);
        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");/*设置不规则图片样式*/
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));
        if(this->min>this->max)
        {
            this->min=1;
            isAnimation=false;//停止做动画
            time1->stop();
        }
    });

    connect(time2,&QTimer::timeout,this,[=](){
        QPixmap pix;
        QString str = QString(":/res/Coin000%1.png").arg(this->max--);
        pix.load(str);
        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");/*设置不规则图片样式*/
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));
        if(this->min > this->max)
        {
            this->max=8;
            isAnimation=false;//停止做动画
            time2->stop();
        }
    });
}

void MyCoin::mousePressEvent(QMouseEvent *e)
{
    if(this->isAnimation || this->isWin)
    {
        return;
    }
    else
    {
        QPushButton::mousePressEvent(e);
    }
}

//改变标志，执行翻转效果
void MyCoin::changeFlag()
{
    //如果是正面 翻成反面
    if(this->flag)
    {
        time1->start(30);
        isAnimation=true;//开始做动画
        this->flag=false;
        this->isWin=true;
    }
    else{//反面翻正面
        time2->start(30);
        isAnimation=true;//开始做动画
        this->flag=true;
        this->isWin=true;
    }
}
