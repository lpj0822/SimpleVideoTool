#pragma execution_character_set("utf-8")
#include "controlwindow.h"
#include <QHBoxLayout>
#include <QFileDialog>
#include <QDebug>

ControlWindow::ControlWindow(QWidget *parent)
    : QWidget(parent)
{
    init();
    initUI();
    initConnect();
}

ControlWindow::~ControlWindow()
{

}

void ControlWindow::slotOK()
{

}

void ControlWindow::init()
{

}

void ControlWindow::initUI()
{
    tabweight=new QTabWidget();

    pictureToVideoWindow=new FromPictureToVideoWindow();
    videoToPictureWindow=new FromVideoToPictureWindow();
    videoToScreenshotWindow=new FromVideoToScreenshotWindow();
    videoCroppingWindow=new VideoCroppingWindow();
    imageSamplesMakeWindow=new ImageSamplesMakeWindow();
    qcameraWindow=new QCameraWindow();
    imageConverterWindow = new ImageConverterWindow();

    tabweight->addTab(pictureToVideoWindow,tr("一系列图片转为视频"));
    tabweight->addTab(videoToPictureWindow,tr("视频转换为一系列图片"));
    tabweight->addTab(videoToScreenshotWindow,tr("从视频中截图"));
    tabweight->addTab(videoCroppingWindow,tr("视频剪辑"));
    tabweight->addTab(imageSamplesMakeWindow,tr("图像样本自作"));
    tabweight->addTab(qcameraWindow,tr("摄像头操作"));
    tabweight->addTab(imageConverterWindow, tr("图片格式转换器"));

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel); // 创建QDialogButtonBox
    buttonBox->button(QDialogButtonBox::Ok)->setText(tr("确定"));//将buttonbox中的ok 变成汉化
    buttonBox->button(QDialogButtonBox::Cancel)->setText(tr("取消"));

    mainLayout=new QVBoxLayout();
    mainLayout->addWidget(tabweight);
    mainLayout->addWidget(buttonBox);

    this->setLayout(mainLayout);
    this->setMinimumSize(700,520);
    this->setWindowTitle(tr("视频简单处理工具"));
}

void ControlWindow::initConnect()
{
    connect(buttonBox,&QDialogButtonBox::accepted, this, &ControlWindow::slotOK);  // 为button定义连接信号槽
    connect(buttonBox, &QDialogButtonBox::rejected, this, &ControlWindow::close);
}
