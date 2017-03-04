#ifndef IMAGESAMPLESMAKETHREAD_H
#define IMAGESAMPLESMAKETHREAD_H

#include <QThread>
#include "utility/dirprocess.h"

class ImageSamplesMakeThread : public QThread
{
    Q_OBJECT

public:
    ImageSamplesMakeThread();
    ~ImageSamplesMakeThread();

    int initImageSampleData(const QString &fileNameDir,bool isUse,QString fileSuffix,int type);

    void startThread();//开始线程
    void stopThread();//结束线程

signals:
    void signalFinish(QString name);

public slots:

protected:
    void run();

private:

    DirProcess *dirProcess;

    QString dirName;//保存的文件名
    bool isUseSuffix;
    QString suffix;
    int type;

    bool isStart;

    void init();
};

#endif // IMAGESAMPLESMAKETHREAD_H
