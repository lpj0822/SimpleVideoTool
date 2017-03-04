#ifndef VIDEOCROPPINGWINDOW_H
#define VIDEOCROPPINGWINDOW_H

#include <QWidget>
#include <QSpinBox>
#include <QCheckBox>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QString>
#include <memory>
#include "utility/videoprocess.h"
#include "croppingvideothread.h"

class VideoCroppingWindow : public QWidget
{
    Q_OBJECT
public:
    VideoCroppingWindow(QWidget *parent = 0);
    ~VideoCroppingWindow();

signals:

public slots:
    void slotOpen();
    void slotStart();
    void slotStop();
    void slotFinish(QString name);

private:

    QVBoxLayout* mainLayout;

    QCheckBox* isAllCropBox;

    QLabel* scaleSizeLabel;
    QDoubleSpinBox *scaleSizeBox;//缩放尺寸输入
    QLabel* startLabel;
    QLabel* stopLabel;
    QSpinBox* startPosBox;
    QSpinBox* stopPosBox;

    QLineEdit *pathText;
    QPushButton* openButton;
    QPushButton* startButton;
    QPushButton* stopButton;

    QLabel* infoLabel;

    std::shared_ptr<VideoProcess> videoProcess;
    CroppingVideoThread *croppingVideo;

    QString path;

    void init();
    void initUI();
    void initConnect();
};

#endif // VIDEOCROPPINGWINDOW_H
