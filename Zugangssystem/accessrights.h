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
    void SQLRequest(QString RFID, QString loc);
    void Visual(QString RFID, QString loc, bool access);
    void Door(bool access, QString loc);
    void logMessage(QString msg, int index);

public slots:
    void checkAccess(QString RFID, QString loc);
    void receiveResult(bool access, QString RFID, QString loc, QString name);

private:
    accessRights();
    static accessRights* aInstance;
};

#endif // ACCESSRIGHTS_H
