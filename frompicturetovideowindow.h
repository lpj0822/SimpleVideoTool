#ifndef FROMPICTURETOVIDEOWINDOW_H
#define FROMPICTURETOVIDEOWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QSpinBox>
#include <QLabel>
#include <QComboBox>
#include "utility/dirprocess.h"
#include "save_data/savevideothread.h"

class FromPictureToVideoWindow : public QWidget
{
    Q_OBJECT

public:
    FromPictureToVideoWindow(QWidget *parent = 0);
    ~FromPictureToVideoWindow();

public slots:
    void slotOpen();
    void slotStart();
    void slotStop();
    void slotFinish(QString name);

private:

    QVBoxLayout *mainLayout;
    QPushButton *openButton;
    QPushButton *startButton;
    QPushButton *stopButton;
    QLineEdit *pathText;
    QLabel *fpsLabel;
    QSpinBox *fpsBox;
    QLabel *postLabel;
    QComboBox *postBox;
    DirProcess dirProcess;
    SaveVideoThread* saveVideo;
    QList<QString> pathList;
    QString pathDir;

    void init();
    void initUI();
    void initConnect();
};

#endif // FROMPICTURETOVIDEOWINDOW_H
