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

public:
    static Scanner* getInstance(void);
    int saveInCorrectFormat(int code);

protected:
    void run() override;

signals:
    /**
     * @brief ChipScanned
     * emits when a chip was scanned
     * @param rfid
     * scanned RFID
     */
    void ChipScanned(QString rfid);

    /**
     * @brief logMessage
     * emits to log a certain event
     * @param msg
     * logging message
     * @param index
     * specifies which file it should be logged in
     */
    void logMessage(QString msg, int index);

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
