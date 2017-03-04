#ifndef DIRPROCESS_H
#define DIRPROCESS_H

#include <QObject>
#include <QObject>
#include <QList>
#include <QString>

class DirProcess : public QObject
{
    Q_OBJECT
public:
    DirProcess(QObject *parent = 0);
    ~DirProcess();

    QList<QString> getDirFileName(const QString& pathDir);
	//filter << "*.jpg";
    QList<QString> getDirFileName(const QString &pathDir,QString filterPostfix);

    void modifyDirFileName(const QString &pathDir,const QString &rePathDir);
    void modifyDirFileName(const QString &pathDir,const QString &rePathDir,QString filterPostfix);

    void createInfoPos(const QString &pathDir);
    void createInfoPos(const QString &pathDir,QString filterPostfixconst);
    void createInfoNeg(const QString &pathDir);
    void createInfoNeg(const QString &pathDir,QString filterPostfix);

    std::string toNumberStr(const int number,const int width);

signals:

public slots:

};

#endif // DIRPROCESS_H
