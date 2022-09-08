#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H
#include<QMouseEvent>
#include <QPushButton>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    //explicit MyPushButton(QWidget *parent = nullptr);
    //
    MyPushButton(QString normalImg,QString pressImg="");

    QString normalImgPath;
    QString pressImgPath;
    void zoom1();
    void zoom2();
    void mousePressEvent(QMouseEvent* e);
    void mouseReleaseEvent(QMouseEvent* e);
    bool m_flag = false; //是否禁用按钮



signals:

};

#endif // MYPUSHBUTTON_H
