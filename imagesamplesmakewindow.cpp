#pragma execution_character_set("utf-8")
#include "imagesamplesmakewindow.h"
#include <QHBoxLayout>
#include <QFileDialog>
#include <QDebug>


ImageSamplesMakeWindow::ImageSamplesMakeWindow(QWidget *parent) : QWidget(parent)
{
    init();
    initUI();
    initConnect();
}

ImageSamplesMakeWindow::~ImageSamplesMakeWindow()
{
    if(imageSamplesMake)
    {
        imageSamplesMake->stopThread();
        imageSamplesMake->wait();
        delete imageSamplesMake;
        imageSamplesMake=NULL;
    }
}

void ImageSamplesMakeWindow::slotPath()
{
    pathDir=QFileDialog::getExistingDirectory(this, tr("选择文件夹"),".",QFileDialog::ShowDirsOnly);
    this->pathText->setText(pathDir);
    if(pathDir.trimmed().isEmpty())
    {
        qDebug()<<"打开的文件路径有误:"<<pathDir<<endl;
        return;
    }
    modifyButton->setEnabled(true);
    imageInfoPosButton->setEnabled(true);
    imageInfoNegButton->setEnabled(true);
    cancelButton->setEnabled(false);
}

void ImageSamplesMakeWindow::slotModify()
{
    imageSamplesMake->initImageSampleData(pathDir,isUsePost->isChecked(),postBox->currentText(),0);
    imageSamplesMake->startThread();
    imageSamplesMake->start();
    modifyButton->setEnabled(false);
    imageInfoPosButton->setEnabled(false);
    imageInfoNegButton->setEnabled(false);
    cancelButton->setEnabled(false);
}

void ImageSamplesMakeWindow::slotCreateInfoPos()
{
    imageSamplesMake->initImageSampleData(pathDir,isUsePost->isChecked(),postBox->currentText(),1);
    imageSamplesMake->startThread();
    imageSamplesMake->start();
    modifyButton->setEnabled(false);
    imageInfoPosButton->setEnabled(false);
    imageInfoNegButton->setEnabled(false);
    cancelButton->setEnabled(false);
}

void ImageSamplesMakeWindow::slotCreateInfoNeg()
{
    imageSamplesMake->initImageSampleData(pathDir,isUsePost->isChecked(),postBox->currentText(),2);
    imageSamplesMake->startThread();
    imageSamplesMake->start();
    modifyButton->setEnabled(false);
    imageInfoPosButton->setEnabled(false);
    imageInfoNegButton->setEnabled(false);
    cancelButton->setEnabled(false);
}

void ImageSamplesMakeWindow::slotFinish(QString name)
{
    qDebug()<<"save image:"<<name;
    modifyButton->setEnabled(true);
    imageInfoPosButton->setEnabled(true);
    imageInfoNegButton->setEnabled(true);
    cancelButton->setEnabled(false);
}

void ImageSamplesMakeWindow::slotCancel()
{
    imageSamplesMake->stopThread();
}

void ImageSamplesMakeWindow::init()
{
    imageSamplesMake=new ImageSamplesMakeThread();
    pathDir="";
}

void ImageSamplesMakeWindow::initUI()
{
    mainLayout=new QVBoxLayout();

    QHBoxLayout *layout=new QHBoxLayout();
    isUsePost=new QCheckBox(tr("是否使用图像后缀过滤"));
    isUsePost->setChecked(true);
    postLabel=new QLabel(tr("图片格式："));
    postBox=new QComboBox();
    postBox->addItem(tr("*.png"));
    postBox->addItem(tr("*.jpg"));
    postBox->addItem(tr("*.gif"));

    layout->addWidget(isUsePost);
    layout->addWidget(postLabel);
    layout->addWidget(postBox);

    QHBoxLayout *layout1=new QHBoxLayout();
    layout1->setSpacing(10);
    pathText=new QLineEdit();
    pathText->setReadOnly(true);
    pathButton=new QPushButton(tr("打开文件夹"));
    layout1->addWidget(pathText);
    layout1->addWidget(pathButton);

    QHBoxLayout *layout2=new QHBoxLayout();
    modifyButton=new QPushButton(tr("修改文件名"));
    imageInfoPosButton=new QPushButton(tr("生成正样本描述文件"));
    imageInfoNegButton=new QPushButton(tr("生成负样本描述文件"));
    cancelButton=new QPushButton(tr("停止"));

    modifyButton->setEnabled(false);
    imageInfoPosButton->setEnabled(false);
    imageInfoNegButton->setEnabled(false);
    cancelButton->setEnabled(false);

    layout2->setSpacing(30);
    //layout->setAlignment(Qt::AlignCenter);
    layout2->addWidget(modifyButton);
    layout2->addWidget(imageInfoPosButton);
    layout2->addWidget(imageInfoNegButton);
    layout2->addWidget(cancelButton);

    mainLayout->setMargin(10);
    mainLayout->addLayout(layout);
    mainLayout->addLayout(layout1);
    mainLayout->addLayout(layout2);

    this->setLayout(mainLayout);
}

void ImageSamplesMakeWindow::initConnect()
{
    connect(pathButton,&QPushButton::clicked,this,&ImageSamplesMakeWindow::slotPath);
    connect(modifyButton,&QPushButton::clicked,this,&ImageSamplesMakeWindow::slotModify);
    connect(imageInfoPosButton,&QPushButton::clicked,this,&ImageSamplesMakeWindow::slotCreateInfoPos);
    connect(imageInfoNegButton,&QPushButton::clicked,this,&ImageSamplesMakeWindow::slotCreateInfoNeg);
    connect(cancelButton,&QPushButton::clicked,this,&ImageSamplesMakeWindow::slotCancel);
    connect(imageSamplesMake,&ImageSamplesMakeThread::signalFinish,this,&ImageSamplesMakeWindow::slotFinish);
}
