#include "scanner.h"

Scanner* Scanner::sInstance = new Scanner();

/**
 * @brief Scanner::getInstance
 * returns instance for use in other classes
 * @return
 */
Scanner* Scanner::getInstance(void){
    return sInstance;
}

Scanner::Scanner(QObject *parent) : QThread(parent){
    moveToThread(this);
    start();
}

Scanner::~Scanner(){

}

/**
 * @brief Scanner::run
 * run function for thread
 * initializes scanner
 */
void Scanner::run(){
    initScanner();
    QThread::exec();
}

/**
 * @brief Scanner::initScanner
 * initialize the timer to check up on the keyboard event file
 */
void Scanner::initScanner(void){
    notificationEnabled = false;
    sScannerFile = new QFile(defaultPath);

    //timer for checking every 100ms to check for the keyboard/scanner
    sCheckScanner = new QTimer(this);
    sCheckScanner->setInterval(100);
    sCheckScanner->setSingleShot(false);
    connect(sCheckScanner, SIGNAL(timeout()), this, SLOT(checkScannerData()));
    sCheckScanner->start();
}

/**
 * @brief Scanner::checkScannerData
 * check if the keyboard is connected or not
 * if it is connected, activate event handling
 */
void Scanner::checkScannerData(){
    if(sScannerFile->exists()){
        if(notificationEnabled){
            return;
        }

        //open the input event file and connect the signal for any event happening for the file to handleNotification
        fd = open(defaultPath.toUtf8().data(), O_RDONLY | O_NONBLOCK);
        if(-1 != fd){
            sNotifier = new QSocketNotifier(fd, QSocketNotifier::Read, this);
            connect(sNotifier, SIGNAL(activated(int)), this, SLOT(handleNotification(int)));
            emit logMessage("scanner connected;Scanner", (int)LOG_SCAN);
            notificationEnabled = true;
        }
    }else{
        //if the keyboard got disconnected, disable all connection and check up on the input event file
        if(notificationEnabled){
            sNotifier->setEnabled(false);
            disconnect(sNotifier, SIGNAL(activated(int)), this, SLOT(handleNotification(int)));
            delete sNotifier;
            close(fd);
            emit logMessage("scanner disconnected;Scanner", (int)LOG_SCAN);
            notificationEnabled = false;
        }
    }
}

/**
 * @brief Scanner::handleNotification
 * check if the scanner is still connected or if the event was the disconnect
 * if still connected than read the data and save it
 * @param socket
 */
void Scanner::handleNotification(int socket){
    //check if the event is the disconnection of the scanner
    if(!sScannerFile->exists()){
        if(notificationEnabled){
            sNotifier->setEnabled(false);
            disconnect(sNotifier, SIGNAL(activated(int)), this, SLOT(handleNotification(int)));
            delete sNotifier;
            close(fd);
            emit logMessage("scanner disconnected;Scanner", (int)LOG_SCAN);
            notificationEnabled = false;
        }
        return;
    }

    //read the input data and save it in the correct format
    if(read(fd, &event, sizeof(event)) == sizeof(event)){
        if(event.type != EV_SYN){
            if(event.value == 1 && event.code != 28){
                RFID[i] = saveInCorrectFormat(event.code);
                rfid.append(QString("%1").arg(saveInCorrectFormat(event.code)));
                i++;
            }
            //qDebug() << "Event: time " << event.time.tv_sec <<"."<<event.time.tv_usec << ", type " << event.type << ", code " << event.code << ", value " << event.value;
        }
    }

    //check if the whole rfid has gotten read and if it had been read 10 times
    if(rfid.size() == 10){
        buffer++;
        if(buffer == 10){
            emit ChipScanned(rfid);
            emit logMessage("RFID read an processed;Scanner", (int)LOG_SCAN);
            i = 0;
            rfid.clear();
            buffer = 0;
        }
    }
}

/**
 * @brief Scanner::saveInCorrectFormat
 * correct the raw data in the it's right format
 * @param code
 * current data to convert
 * @return
 * converted data
 */
int Scanner::saveInCorrectFormat(int code){
    /* the raw data is generally just one to big than the actual expected value */
    /* there are certain exception, like an code 11 means it is a 0 */
    /* the string of the rfid ends with an enter which is sent as the code 28 but this case shouldn't get here, if it does the -1 will signal that there was a mistake */
    switch(code){
    case 11:
        return 0;
    case 28:
        return -1;
    default:
        return code-1;
    }
}
