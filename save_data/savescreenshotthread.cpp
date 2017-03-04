#pragma execution_character_set("utf-8")
#include "savescreenshotthread.h"
#include <opencv2/imgproc.hpp>
#include <QDir>
#include <iostream>

cv::Mat frame;
cv::Mat dst,img,tmp;
char key;

void on_mouse(int event,int x,int y,int flags,void *ustc)//event鼠标事件代号，x,y鼠标坐标，flags拖拽和键盘操作的代号
{
    static cv::Point pre_pt = (-1,-1);//初始坐标
    static cv::Point cur_pt = (-1,-1);//实时坐标
    char temp[16];
    if (event == CV_EVENT_LBUTTONDOWN)//左键按下，读取初始坐标，并在图像上该点处划圆
    {
        frame.copyTo(img);//将原始图片复制到img中
        sprintf(temp,"(%d,%d)",x,y);
        pre_pt = cv::Point(x,y);
        cv::putText(img,temp,pre_pt,cv::FONT_HERSHEY_SIMPLEX,0.5,cv::Scalar(0,0,0,255),1,8);//在窗口上显示坐标
        cv::circle(img,pre_pt,2,cv::Scalar(255,0,0,0),CV_FILLED,CV_AA,0);//划圆
        cv::imshow("img",img);
    }
    else if (event == CV_EVENT_MOUSEMOVE && !(flags & CV_EVENT_FLAG_LBUTTON))//左键没有按下的情况下鼠标移动的处理函数
    {
        img.copyTo(tmp);//将img复制到临时图像tmp上，用于显示实时坐标
        sprintf(temp,"(%d,%d)",x,y);
        cur_pt = cv::Point(x,y);
        cv::putText(tmp,temp,cur_pt,cv::FONT_HERSHEY_SIMPLEX,0.5,cv::Scalar(0,0,0,255));//只是实时显示鼠标移动的坐标
        cv::imshow("img",tmp);
    }
    else if (event == CV_EVENT_MOUSEMOVE && (flags & CV_EVENT_FLAG_LBUTTON))//左键按下时，鼠标移动，则在图像上划矩形
    {
        img.copyTo(tmp);
        sprintf(temp,"(%d,%d)",x,y);
        cur_pt = cv::Point(x,y);
        cv::putText(tmp,temp,cur_pt,cv::FONT_HERSHEY_SIMPLEX,0.5,cv::Scalar(0,0,0,255));
        cv::rectangle(tmp,pre_pt,cur_pt,cv::Scalar(0,255,0,0),1,8,0);//在临时图像上实时显示鼠标拖动时形成的矩形
        cv::imshow("img",tmp);
    }
    else if (event == CV_EVENT_LBUTTONUP)//左键松开，将在图像上划矩形
    {
        if(cur_pt.x>=0&&cur_pt.x<=frame.cols&&cur_pt.y>=0&&cur_pt.y<frame.rows)
        {
            frame.copyTo(img);
            sprintf(temp,"(%d,%d)",x,y);
            cur_pt = cv::Point(x,y);
            cv::putText(img,temp,cur_pt,cv::FONT_HERSHEY_SIMPLEX,0.5,cv::Scalar(0,0,0,255));
            cv::circle(img,pre_pt,2,cv::Scalar(255,0,0,0),CV_FILLED,CV_AA,0);
            cv::rectangle(img,pre_pt,cur_pt,cv::Scalar(0,255,0,0),1,8,0);//根据初始点和结束点，将矩形画到img上
            cv::imshow("img",img);
            img.copyTo(tmp);
            //截取矩形包围的图像，并保存到dst中
            int width = abs(pre_pt.x - cur_pt.x);
            int height = abs(pre_pt.y - cur_pt.y);
            if (width == 0 || height == 0)
            {
                printf("width == 0 || height == 0\n");
                return;
            }
            dst = frame(cv::Rect(cv::min(cur_pt.x,pre_pt.x),cv::min(cur_pt.y,pre_pt.y),width,height));
            cv::imshow("dst",dst);
            cv::moveWindow("dst",x,y);
            key = cv::waitKey(0);
        }


    }
}

SaveScreenshotThread::SaveScreenshotThread()
{
    init();
}

SaveScreenshotThread::~SaveScreenshotThread()
{

}

void SaveScreenshotThread::run()
{
    int frameCount=0;
    int errCode=0;
    QString fileName;
    int currentPos=videoProcess->getFramePosition();
    cv::namedWindow("img");//定义一个img窗口
    cv::setMouseCallback("img",on_mouse,0);//调用回调函数
    while (isStart)
    {
        if(videoProcess->isOpen())
        {
            if(currentPos<=stopFrame)
            {
                errCode=videoProcess->readFrame(frame);
                if(errCode==0&&!frame.empty())
                {
                    frame.copyTo(img);
                    cv::imshow("img",frame);
                    key = cv::waitKey(0);
                    switch(key)
                    {
                    case 'a':
                        currentPos=currentPos-spaceNumber;
                        if(currentPos<startFrame)
                        {
                            currentPos=startFrame;
                        }
                        break;
                    case 'd':
                         currentPos=currentPos+spaceNumber;
                         if(currentPos>stopFrame)
                         {
                             currentPos=stopFrame;
                         }
                        break;
                    case 'w':
                        {
                            fileName=dirName+"/img"+QString::fromStdString(dirProcess.toNumberStr(frameCount,widthStr))+imagePost;
                            myImageWrite.saveImage(dst, fileName.toStdString());
                            frameCount++;
                            cv::destroyWindow("dst");
                        }
                        break;
                    case 32:
                        cv::destroyWindow("dst");
                        break;
                    case 27:
                        isStart=false;
                        emit signalFinish(dirName);
                        break;
                    }
                    videoProcess->setFramePosition(currentPos);
                }
                else
                {
                    videoProcess->setFramePosition(currentPos-1);
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
int SaveScreenshotThread::initSaveScreenshotData(const QString &fileNameDir,QString imagePost,std::shared_ptr<VideoProcess> video,bool isAll,int space,int startPos,int stopPos)
{
    QDir makeDir;
    if(video._Get()&&video->isOpen())
    {
        if(isAll)
        {
            this->spaceNumber=space;
            this->startFrame=0;
            this->stopFrame=video->getFrameCount();
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
        else
        {
            this->spaceNumber=space;
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
void SaveScreenshotThread::startThread()
{
    isStart=true;
}

//结束线程
void SaveScreenshotThread::stopThread()
{
    isStart=false;
    cv::destroyAllWindows();
}

void SaveScreenshotThread::init()
{
    videoProcess=nullptr;

    dirName="";//保存的文件名
    imagePost=".png";
    dirNumber=0;

    spaceNumber=1;
    startFrame=0;
    stopFrame=0;

    isStart=false;

    widthStr=1;
}
