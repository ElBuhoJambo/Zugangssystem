#include "logging.h"
#include "unistd.h"

#include <QDateTime>
#include <QDebug>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

Logging* Logging::_instance = new Logging();

/* Returns a pointer to the instance
 * \return Logging*   instance pointer
 */
Logging* Logging::getInstance(void)
{
    return _instance;
}

/* Constructor of the class.
 * The logging class starts its own thread including its own message handler.
 * \return -
 */
Logging::Logging(QObject *parent)
    : QThread(parent)
{
    lLogQueue.clear();

    for (int i = 0; i < LOG_NO_LOGFILES; i++)
    {
        lPLogFile[i] = new QFile(QString("%1.%2").arg(lLogNames[i]).arg("log"));
    }

    lMaxLogFileSize = LOGGING_LOG_FILE_SIZE;

    unlink(NAME_PIPE_IN);
    mkfifo(NAME_PIPE_IN, 0666);
    lFdPipeIn = open(NAME_PIPE_IN, O_RDONLY | O_NONBLOCK);
    moveToThread(this);


    lIsTimeValid = true;
    logMessage("App;Logging available - waiting for timestamp",(int)LOG_COMMON);
    lIsTimeValid = false;

    connect(this, SIGNAL(GetCurrentTime()), this, SLOT(timeUpdate_Logging()));

    start();
}

/* Destructor of the class.
 * \return -
 */
Logging::~Logging()
{
    for (int i = 0; i < LOG_NO_LOGFILES; i++)
    {
        lPLogFile[i]->close();
    }
    close(lFdPipeIn);
    udpSocket->close();
}

/**
 * @brief Logging::getCurrTime
 * get the last time saved in current time
 * @return
 */
QDateTime Logging::getCurrTime(){
    return currentTime;
}

/**
 * @brief Logging::getCurrTime
 * emit the last time saved in current time
 * @param csv
 * safety
 */
void Logging::getCurrTime(bool csv, QString name){
    if(csv){
        emit SendCurrentTime(currentTime, name);
    }
}

/**
 * @brief Logging::timeUpdate_Logging
 * establish connection to ntp server
 */
void Logging::timeUpdate_Logging(){
    QHostInfo info = QHostInfo::fromName("0.pool.ntp.org");
    QString ipAddress = info.addresses().first().toString();
    //qDebug() << ipAddress;
    udpSocket = new QUdpSocket(this);

    connect(udpSocket, SIGNAL(readyRead()), this, SLOT(readPendingDatagrams()));
    connect(udpSocket, SIGNAL(connected()), this, SLOT(connectSuccess()));
    udpSocket->abort();
    udpSocket->connectToHost("0.pool.ntp.org", 123);
}

/**
 * @brief Logging::readPendingDatagrams
 * read the data of the ntp server, check if it's valid and save it
 */
void Logging::readPendingDatagrams(){
    QByteArray newTime;
    QDateTime Epoch(QDate(1900, 1, 1));
    QDateTime unixStart(QDate(1970, 1, 1));
    quint64 seconds = 0;

    //read the data and save it in array
    while(udpSocket->hasPendingDatagrams()){
        QByteArray byteArray;
        byteArray.append(udpSocket->read(48));
        //qDebug() << (QString::number(byteArray.size()));

        QByteArray lastbyteArray(byteArray.right(8));

        seconds = 0;
        for(int i = 0; i <= 3; i++){
            seconds = (seconds << 8) | lastbyteArray[i];
        }

        //qDebug() << (QString::number(seconds, 10));
    }

    //calculate the current date and time
    QDateTime newestTime;
    quint64 diffe = seconds - (quint64) Epoch.secsTo(unixStart) + 3600;
    newestTime.setTime_t(diffe);
    //qDebug() << (QString::number((quint64) Epoch.secsTo(unixStart), 10));
    //qDebug() << (newestTime.toString());

    if(diffe < 2081376000){
        Logging::currentTime = newestTime;
    }else{
        //qDebug() << "Time invalid";
    }


}

/**
 * @brief Logging::connectSuccess
 * connection to ntp server established
 */
void Logging::connectSuccess(){
    //qDebug() << "Connected";
    QByteArray timeRequest(48, 0);
    timeRequest[0] = '\x23';
    udpSocket->flush();
    udpSocket->write(timeRequest);
}

/* Cyclic part of the logging thread
 * \return -
 */
void Logging::run()
{
    lPCheckExtLog = new QTimer();
    lPCheckExtLog->setInterval(1000);
    lPCheckExtLog->setSingleShot(false);
    connect(lPCheckExtLog,SIGNAL(timeout()),this,SLOT(checkExternalLogging()));
    lPCheckExtLog->start();


    QThread::exec();
}
/*
 *
 */
