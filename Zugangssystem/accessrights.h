#ifndef ACCESSRIGHTS_H
#define ACCESSRIGHTS_H

#include <QObject>
#include <QDebug>

#include "logging.h"


class accessRights : public QObject
{
    Q_OBJECT

public:
    static accessRights* getInstance(void);

signals:
    /**
     * @brief SQLRequest
     * emits the request for the database to query the scanned chip
     * @param RFID
     * scanned RFID
     * @param loc
     * location of scan
     */
    void SQLRequest(QString RFID, QString loc);

    /**
     * @brief Visual
     * emits the data of the database query for visual output
     * @param RFID
     * scanned RFID
     * @param loc
     * location of scan
     * @param access
     * access status at location
     */
    void Visual(QString RFID, QString loc, bool access);

    /**
     * @brief Door
     * emits the data of the database query for the doorlock handling
     * @param access
     * access status at location
     * @param loc
     * location of scan
     */
    void Door(bool access, QString loc);

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
    void checkAccess(QString RFID, QString loc);
    void receiveResult(bool access, QString RFID, QString loc, QString name);

    //constructor and instance for use in other classes
private:
    accessRights();
    static accessRights* aInstance;
};

#endif // ACCESSRIGHTS_H
