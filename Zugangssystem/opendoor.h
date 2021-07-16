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
    void Rights(QString RFID, QString loc);
    void logMessage(QString msg, int index);

public slots:
    void rightsReturned(bool access, QString loc);
    void checkAccess(QString RFID, QString loc);

private:
    openDoor();
    static openDoor* oInstance;
};

#endif // OPENDOOR_H
