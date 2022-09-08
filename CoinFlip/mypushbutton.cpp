#include "mypushbutton.h"
#include<QDebug>
#include<QPropertyAnimation>
//MyPushButton::MyPushButton(QWidget *parent) : QPushButton(parent)
//{

//}

MyPushButton::MyPushButton(QString normalImg,QString pressImg){
    this->normalImgPath=normalImg;
    this->pressImgPath=pressImg;
    QPixmap pix;
    if(!pix.load(normalImg)){
        qDebug()<<"load erro";
        return;
    }
    this->setFixedSize(pix.width(),pix.height());
    this->setStyleSheet("QPushButton{border:0px}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width()*0.7,pix.height()*0.7));


}
void MyPushButton::zoom1(){
    QPropertyAnimation *animation =new QPropertyAnimation(this,"geometry");
    animation->setDuration(200);
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    animation->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start();
}
void MyPushButton::zoom2(){
    QPropertyAnimation *animation =new QPropertyAnimation(this,"geometry");
    animation->setDuration(200);
    animation->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start();

}

void MyPushButton::mousePressEvent(QMouseEvent* e){
    if(this->pressImgPath!=""){
        QPixmap pix;
        if(!pix.load(this->pressImgPath)){
            qDebug()<<"load erro";
            return;
        }
        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width()*0.7,pix.height()*0.7));
    }
    return QPushButton::mousePressEvent(e);

}
void MyPushButton::mouseReleaseEvent(QMouseEvent* e){
    if(this->pressImgPath!=""){
        QPixmap pix;
        if(!pix.load(this->normalImgPath)){
            qDebug()<<"load erro";
            return;
        }
        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width()*0.7,pix.height()*0.7));
    }
    return QPushButton::mouseReleaseEvent(e);
}
