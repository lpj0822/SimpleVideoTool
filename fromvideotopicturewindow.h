#ifndef FROMVIDEOTOPICTUREWINDOW_H
#define FROMVIDEOTOPICTUREWINDOW_H

#include <QWidget>
#include <QSpinBox>
#include <QCheckBox>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QString>
#include <memory>
#include "save_data/saveimagethread.h"
#include "utility/videoprocess.h"

class FromVideoToPictureWindow : public QWidget
{
    Q_OBJECT
public:
    FromVideoToPictureWindow(QWidget *parent = 0);
    ~FromVideoToPictureWindow();

signals:

public slots:
    void slotOpen();
    void slotStart();
    void slotStop();
    void slotFinish(QString name);

private:

    QVBoxLayout* mainLayout;

    QCheckBox* isAllSaveBox;
    QLabel* startLabel;
    QLabel* stopLabel;
    QSpinBox* startPosBox;
    QSpinBox* stopPosBox;
    QLabel* postLabel;
    QComboBox* postBox;

    QLineEdit *pathText;
    QPushButton* openButton;
    QPushButton* startButton;
    QPushButton* stopButton;

    std::shared_ptr<VideoProcess> videoProcess;
    SaveImageThread* saveImage;

    QString path;

    void init();
    void initUI();
    void initConnect();

};

#endif // FROMVIDEOTOPICTUREWINDOW_H
