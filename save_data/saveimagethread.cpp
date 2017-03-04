#pragma execution_character_set("utf-8")
#include "saveimagethread.h"
#include <QDir>
#include <iostream>

SaveImageThread::SaveImageThread()
{
    init();
}

SaveImageThread::~SaveImageThread()
{

}

void SaveImageThread::run()
{
    int frameCount=0;
    cv::Mat frame;
    int errCode=0;
    QString fileName;
    while (isStart)
    {
        if(videoProcess->isOpen())
        {
            if(videoProcess->getFramePosition()<=stopFrame)
            {
                errCode=videoProcess->readFrame(frame);
                if(errCode==0)
                {
                    fileName=dirName+"/img"+QString::fromStdString(dirProcess.toNumberStr(frameCount,widthStr))+imagePost;
                    myImageWrite.saveImage(frame, fileName.toStdString());
                    frameCount++;
                }
                else
                {
                    isStart=false;
                    emit signalFinish(dirName);
                }
            }
            else
            {
                isStart=false;
                emit signalFinish(dirName);
            }
        }
    }
    videoProcess->closeVideo();
}

//初始化保存数据参数
int SaveImageThread::initSaveImageData(const QString &fileNameDir,QString imagePost,std::shared_ptr<VideoProcess> video,bool isAll,int startPos,int stopPos)
{
    QDir makeDir;
    if(video._Get()&&video->isOpen())
    {
        if(isAll)
        {
            this->startFrame=0;
            this->stopFrame=video->getFrameCount();
            video->setFramePosition(0);
            this->videoProcess=video;
            this->dirName=fileNameDir+"/temp"+QString::number(dirNumber);
            if(makeDir.exists(dirName))
            {
                dirNumber++;
                this->dirName=fileNameDir+"/temp"+QString::number(dirNumber);
            }
            if(!makeDir.exists(dirName))
            {
                if(!makeDir.mkdir(dirName))
                {
                    std::cout<<"make dir fail!"<<std::endl;
                    return -11;
                }
            }
            std::cout<<"fileName:"<<dirName.toStdString()<<std::endl;
        }
        else
        {
            this->startFrame=startPos*video->getFrameFPS();
            this->stopFrame=stopPos*video->getFrameFPS();
            video->setFramePosition(startFrame);
            this->videoProcess=video;
            this->dirName=fileNameDir+"/temp"+QString::number(dirNumber);
            if(makeDir.exists(dirName))
            {
                dirNumber++;
                this->dirName=fileNameDir+"/temp"+QString::number(dirNumber);
            }
            if(!makeDir.exists(dirName))
            {
                if(!makeDir.mkdir(dirName))
                {
                    std::cout<<"make dir fail!"<<std::endl;
                    return -11;
                }
            }
            std::cout<<"fileName:"<<dirName.toStdString()<<std::endl;
        }
        this->imagePost=imagePost;
        this->widthStr=QString::number(stopFrame).length();
        return 0;
    }
    else
    {
        return -1;
    }
}

//开始线程
void SaveImageThread::startThread()
{
    isStart=true;
}

//结束线程
void SaveImageThread::stopThread()
{
    isStart=false;
}

void SaveImageThread::init()
{
    videoProcess=nullptr;

    dirName="";//保存的文件名
    imagePost=".png";
    dirNumber=0;

    startFrame=0;
    stopFrame=0;

    isStart=false;

    widthStr=1;
}
