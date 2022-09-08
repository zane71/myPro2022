#include "chooselevelscene.h"
#include<QMenuBar>
#include<QPainter>
#include"mypushbutton.h"
#include<QTimer>
#include<QDebug>
#include<QLabel>
#include<QSound>
ChooseLevelScene::ChooseLevelScene(QWidget *parent) : QMainWindow(parent)
{
    //set fixed size
    setFixedSize(320,588);

    //set Icon
    setWindowIcon(QIcon(":/res/Coin0001.png"));
    //set title
    setWindowTitle("Level_scene");

    //set menu
    QMenuBar*bar=menuBar();
    setMenuBar(bar);
    QMenu *startMenu= bar->addMenu("Play");
    QAction *quitAction = startMenu->addAction("Quit");
    connect(quitAction,&QAction::triggered,[=](){
        this->close();
    });

    //set sound
    QSound *selectsound =new QSound(":/res/TapButtonSound.wav",this);
    QSound *backsound =new QSound(":/res/BackButtonSound.wav",this);

    //set backbt
    MyPushButton *backbt=new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    backbt->setParent(this);
    backbt->move(this->width()-backbt->width(),this->height()-backbt->height());

    connect(backbt,&MyPushButton::clicked,[=](){
        backsound->play();
        emit this->chooseselectback();

    });


    for(int i=0;i<20;++i){
        MyPushButton *menubt=new MyPushButton(":/res/LevelIcon.png");
        menubt->setParent(this);
        menubt->move(25+i%4*70,130+i/4*70);

        connect(menubt,&MyPushButton::clicked,[=](){
            selectsound->play();
            QString str=QString("select %1").arg(i+1);
            qDebug()<<"select %d"<<i+1;

            this->hide();
            playscene =new Playscene(i+1);

            playscene->setGeometry(this->geometry());
            playscene->show();
            connect(playscene,&Playscene::palyback,[=](){
                this->setGeometry(playscene->geometry());

                this->show();
                delete playscene;
                playscene =nullptr;
            });

        });

        QLabel *label1=new QLabel;
        label1->setParent(this);
        label1->setFixedSize(menubt->width(),menubt->height());
        label1->setText(QString::number(i+1));
        label1->move(25+i%4*70,130+i/4*70);;
        label1->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        label1->setAttribute(Qt::WA_TransparentForMouseEvents);
    }


}


void ChooseLevelScene::paintEvent(QPaintEvent*){
    QPainter painter(this);
    QPixmap pixmap;
    pixmap.load(":/res/OtherSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(), pixmap);
    // draw bgcoin
    pixmap.load(":/res/Title.png");
    //pixmap = pixmap.scaled(pixmap.width()*0.5,pixmap.height()*0.5);

    painter.drawPixmap((this->width()-pixmap.width())*0.5,30,pixmap);
}
