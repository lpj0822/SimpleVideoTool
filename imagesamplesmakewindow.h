#ifndef IMAGESAMPLESMAKEWINDOW_H
#define IMAGESAMPLESMAKEWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QCheckBox>
#include <QComboBox>
#include <QLabel>
#include <QVBoxLayout>
#include "imagesamplesmakethread.h"

class ImageSamplesMakeWindow : public QWidget
{
    Q_OBJECT
public:
    ImageSamplesMakeWindow(QWidget *parent = 0);
    ~ImageSamplesMakeWindow();

signals:

public slots:
    void slotPath();
    void slotModify();
    void slotCreateInfoPos();
    void slotCreateInfoNeg();
    void slotCancel();
    void slotFinish(QString name);

private:
    QVBoxLayout *mainLayout;
    QPushButton *modifyButton;
    QPushButton *cancelButton;
    QPushButton *imageInfoPosButton;
    QPushButton *imageInfoNegButton;
    QPushButton *pathButton;
    QLineEdit *pathText;

    QCheckBox *isUsePost;
    QLabel *postLabel;
    QComboBox *postBox;

    ImageSamplesMakeThread *imageSamplesMake;
    QString pathDir;

    void init();
    void initUI();
    void initConnect();

};

#endif // IMAGESAMPLESMAKEWINDOW_H
