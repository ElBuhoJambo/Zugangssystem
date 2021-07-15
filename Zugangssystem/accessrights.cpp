#include "accessrights.h"

accessRights* accessRights::aInstance = new accessRights();

accessRights* accessRights::getInstance(){
    return aInstance;
}

accessRights::accessRights()
{

}

void accessRights::checkAccess(QString RFID, QString loc){
    emit SQLRequest(RFID, loc);
}

void accessRights::receiveResult(bool access, QString RFID, QString loc, QString name){
    emit Door(access, loc);
    emit Visual(name, RFID, access);
}
