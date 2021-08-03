#ifndef SCANNER_H
#define SCANNER_H

#include <QObject>
#include <QThread>
#include <QTimer>
#include <QDebug>
#include <QString>
#include <QFile>
#include <QSocketNotifier>

#include "logging.h"

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

    //function to access class in any other class
public:
    static Scanner* getInstance(void);
    int saveInCorrectFormat(int code);

    //run function for thread
protected:
    void run() override;

    //signals for sending the scanned RFID,
    //and logging
signals:
    void ChipScanned(QString rfid);
    void logMessage(QString msg, int index);

    //slots for handling the input events,
    //and checking on the scanner
private slots:
    void handleNotification(int socket);
    void checkScannerData();

    //constructor and instance for use in other classes,
    //and initializing the timer for checking on the scanner
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
