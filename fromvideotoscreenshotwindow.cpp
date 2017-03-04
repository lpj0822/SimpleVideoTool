#pragma execution_character_set("utf-8")
#include "fromvideotoscreenshotwindow.h"
#include <QDebug>
#include <QFileDialog>
#include <QFileInfo>

FromVideoToScreenshotWindow::FromVideoToScreenshotWindow(QWidget *parent) : QWidget(parent)
{
    init();
    initUI();
    initConnect();
}

FromVideoToScreenshotWindow::~FromVideoToScreenshotWindow()
{
    if(saveScreenshot)
    {
        saveScreenshot->stopThread();
        saveScreenshot->wait();
        delete saveScreenshot;
        saveScreenshot = NULL;
    }
}

void FromVideoToScreenshotWindow::slotOpen()
{
    QString name=QFileDialog::getOpenFileName(this,tr("open video dialog"),".","video files(*.avi *.mp4 *.mpg)");
    path = name;
    this->pathText->setText(path);
    if(videoProcess._Get())
    {
        if(path.trimmed().isEmpty())
        {
            qDebug()<<"打开的视频文件路径有误:"<<path<<endl;
            return;
        }
        videoProcess->closeVideo();
        if(videoProcess->openVideo(path)==0)
        {
            int countFrame=videoProcess->getFrameCount();
            int countSec=countFrame/videoProcess->getFrameFPS();

            spaceBox->setMaximum(countFrame);
            startPosBox->setMaximum(countSec);
            stopPosBox->setMaximum(countSec);

            openButton->setEnabled(true);
            startButton->setEnabled(true);
            stopButton->setEnabled(false);
        }
    }
}

void FromVideoToScreenshotWindow::slotStart()
{
    QFileInfo info(path);
    qDebug()<<info.absolutePath();
    if(saveScreenshot->initSaveScreenshotData(info.absolutePath(),postBox->currentText(),videoProcess,isAllSaveBox->isChecked(),spaceBox->value(),startPosBox->value(),stopPosBox->value())==0)
    {
        saveScreenshot->startThread();
        saveScreenshot->start();
        stopButton->setEnabled(true);
        startButton->setEnabled(false);
        openButton->setEnabled(false);
    }
}

void FromVideoToScreenshotWindow::slotStop()
{
    saveScreenshot->stopThread();
    stopButton->setEnabled(false);
    startButton->setEnabled(false);
    openButton->setEnabled(true);
}

void FromVideoToScreenshotWindow::slotFinish(QString name)
{
    qDebug()<<"save image:"<<name;
    stopButton->setEnabled(false);
    startButton->setEnabled(false);
    openButton->setEnabled(true);
}

void FromVideoToScreenshotWindow::init()
{
    videoProcess=std::shared_ptr<VideoProcess>(new VideoProcess());
    saveScreenshot=new SaveScreenshotThread();
    path="";
}

void FromVideoToScreenshotWindow::initUI()
{
    mainLayout=new QVBoxLayout();

    QHBoxLayout *layout1=new QHBoxLayout();
    isAllSaveBox=new QCheckBox(tr("是否全部播放"));
    isAllSaveBox->setChecked(true);

    postLabel=new QLabel(tr("保存截图的格式："));
    postBox=new QComboBox();
    postBox->addItem(".png");
    postBox->addItem(".jpg");

    layout1->addWidget(isAllSaveBox);
    layout1->addWidget(postLabel);
    layout1->addWidget(postBox);

    QHBoxLayout *layout2=new QHBoxLayout();
    layout2->setSpacing(20);

    spaceLabel=new QLabel(tr("视频间隔播放的帧数："));
    spaceBox=new QSpinBox();
    spaceBox->setMinimum(1);
    spaceBox->setValue(1);

    startLabel=new QLabel(tr("视频开始播放时间："));
    startPosBox=new QSpinBox();
    startPosBox->setSuffix("s");
    startPosBox->setMinimum(0);
    startPosBox->setValue(0);

    stopLabel=new QLabel(tr("视频结束播放时间："));
    stopPosBox=new QSpinBox();
    stopPosBox->setSuffix("s");
    stopPosBox->setMinimum(0);
    stopPosBox->setValue(0);

    layout2->addWidget(spaceLabel);
    layout2->addWidget(spaceBox);
    layout2->addWidget(startLabel);
    layout2->addWidget(startPosBox);
    layout2->addWidget(stopLabel);
    layout2->addWidget(stopPosBox);

    QHBoxLayout *layout3=new QHBoxLayout();
    pathText=new QLineEdit();
    pathText->setReadOnly(true);
    openButton=new QPushButton(tr("打开视频"));

    layout3->addWidget(pathText);
    layout3->addWidget(openButton);

    QHBoxLayout *layout4=new QHBoxLayout();
    layout4->setSpacing(50);
    startButton=new QPushButton(tr("开始播放"));
    stopButton=new QPushButton(tr("结束播放"));
    startButton->setEnabled(false);
    stopButton->setEnabled(false);

    layout4->addWidget(startButton);
    layout4->addWidget(stopButton);

    QHBoxLayout *layout5=new QHBoxLayout();
    infoLabel=new QLabel(tr("备注：a键---后退视频 d键---前进视频 w键---保存截图\n      空格键---关闭截图窗口 Esc键---结束视频播放"));
    infoLabel->setFixedHeight(40);
    layout5->addWidget(infoLabel);

    mainLayout->addLayout(layout1);
    mainLayout->addLayout(layout2);
    mainLayout->addLayout(layout3);
    mainLayout->addLayout(layout4);
    mainLayout->addLayout(layout5);

    this->setLayout(mainLayout);
}

void FromVideoToScreenshotWindow::initConnect()
{
    connect(openButton,&QPushButton::clicked,this,&FromVideoToScreenshotWindow::slotOpen);
    connect(startButton,&QPushButton::clicked,this,&FromVideoToScreenshotWindow::slotStart);
    connect(stopButton,&QPushButton::clicked,this,&FromVideoToScreenshotWindow::slotStop);
    connect(saveScreenshot,&SaveScreenshotThread::signalFinish,this,&FromVideoToScreenshotWindow::slotFinish);
}
