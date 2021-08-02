#ifndef SCANNER_H
#define SCANNER_H

#include <QObject>
#include <QThread>
#include <QTimer>
#include <QDebug>
#include <QString>
#include <QFile>
#include <QSocketNotifier>

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/input.h>

class Scanner : public QThread
{
    Q_OBJECT

public:
    static Scanner* getInstance(void);
    int saveInCorrectFormat(int code);

protected:
    void run() override;

signals:
    void ChipScanned(QString rfid);

private slots:
    void handleNotification(int socket);
    void checkScannerData();

private:
    Scanner(QObject *parent = 0);
    ~Scanner();

    void initScanner(void);

    static Scanner* sInstance;
    QString defaultPath = "/dev/input/event2";
    QString rfid;
    QTimer* sCheckScanner;
    QFile *sScannerFile;
    QSocketNotifier *sNotifier;
    int fd;
    bool notificationEnabled;
    struct input_event event;
    int RFID[10];
    int i = 0;
    int buffer = 0;
};

#endif // SCANNER_H
