#ifndef OPENDOOR_H
#define OPENDOOR_H

#include <QObject>
#include <QDebug>

#include "logging.h"

class openDoor : public QObject
{
    Q_OBJECT

    //function to access class in any other class
public:
    static openDoor* getInstance(void);

    //signals for checking the rights of an RFID,
    //and logging
signals:
    void Rights(QString RFID, QString loc);
    void logMessage(QString msg, int index);

    //slots opening the door or keeping it closed,
    //and sending the RFID for checking access
public slots:
    void rightsReturned(bool access, QString loc);
    void checkAccess(QString RFID, QString loc);

    //constructor and instance for use in other classes
private:
    openDoor();
    static openDoor* oInstance;
};

#endif // OPENDOOR_H
