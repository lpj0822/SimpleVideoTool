#ifndef QCAMERAWINDOW_H
#define QCAMERAWINDOW_H

#include <QWidget>
#include <QCamera>
#include <QCameraInfo>
#include <QCameraViewfinder>
#include <QCameraViewfinderSettings>
#include <QCameraImageCapture>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QImage>

class QCameraWindow : public QWidget
{
    Q_OBJECT
public:
    QCameraWindow(QWidget *parent = 0);
    ~QCameraWindow();

signals:

public slots:
    void openCameraSlot();
    void captrueSlot();
    void saveImage(int,QImage);
    void exitSlot();

private:

    QLabel *cameraInfoLabel;
    QComboBox *cameraInfoBox;
    QPushButton *startCameraButton;
    QPushButton *captureButton;
    QPushButton *exitButton;
    QScrollArea *scrollArea;//滚动区域

    QVBoxLayout *mainLayout;//主布局

    QCamera *camera;
    QCameraViewfinder *viewfinder;
    QCameraViewfinderSettings viewfinderSettings;
    QCameraImageCapture *imageCapture;
    QList<QCameraInfo> cameras;

    void init();
    void initUI();
    void initConnect();
};

#endif // QCAMERAWINDOW_H
