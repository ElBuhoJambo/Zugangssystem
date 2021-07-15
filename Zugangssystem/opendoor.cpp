#include "opendoor.h"

openDoor* openDoor::oInstance = new openDoor();

openDoor* openDoor::getInstance(){
    return oInstance;
}

openDoor::openDoor()
{

}

void openDoor::rightsReturned(bool access, QString loc){

}

void openDoor::checkAccess(QString RFID, QString loc){
    emit Rights(RFID, loc);
}
