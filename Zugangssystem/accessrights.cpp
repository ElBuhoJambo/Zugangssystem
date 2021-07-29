#include "accessrights.h"

accessRights* accessRights::aInstance = new accessRights();

/**
 * @brief accessRights::getInstance
 * returns instance for use in other classes
 * @return
 */
accessRights* accessRights::getInstance(){
    return aInstance;
}

accessRights::accessRights()
{

}

/**
 * @brief accessRights::checkAccess
 * emits the signal to check for the access status in the SQLite db
 * @param RFID
 * scanned RFID
 * @param loc
 * location of scan
 */
void accessRights::checkAccess(QString RFID, QString loc){

    //checks if RFID is in the correct format
    if(RFID.length() == 10){
        emit SQLRequest(RFID, loc);
    }else{
        qDebug() << "ERROR RFID in faulty format at accessRights";
        emit logMessage(QString("ERR;faulty RFID;checkAccess;").append(RFID), (int)LOG_SCAN);
    }

}

/**
 * @brief accessRights::receiveResult
 * recieves the SQLite results and distriputes them to the other classes
 * @param access
 * access status
 * @param RFID
 * scanned RFID
 * @param loc
 * location of scan
 * @param name
 * name of the worker of the RFID
 */
void accessRights::receiveResult(bool access, QString RFID, QString loc, QString name){
    emit Door(access, loc);
    emit Visual(name, RFID, access);
}
