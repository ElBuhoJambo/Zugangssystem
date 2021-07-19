#ifndef SQLCHECK_H
#define SQLCHECK_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

#include "logging.h"

class sqlCheck : public QObject
{
    Q_OBJECT

public:
    static sqlCheck* getInstance(void);
    bool isOpen();
    QStringList request(QString RFID, QString loc);

signals:
    void Result(bool access, QString RFID, QString loc, QString name);
    void ShowTable(QString name, QString loc, QString RFID, QString access);
    void DeleteRow(QString RFID);
    void UpdateWorker(QString RFID, QString location, QString name, QString access, QString currRFID);
    void logMessage(QString msg, int index);

public slots:
    void receiveRequest(QString RFID, QString loc);
    void showTable();
    void addWorker(QString RFID, QString location, QString name, QString access);
    void deleteWorker(QString RFID);
    void updateWorker(QString RFID, QString location, QString name, QString access, QString currRFID);

private:
    sqlCheck();
    static sqlCheck* sInstance;
    QSqlDatabase sDB;
};

#endif // SQLCHECK_H
