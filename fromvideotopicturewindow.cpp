#pragma execution_character_set("utf-8")
#include "fromvideotopicturewindow.h"
#include <QDebug>
#include <QFileDialog>
#include <QFileInfo>

FromVideoToPictureWindow::FromVideoToPictureWindow(QWidget *parent) : QWidget(parent)
{
    init();
    initUI();
    initConnect();
}

FromVideoToPictureWindow::~FromVideoToPictureWindow()
{
    if(saveImage)
    {
        saveImage->stopThread();
        saveImage->wait();
        delete saveImage;
        saveImage=NULL;
    }
}

void FromVideoToPictureWindow::slotOpen()
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
            int countSec=videoProcess->getFrameCount()/videoProcess->getFrameFPS();
            startPosBox->setMaximum(countSec);
            stopPosBox->setMaximum(countSec);

            startButton->setEnabled(true);
            stopButton->setEnabled(false);
        }
    }
}

void FromVideoToPictureWindow::slotStart()
{
    QFileInfo info(path);
    qDebug()<<info.absolutePath();
    if(saveImage->initSaveImageData(info.absolutePath(),postBox->currentText(),videoProcess,isAllSaveBox->isChecked(),startPosBox->value(),stopPosBox->value())==0)
    {
        saveImage->startThread();
        saveImage->start();
        stopButton->setEnabled(true);
        startButton->setEnabled(false);
        openButton->setEnabled(false);
    }
}

void FromVideoToPictureWindow::slotStop()
{
    saveImage->stopThread();
    stopButton->setEnabled(false);
    startButton->setEnabled(false);
    openButton->setEnabled(true);
}

void FromVideoToPictureWindow::slotFinish(QString name)
{
    qDebug()<<"save image:"<<name;
    stopButton->setEnabled(false);
    startButton->setEnabled(false);
    openButton->setEnabled(true);
}

void FromVideoToPictureWindow::init()
{
    videoProcess=std::shared_ptr<VideoProcess>(new VideoProcess());
    saveImage=new SaveImageThread();
    path="";
}

void FromVideoToPictureWindow::initUI()
{
    mainLayout=new QVBoxLayout();

    QHBoxLayout *layout1=new QHBoxLayout();
    isAllSaveBox=new QCheckBox(tr("是否全部转换为图片"));
    isAllSaveBox->setChecked(true);

    postLabel=new QLabel(tr("保存图片的格式："));
    postBox=new QComboBox();
    postBox->addItem(".png");
    postBox->addItem(".jpg");

    layout1->addWidget(isAllSaveBox);
    layout1->addWidget(postLabel);
    layout1->addWidget(postBox);

    QHBoxLayout *layout2=new QHBoxLayout();
    layout2->setSpacing(50);
    startLabel=new QLabel(tr("视频开始转换时间："));
    startPosBox=new QSpinBox();
    startPosBox->setSuffix("s");
    startPosBox->setMinimum(0);
    startPosBox->setValue(0);

    stopLabel=new QLabel(tr("视频结束转换时间："));
    stopPosBox=new QSpinBox();
    stopPosBox->setSuffix("s");
    stopPosBox->setMinimum(0);
    stopPosBox->setValue(0);

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
    startButton=new QPushButton(tr("开始转换"));
    stopButton=new QPushButton(tr("结束转换"));
    startButton->setEnabled(false);
    stopButton->setEnabled(false);

    layout4->addWidget(startButton);
    layout4->addWidget(stopButton);

    mainLayout->addLayout(layout1);
    mainLayout->addLayout(layout2);
    mainLayout->addLayout(layout3);
    mainLayout->addLayout(layout4);

    this->setLayout(mainLayout);
}

void FromVideoToPictureWindow::initConnect()
{
    connect(openButton,&QPushButton::clicked,this,&FromVideoToPictureWindow::slotOpen);
    connect(startButton,&QPushButton::clicked,this,&FromVideoToPictureWindow::slotStart);
    connect(stopButton,&QPushButton::clicked,this,&FromVideoToPictureWindow::slotStop);
    connect(saveImage,&SaveImageThread::signalFinish,this,&FromVideoToPictureWindow::slotFinish);
}