void Logging::checkExternalLogging(void)
{
    QByteArray data;
    data.clear();
    data.reserve(1024);
    size_t bytesRead;
    if ( 0 != (bytesRead = read(lFdPipeIn,data.data(),1024)))
    {
        data.resize(bytesRead);
        logMessage(QString("External log;%1").arg(QString::fromUtf8(data.data()).simplified()),(int)LOG_COMMON);
    }

}

/* Sets the maximum logfile size in bytes (default is 1MB)
 * \param   maxFileSize requested logfile size
 * \return -
 */
void Logging::setLogFileSize(quint32 const maxFileSize)
{
    lMaxLogFileSize = maxFileSize;
}

/* Local time now is valid -> empty the queue.
 * \param -
 * \return -
 */
void Logging::logTimeIsvalid(void)
{
    lIsTimeValid = true;
    for (int i = 0; i < lLogQueue.count(); i++)
    {
        LOG_QueueEl_t* pEntry = lLogQueue.at(i);

        logMessage(pEntry->msg,pEntry->index);
        delete pEntry;
    }
    lLogQueue.clear();
}

/* Slot for the log message.
 * Date and time will be added.
 * The log message is written to the logfile immediately.
 * The file system is synced afterwards.
 * \param   msg     QString containing the log message
 * \param   index   file index
 * \return -
 */
void Logging::logMessage(QString msg,int index)
{
    //temporary
    lIsTimeValid = true;
    if (lIsTimeValid)
    {
        QFile* pLogFile = lPLogFile[index];

        while (pLogFile->isOpen())
        {
            msleep(5);
        }

        /* keep the file closed */
        if (pLogFile->open(QIODevice::Append))
        {
            emit GetCurrentTime();

            QString message = currentTime.toString("yyyyMMdd;hhmmss;") + msg + "\n";
            pLogFile->write(message.toLatin1(),message.length());
            pLogFile->close();
            /* sync with the disc to avoid losing data on power down */
            fsync(pLogFile->handle());
            emit LogMessageTest(message);
        }
        /* create a backup log file if the maximum size is reached */
        if ( lMaxLogFileSize <= pLogFile->size())
        {
            QFile* pBackupLogFile = new QFile(QString("%1.%2").arg(lLogNames[index]).arg("bak"));
            if ( pBackupLogFile->exists())
            {
                pBackupLogFile->remove();
            }
            if (pLogFile->rename(QString("%1.%2").arg(lLogNames[index]).arg("bak")))
            {
                fsync(pLogFile->handle());
                pLogFile->setFileName(QString("%1.%2").arg(lLogNames[index]).arg("log"));
            }
            delete pBackupLogFile;
        }
    }
    else
    {
        LOG_QueueEl_t* pEntry = new LOG_QueueEl_t;
        pEntry->msg = msg;
        pEntry->index = index;
        lLogQueue.append(pEntry);
    }
}


QString Logging::getLogFileName(int index)
{
    if (index < (int)LOG_NO_LOGFILES)
    {
        return QString(lLogNames[index]);
    }
    return QString("");
}


void Logging::copyLogfiles(QString destination)
{
    logMessage(QString("copy logfiles to %1").arg(destination),(int)LOG_COMMON);

    for (int i = 0; i < LOG_NO_LOGFILES; i++)
    {
        /* remove at destination */
        QFile* pTmpFile = new QFile(QString("%1/%2.bak").arg(destination).arg(lLogNames[i]));
        if (pTmpFile->exists())
        {
            pTmpFile->remove();
        }
        delete pTmpFile;
        pTmpFile = new QFile(QString("%1/%2.log").arg(destination).arg(lLogNames[i]));
        if (pTmpFile->exists())
        {
            pTmpFile->remove();
        }
        delete pTmpFile;
        /* copy the files */
        pTmpFile = new QFile(QString("%1.log").arg(lLogNames[i]));
        if ( pTmpFile->exists())
        {
            if ( pTmpFile->copy(QString("%1/%2").arg(destination).arg(pTmpFile->fileName())))
            {
                logMessage(QString("copy %1 successful").arg(pTmpFile->fileName()),(int)LOG_COMMON);
            }
            else
            {
                logMessage(QString("copy %1 failed").arg(pTmpFile->fileName()),(int)LOG_COMMON);
            }
        }
        delete pTmpFile;
        pTmpFile = new QFile(QString("%1.bak").arg(lLogNames[i]));
        if ( pTmpFile->exists())
        {
            if ( pTmpFile->copy(QString("%1/%2").arg(destination).arg(pTmpFile->fileName())))
            {
                logMessage(QString("copy %1 successful").arg(pTmpFile->fileName()),(int)LOG_COMMON);
            }
            else
            {
                logMessage(QString("copy %1 failed").arg(pTmpFile->fileName()),(int)LOG_COMMON);
            }
        }
        delete pTmpFile;
    }
    emit stopCopyLogfiles();
}
