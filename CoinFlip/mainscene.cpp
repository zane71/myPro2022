#include "mainscene.h"
#include "ui_mainscene.h"
#include<QPainter>
#include<QDebug>
#include<QTimer>
#include"mypushbutton.h"
#include"chooselevelscene.h"
#include<QSound>
MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScene)
{
    ui->setupUi(this);

    //set fixed size
    setFixedSize(320,588);

    //set Icon
    setWindowIcon(QIcon(":/res/Coin0001.png"));
    //set title
    setWindowTitle("Play5");

    //set quit
    connect(ui->actionQuit,&QAction::triggered,[=](){
        this->close();
    });


    //set sound
    QSound *startsound =new QSound(":/res/TapButtonSound.wav",this);


    //set playbutton
    MyPushButton *Playbt=new MyPushButton(":/res/MenuSceneStartButton.png");
    Playbt->setParent(this);
    Playbt->move(this->width()*0.5-Playbt->width()*0.5,this->height()*0.7);

    chooseScene = new ChooseLevelScene;
    connect(chooseScene,&ChooseLevelScene::chooseselectback,this,[=](){
        this->setGeometry(chooseScene->geometry());
        chooseScene->hide();
        this->show();
    });

    connect(Playbt,&MyPushButton::clicked,[=](){
        startsound->play();
        Playbt->zoom1();
        Playbt->zoom2();
        QTimer::singleShot(200,this,[=](){
            chooseScene->setGeometry(this->geometry());
            this->hide();
            //select scene
            chooseScene->show();

            //listen

        });


    });


}
void MainScene::paintEvent(QPaintEvent*){
    QPainter painter(this);
    QPixmap pixmap;
    pixmap.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(), pixmap);
    // draw bgcoin
    pixmap.load(":/res/Title.png");
    pixmap = pixmap.scaled(pixmap.width()*0.5,pixmap.height()*0.5);

    painter.drawPixmap(10,30,pixmap);
}

MainScene::~MainScene()
{
    delete ui;
}

