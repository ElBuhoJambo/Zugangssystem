#ifndef OPENDOOR_H
#define OPENDOOR_H

#include <QObject>
#include <QDebug>

#include "logging.h"

class openDoor : public QObject
{
    Q_OBJECT

public:
    static openDoor* getInstance(void);

signals:
    /**
     * @brief Rights
     * emits to check for the access status
     * @param RFID
     * scanned RFID
     * @param loc
     * location of scan
     */
    void Rights(QString RFID, QString loc);

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
    void rightsReturned(bool access, QString loc);
    void checkAccess(QString RFID, QString loc);

    //constructor and instance for use in other classes
private:
    openDoor();
    static openDoor* oInstance;
};

#endif // OPENDOOR_H
