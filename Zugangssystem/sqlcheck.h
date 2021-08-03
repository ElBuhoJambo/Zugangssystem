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

    //functions to access class in any other class,
    //checking if the database is open,
    //and checking for a certain RFID in the database
public:
    static sqlCheck* getInstance(void);
    bool isOpen();
    QStringList request(QString RFID, QString loc);

    //signals for sending the results of one worker,
    //sending the whole table one after the other,
    //deleting a specific worker,
    //updating a certain worker,
    //sending every name of all worker,
    //and logging
signals:
    void Result(bool access, QString RFID, QString loc, QString name);
    void ShowTable(QString name, QString loc, QString RFID, QString access);
    void DeleteRow(QString RFID);
    void UpdateWorker(QString RFID, QString location, QString name, QString access, QString currRFID);
    void GetNames(QStringList names);
    void logMessage(QString msg, int index);

    //slots for receiving the request and start it,
    //querying to get the whole database,
    //querying to add a worker,
    //querying to delete a worker,
    //querying to update a worker,
    //and querying to get all names
public slots:
    void receiveRequest(QString RFID, QString loc);
    void showTable();
    void addWorker(QString RFID, QString location, QString name, QString access);
    void deleteWorker(QString RFID);
    void updateWorker(QString RFID, QString location, QString name, QString access, QString currRFID);
    void getNames();

    //constructor and instance for use in other classes, and the database variable
private:
    sqlCheck();
    static sqlCheck* sInstance;
    QSqlDatabase sDB;
};

#endif // SQLCHECK_H
