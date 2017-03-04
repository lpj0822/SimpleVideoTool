#pragma execution_character_set("utf-8")
#include "qcamerawindow.h"
#include <QPixmap>

QCameraWindow::QCameraWindow(QWidget *parent) : QWidget(parent)
{
    init();
    initUI();
    initConnect();
}

QCameraWindow::~QCameraWindow()
{

}

void QCameraWindow::openCameraSlot()
{
    camera = new QCamera(cameras[cameraInfoBox->currentData().toInt()]);
    camera->setCaptureMode(QCamera::CaptureViewfinder);
    camera->setViewfinder(viewfinder);
    //camera->setViewfinderSettings(viewfinderSettings);
    imageCapture=new QCameraImageCapture(camera);
    connect(imageCapture,&QCameraImageCapture::imageCaptured,this,&QCameraWindow::saveImage);

    viewfinder->show();
    camera->start();

    startCameraButton->setEnabled(false);
    captureButton->setEnabled(true);
    exitButton->setEnabled(true);
}

void QCameraWindow::captrueSlot()
{
    imageCapture->capture();
}

void QCameraWindow::exitSlot()
{
    if(camera)
    {
        if(camera->isAvailable())
        {
            camera->stop();
        }
    }
    startCameraButton->setEnabled(true);
    captureButton->setEnabled(false);
    exitButton->setEnabled(false);
}

void QCameraWindow::saveImage(int id, QImage image)
{
    QString fileName="./image.png";
    qDebug()<<"id:"<<id;
    image.save(fileName);
}

void QCameraWindow::init()
{
    viewfinder=new QCameraViewfinder(this);
    viewfinder->setFixedSize(640,480);

    viewfinderSettings.setResolution(640, 480);
    viewfinderSettings.setMinimumFrameRate(15.0);
    viewfinderSettings.setMaximumFrameRate(30.0);

    camera=NULL;
    imageCapture=NULL;
}

void QCameraWindow::initUI()
{
    int count=0;
    cameraInfoLabel=new QLabel(tr("摄像头列表："));
    cameraInfoBox=new QComboBox();
    cameras = QCameraInfo::availableCameras();
    foreach (const QCameraInfo &cameraInfo, cameras)
    {
        cameraInfoBox->addItem(cameraInfo.deviceName(),count);
        count++;
    }

    QHBoxLayout *topLayout=new QHBoxLayout();
    topLayout->setAlignment(Qt::AlignCenter);
    topLayout->addWidget(cameraInfoLabel);
    topLayout->addWidget(cameraInfoBox);

    scrollArea = new QScrollArea;
    scrollArea->setAlignment(Qt::AlignCenter);
    scrollArea->setBackgroundRole(QPalette::Dark);
    scrollArea->setWidget(viewfinder);
    viewfinder->show();

    startCameraButton = new QPushButton(tr("打开摄像头"));
    startCameraButton->setEnabled(false);
    captureButton=new QPushButton(tr("拍照"));
    captureButton->setEnabled(false);
    exitButton=new QPushButton(tr("关闭"));
    exitButton->setEnabled(false);

    QHBoxLayout *bottomLayout=new QHBoxLayout();
    bottomLayout->setSpacing(50);
    bottomLayout->setAlignment(Qt::AlignCenter);
    bottomLayout->addWidget(startCameraButton);
    bottomLayout->addWidget(captureButton);
    bottomLayout->addWidget(exitButton);

    mainLayout=new QVBoxLayout();//主布局
    mainLayout->addLayout(topLayout);
    mainLayout->addWidget(scrollArea);
    mainLayout->addLayout(bottomLayout);

    this->setLayout(mainLayout);

    if (cameras.size() > 0)
    {
        startCameraButton->setEnabled(true);
    }
}

void QCameraWindow::initConnect()
{
    connect(startCameraButton, &QPushButton::clicked, this, &QCameraWindow::openCameraSlot);
    connect(captureButton, &QPushButton::clicked, this, &QCameraWindow::captrueSlot);
    connect(exitButton, &QPushButton::clicked, this, &QCameraWindow::exitSlot);
}
