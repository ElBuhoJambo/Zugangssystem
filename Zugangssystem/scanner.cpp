#include "scanner.h"

Scanner* Scanner::sInstance = new Scanner();

Scanner* Scanner::getInstance(void){
    return sInstance;
}

Scanner::Scanner(QObject *parent) : QThread(parent){
    moveToThread(this);
    start();
}

Scanner::~Scanner(){

}

void Scanner::run(){
    initScanner();
    QThread::exec();
}

void Scanner::initScanner(void){
    notificationEnabled = false;
    sScannerFile = new QFile(defaultPath);

    sCheckScanner = new QTimer(this);
    sCheckScanner->setInterval(100);
    sCheckScanner->setSingleShot(false);
    connect(sCheckScanner, SIGNAL(timeout()), this, SLOT(checkScannerData()));
    sCheckScanner->start();
}

void Scanner::checkScannerData(){
    if(sScannerFile->exists()){
        if(notificationEnabled){
            return;
        }

        fd = open(defaultPath.toUtf8().data(), O_RDONLY | O_NONBLOCK);
        if(-1 != fd){
            sNotifier = new QSocketNotifier(fd, QSocketNotifier::Read, this);
            connect(sNotifier, SIGNAL(activated(int)), this, SLOT(handleNotification(int)));
            qDebug() << "Scanner connected";
            notificationEnabled = true;
        }
    }else{
        if(notificationEnabled){
            sNotifier->setEnabled(false);
            disconnect(sNotifier, SIGNAL(activated(int)), this, SLOT(handleNotification(int)));
            delete sNotifier;
            close(fd);
            qDebug() << "Scanner disconnect";
            notificationEnabled = false;
        }
    }
}

void Scanner::handleNotification(int socket){
    if(!sScannerFile->exists()){
        if(notificationEnabled){
            sNotifier->setEnabled(false);
            disconnect(sNotifier, SIGNAL(activated(int)), this, SLOT(handleNotification(int)));
            delete sNotifier;
            close(fd);
            qDebug() << "Scanner disconnect";
            notificationEnabled = false;
        }
        return;
    }

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

    if(rfid.size() == 10){
        buffer++;
        if(buffer == 10){
            emit ChipScanned(rfid);
            i = 0;
            rfid.clear();
            buffer = 0;
        }
    }
}

int Scanner::saveInCorrectFormat(int code){
    switch(code){
    case 11:
        return 0;
    case 28:
        return -1;
    default:
        return code-1;
    }
}
