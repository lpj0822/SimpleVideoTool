#include "imagesamplesmakethread.h"

ImageSamplesMakeThread::ImageSamplesMakeThread()
{
    init();
}

ImageSamplesMakeThread::~ImageSamplesMakeThread()
{
    if(dirProcess)
    {
        delete dirProcess;
        dirProcess = NULL;
    }
}

void ImageSamplesMakeThread::run()
{
    while(isStart)
    {
        switch(type)
        {
        case 0:
            {
                QString reDir=dirName+"/temp";
                if(isUseSuffix)
                {
                    dirProcess->modifyDirFileName(dirName,reDir,suffix);
                    emit signalFinish(dirName);
                }
                else
                {
                    dirProcess->modifyDirFileName(dirName,reDir);
                    emit signalFinish(dirName);
                }
            }
            break;
        case 1:
            if(isUseSuffix)
            {
                dirProcess->createInfoPos(dirName,suffix);
                emit signalFinish(dirName);
            }
            else
            {
                dirProcess->createInfoPos(dirName);
                emit signalFinish(dirName);
            }
            break;
        case 2:
            if(isUseSuffix)
            {
                dirProcess->createInfoNeg(dirName,suffix);
                emit signalFinish(dirName);
            }
            else
            {
                dirProcess->createInfoNeg(dirName);
                emit signalFinish(dirName);
            }
            break;
        }
        isStart=false;
    }
}

int ImageSamplesMakeThread::initImageSampleData(const QString &fileNameDir,bool isUse,QString fileSuffix,int type)
{
    this->dirName=fileNameDir;
    this->isUseSuffix=isUse;
    this->suffix=fileSuffix;
    this->type=type;
    return 0;
}

//开始线程
void ImageSamplesMakeThread::startThread()
{
    isStart=true;
}

//结束线程
void ImageSamplesMakeThread::stopThread()
{
    isStart=false;
}

void ImageSamplesMakeThread::init()
{
    dirProcess=new DirProcess();

    dirName="";//保存的文件名
    isUseSuffix=false;
    suffix="";
    type=-1;

    isStart=false;
}
