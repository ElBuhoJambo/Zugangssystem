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
    /**
     * @brief Result
     * emits the results of the query to look for certain worker
     * @param access
     * access status
     * @param RFID
     * scanned RFID
     * @param loc
     * location of scan
     * @param name
     * name of worker
     */
    void Result(QString RFID, QString name);

    /**
     * @brief ShowTable
     * emits the results of the query to fill the table
     * @param name
     * name of a worker
     * @param loc
     * location of a worker
     * @param RFID
     * RFID of a worker
     * @param access
     * access status of a worker
     */
    void ShowTable(QString name, QString loc, QString RFID, QString access);

    /**
     * @brief DeleteRow
     * emits to delete a worker in the table
     * @param RFID
     * deleted RFID
     */
    void DeleteRow(QString RFID);

    /**
     * @brief UpdateWorker
     * emits to update a worker in the table
     * @param RFID
     * updated RFID
     * @param location
     * updated location
     * @param name
     * updated name
     * @param access
     * updated access status
     * @param currRFID
     * old RFID
     */
    void UpdateWorker(QString RFID, QString location, QString name, QString access, QString currRFID);

    /**
     * @brief GetNames
     * emits to send all names of the worker
     * @param names
     * every name in a list
     */
    void GetNames(QStringList names);

    /**
     * @brief logMessage
     * emits to log a certain event
     * @param msg
     * logging message
     * @param index
     * specifies which file it should be logged in
     */
    void logMessage(QString msg, int index);

public slots:
    void receiveRequest(QString RFID, QString loc);
    void showTable();
    void addWorker(QString userId, QString RFID, QString name, QList<int> groups);
    void deleteWorker(QString userId);
    void updateWorker(QString currUserId, QString userId, QString RFID, QString name, QList<int> groups, QString active);
    void getNames();

    //constructor and instance for use in other classes, and the database variable
private:
    sqlCheck();
    static sqlCheck* sInstance;
    QSqlDatabase sDB;
};

#endif // SQLCHECK_H
