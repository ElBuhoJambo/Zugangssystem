#include "accessrights.h"

accessRights* accessRights::aInstance = new accessRights();

accessRights* accessRights::getInstance(){
    return aInstance;
}

accessRights::accessRights()
{

}

void accessRights::checkAccess(QString RFID, QString loc){
    if(RFID.length() == 10){
        emit SQLRequest(RFID, loc);
    }else{
        qDebug() << "ERROR RFID in faulty format at accessRights";
        emit logMessage(QString(";ERR;faulty RFID;checkAccess;").append(RFID), (int)LOG_SCAN);
    }

}

void accessRights::receiveResult(bool access, QString RFID, QString loc, QString name){
    emit Door(access, loc);
    emit Visual(name, RFID, access);
}
