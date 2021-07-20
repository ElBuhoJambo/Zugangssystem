#include "opendoor.h"

openDoor* openDoor::oInstance = new openDoor();

openDoor* openDoor::getInstance(){
    return oInstance;
}

openDoor::openDoor()
{

}

/**
 * @brief openDoor::rightsReturned
 * recieves the result whether or not the door gets unlocked and does it
 * @param access
 * access status
 * @param loc
 * location of scan
 */
void openDoor::rightsReturned(bool access, QString loc){
    if(access){
        qDebug() << "Granted " << loc;
    }else{
        qDebug() << "Denied" << loc;
    }
}

/**
 * @brief openDoor::checkAccess
 * emits signal to check for the access status
 * @param RFID
 * scanned RFID
 * @param loc
 * location of scan
 */
void openDoor::checkAccess(QString RFID, QString loc){
    emit Rights(RFID, loc);
}
