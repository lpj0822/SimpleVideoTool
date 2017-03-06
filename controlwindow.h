#ifndef CONTROLWINDOW_H
#define CONTROLWINDOW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QTabWidget>
#include <QDialogButtonBox>
#include "frompicturetovideowindow.h"
#include "fromvideotopicturewindow.h"
#include "fromvideotoscreenshotwindow.h"
#include "videocroppingwindow.h"
#include "imagesamplesmakewindow.h"
#include "qcamerawindow.h"
#include "imageconverterwindow.h"

class ControlWindow : public QWidget
{
    Q_OBJECT

public:
    ControlWindow(QWidget *parent = 0);
    ~ControlWindow();

signals:

public slots:
    void slotOK();//点击确定

private:

    QVBoxLayout *mainLayout;//布局
    QTabWidget *tabweight;//tab
    QDialogButtonBox *buttonBox;

    FromPictureToVideoWindow *pictureToVideoWindow;
    FromVideoToPictureWindow *videoToPictureWindow;
    FromVideoToScreenshotWindow *videoToScreenshotWindow;
    VideoCroppingWindow* videoCroppingWindow;
    ImageSamplesMakeWindow *imageSamplesMakeWindow;
    QCameraWindow *qcameraWindow;
    ImageConverterWindow *imageConverterWindow;

    void init();
    void initUI();
    void initConnect();
};

#endif // CONTROLWINDOW_H
