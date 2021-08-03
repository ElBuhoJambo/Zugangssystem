#ifndef ACCESSRIGHTS_H
#define ACCESSRIGHTS_H

#include <QObject>
#include <QDebug>

#include "logging.h"


class accessRights : public QObject
{
    Q_OBJECT

    //function to access class in any other class
public:
    static accessRights* getInstance(void);

    //signals for sql, visual output, door access handling and logging
signals:
    void SQLRequest(QString RFID, QString loc);
    void Visual(QString RFID, QString loc, bool access);
    void Door(bool access, QString loc);
    void logMessage(QString msg, int index);

    //slots for receiving the access request and receiving the sql results
public slots:
    void checkAccess(QString RFID, QString loc);
    void receiveResult(bool access, QString RFID, QString loc, QString name);

    //constructor and instance for use in other classes
private:
    accessRights();
    static accessRights* aInstance;
};

#endif // ACCESSRIGHTS_H
