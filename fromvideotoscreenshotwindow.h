#ifndef FROMVIDEOTOSCREENSHOTWINDOW_H
#define FROMVIDEOTOSCREENSHOTWINDOW_H

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
#include "utility/videoprocess.h"
#include "save_data/savescreenshotthread.h"

class FromVideoToScreenshotWindow : public QWidget
{
    Q_OBJECT
public:
    FromVideoToScreenshotWindow(QWidget *parent = 0);
    ~FromVideoToScreenshotWindow();

signals:

public slots:
    void slotOpen();
    void slotStart();
    void slotStop();
    void slotFinish(QString name);

private:

    QVBoxLayout* mainLayout;

    QCheckBox* isAllSaveBox;
    QLabel* postLabel;
    QComboBox* postBox;
    QLabel* spaceLabel;
    QSpinBox* spaceBox;
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
    SaveScreenshotThread *saveScreenshot;

    QString path;

    void init();
    void initUI();
    void initConnect();

};

#endif // FROMVIDEOTOSCREENSHOTWINDOW_H
