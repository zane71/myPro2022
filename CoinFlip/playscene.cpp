#include "playscene.h"
#include<QDebug>
#include<QPainter>
#include<QLabel>
#include"mypushbutton.h"
#include<QMenuBar>
#include<QTimer>
#include "mycoin.h"
#include<dataconfig.h>
#include<QPropertyAnimation>
#include<QSound>
//Playscene::Playscene(QWidget *parent) : QMainWindow(parent)
//{

//}

Playscene::Playscene(int levelNum){
    this->levelIndex=levelNum;
    QString str=QString("you select the %1  guan").arg(levelNum);
    qDebug()<<str;


    //set fixed size
    setFixedSize(320,588);

    //set Icon
    setWindowIcon(QIcon(":/res/Coin0001.png"));
    //set title
    setWindowTitle("Playing");

    //set menu
    QMenuBar*bar=menuBar();
    setMenuBar(bar);
    QMenu *startMenu= bar->addMenu("Play");
    QAction *quitAction = startMenu->addAction("Quit");
    connect(quitAction,&QAction::triggered,[=](){
        this->close();
    });
    //set sound
    QSound *backsound =new QSound(":/res/BackButtonSound.wav",this);
    QSound *flipsound =new QSound(":/res/ConFlipSound.wav",this);
    //QSound *winsound =new QSound(":/res/LevelWinSound.wav",this);


    //set backbt
    MyPushButton *backbt=new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    backbt->setParent(this);
    backbt->move(this->width()-backbt->width(),this->height()-backbt->height());

    connect(backbt,&MyPushButton::clicked,[=](){
        backsound->play();
        emit this->palyback();
    });

    QLabel *level =new QLabel;
    level->setParent(this);
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(20);
    level->setFont(font);
    QString str1=QString("Level: %1").arg(levelNum);

    level->setText(str1);
    level->setGeometry(30,this->height()-50,120,50);
    dataconfig datacfg;
    for(int i=0;i<4;++i){
        for(int j=0;j<4;++j){
            this->gameArray[i][j]=datacfg.mData[this->levelIndex][i][j];
        }
    }

    //set success picture
    QLabel *winlabel =new QLabel;
    QPixmap tempix;

    tempix.load(":/res/LevelCompletedDialogBg.png");
    winlabel->setPixmap(tempix);
    winlabel->setGeometry(0,0,tempix.width(),tempix.height());
    winlabel->setParent(this);
    winlabel->move((this->width()-tempix.width())*0.5,-tempix.height());



    for(int i=0;i<4;++i){
        for(int j=0;j<4;++j){
            QLabel *label=new QLabel;
            label->setGeometry(0,0,50,50);
            label->setPixmap(QPixmap(":/res/BoardNode(1).png"));
            label->setParent(this);
            label->move(57+i*50,200+j*50);
            QString s;
            if(gameArray[i][j]==1){
                s=":/res/Coin0001.png";
            }
            else{
                s=":/res/Coin0008.png";
            }
            MyCoin *coin =new MyCoin(s);
            coin->setParent(this);
            coin->move(59+i*50,204+j*50);
            coin->posX=i;
            coin->posY=j;
            coin->flag=gameArray[i][j];


            //将金币放入到金币的二维数组里面
            coinBtn[i][j]=coin;

            //点击金币，进行翻转
            connect(coin,&MyCoin::clicked,this,[=](){
                flipsound->play();
                //在翻转金币的时候禁用其他按钮
                for(int i = 0 ; i < 4; i++)
                {
                    for(int j = 0 ; j < 4 ; j++)
                    {
                        this->coinBtn[i][j]->isWin = true;
                    }
                }

                //翻转本身
                coin->changeFlag();
                this->gameArray[i][j]=this->gameArray[i][j]==0?1:0;
                QTimer::singleShot(100,this,[=](){
                    //翻转四周
                    if(coin->posX<3)
                    {
                        coinBtn[coin->posX+1][coin->posY]->changeFlag();
                        this->gameArray[coin->posX+1][coin->posY]=this->gameArray[coin->posX+1][coin->posY]==0?1:0;
                    }
                    if(coin->posX>0)
                    {
                        coinBtn[coin->posX-1][coin->posY]->changeFlag();
                        this->gameArray[coin->posX-1][coin->posY]=this->gameArray[coin->posX-1][coin->posY]==0?1:0;
                    }
                    if(coin->posY<3)
                    {
                        coinBtn[coin->posX][coin->posY+1]->changeFlag();
                        this->gameArray[coin->posX][coin->posY+1]=this->gameArray[coin->posX][coin->posY+1]==0?1:0;
                    }
                    if(coin->posY>0)
                    {
                        coinBtn[coin->posX][coin->posY-1]->changeFlag();
                        this->gameArray[coin->posX][coin->posY-1]=this->gameArray[coin->posX][coin->posY-1]==0?1:0;
                    }

                    //在翻转完金币后释放其他按钮
                    for(int i = 0 ; i < 4; i++)
                    {
                        for(int j = 0 ; j < 4 ; j++)
                        {
                            this->coinBtn[i][j]->isWin = false;
                        }
                    }

                    //判断是否胜利
                    this->m_isWin=true;
                    for(int i=0;i<4;i++)
                    {
                        for(int j=0;j<4;j++)
                        {
                            if(coinBtn[i][j]->flag==false)
                            {
                                this->m_isWin=false;
                                break;
                            }
                        }
                    }


                    if(this->m_isWin==true)
                    {
                        backbt->m_flag=true;
                        //this->backbt->m_flag = true;
                        for(int i=0;i<4;i++)
                        {
                            for(int j=0;j<4;j++)
                            {
                                coinBtn[i][j]->isWin = true;
                            }
                        }

                        QPropertyAnimation * animation = new QPropertyAnimation(winlabel,"geometry");
                        animation->setDuration(2000);
                        animation->setStartValue(QRect(winlabel->x(),winlabel->y(),winlabel->width(),winlabel->height()));
                        animation->setEndValue(QRect(winlabel->x(),winlabel->y()+200,winlabel->width(),winlabel->height()));
                        animation->setEasingCurve(QEasingCurve::OutBounce);
                        animation->start();

                        QSound * soud1 = new QSound(":/res/LevelWinSound.wav",this);
                        soud1->play();
                        QTimer::singleShot(3000,this,[=](){
                            backbt->m_flag = false;
                            soud1->stop();
                            //发送一个申请下一关的信号
                            emit gotoNext(levelIndex);
                        });




                    }
                });
            });
        }
    }
}


void Playscene::paintEvent(QPaintEvent*){
    QPainter painter(this);
    QPixmap pixmap;
    pixmap.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(), pixmap);
    // draw bgcoin
    pixmap.load(":/res/Title.png");
    pixmap = pixmap.scaled(pixmap.width()*0.5,pixmap.height()*0.5);

    painter.drawPixmap(10,30,pixmap);
}
