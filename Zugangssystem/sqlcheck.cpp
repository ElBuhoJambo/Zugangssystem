#include "sqlcheck.h"

sqlCheck* sqlCheck::sInstance = new sqlCheck();

/**
 * @brief sqlCheck::getInstance
 * returns instance for use in other classes
 * @return
 */
sqlCheck* sqlCheck::getInstance(){
    return sInstance;
}

/**
 * @brief sqlCheck::sqlCheck
 * establish connection to the database
 */
sqlCheck::sqlCheck(){
    const QString DRIVER("QSQLITE");

    if(QSqlDatabase::isDriverAvailable(DRIVER)){
        sDB = QSqlDatabase::addDatabase(DRIVER);
        qDebug() << "Driver set successfully";
        sDB.setDatabaseName("sqliteTest.db");
        if(!sDB.open()){
            qWarning() << "ERROR: " << sDB.lastError();
        }

        QSqlQuery query;

        /*if(!query.exec("CREATE TABLE worker (id INTEGER PRIMARY KEY, name TEXT, RFID TEXT, loc TEXT, access INTEGER)")){
            qWarning() << "ERROR: " << query.lastError().text();
        }*/

        /*if(!query.exec("INSERT INTO worker(name, RFID, loc, access) VALUES('Magda', '0004787793', 'Location 1', '1')")){
            qWarning() << "ERROR: " << query.lastError().text();
        }*/
    }else{
        qDebug() << "Driver Error";
    }
}

/**
 * @brief sqlCheck::updateWorker
 * sql query to update a worker
 * @param RFID
 * new RFID
 * @param location
 * new location
 * @param name
 * new name
 * @param access
 * new access status
 * @param currRFID
 * old RFID
 */
void sqlCheck::updateWorker(QString RFID, QString location, QString name, QString access, QString currRFID){
    QSqlQuery query;
    int accessInt;
    if(access == "true"){
        accessInt = 1;
    }else{
        accessInt = 0;
    }

    //perpare the query and execute it, if successfully emits the results
    query.prepare("UPDATE worker SET name = ?, RFID = ?, loc = ?, access = ? WHERE RFID = ?");
    query.addBindValue(name);
    query.addBindValue(RFID);
    query.addBindValue(location);
    query.addBindValue(accessInt);
    query.addBindValue(currRFID);
    if(query.exec()){
        qDebug() << "Worker updated successfully";
        emit logMessage(QString("worker updated;%1;%2").arg(name).arg(RFID),(int)LOG_COMMON);
        emit UpdateWorker(RFID, location, name, access, currRFID);
    }else{
        qWarning() << "ERROR: " << query.lastError().text();
        emit logMessage(QString("ERR;worker not updated;no query;%1").arg(currRFID), (int)LOG_COMMON);
    }
}

/**
 * @brief sqlCheck::deleteWorker
 * sql query to delete a worker
 * @param RFID
 * RFID of the worker to delete
 */
void sqlCheck::deleteWorker(QString RFID){
    QSqlQuery query;

    //perpare the query and execute it, if successfully emits the results
    query.prepare("DELETE FROM worker WHERE RFID = ?");
    query.addBindValue(RFID);
    if(query.exec()){
        qDebug() << "worker deleted successfully";
        emit logMessage(QString("worker deleted;%1").arg(RFID), (int)LOG_COMMON);
        emit DeleteRow(RFID);
    }else{
        qWarning() << "ERROR: " << query.lastError().text();
        emit logMessage(QString("ERR;worker not deleted;no query;%1").arg(RFID), (int)LOG_COMMON);
    }
}

/**
 * @brief sqlCheck::addWorker
 * sql query to add a worker
 * @param RFID
 * RFID of the worker
 * @param location
 * location of the worker
 * @param name
 * name of the worker
 * @param access
 * access status of the worker
 */
void sqlCheck::addWorker(QString RFID, QString location, QString name, QString access){
    QSqlQuery query;
    int accessInt;
    if(access == "true"){
        accessInt = 1;
    }else{
        accessInt = 0;
    }

    //perpare the query and execute it, if successfully emits the results
    query.prepare("INSERT INTO worker(name, RFID, loc, access) VALUES(?, ?, ?, ?)");
    query.addBindValue(name);
    query.addBindValue(RFID);
    query.addBindValue(location);
    query.addBindValue(accessInt);
    if(query.exec()){
        qDebug() << "worker added successfully";
        emit logMessage(QString("worker added;%1;%2").arg(name).arg(RFID), (int)LOG_COMMON);
        emit ShowTable(name,RFID,location,QString::number(accessInt));
    }else{
        qWarning() << "ERROR: " << query.lastError().text();
        emit logMessage(QString("ERR;worked not added;no query;%1;%2").arg(name).arg(RFID), (int)LOG_COMMON);
    }
}

/**
 * @brief sqlCheck::showTable
 * sql query to show the whole table
 */
void sqlCheck::showTable(){
    QSqlQuery query;
    //perpare the query and execute it, if successfully emits the results
    query.prepare("SELECT name, RFID, loc, access FROM worker");
    if(!query.exec()){
        qWarning() << "ERROR: " << query.lastError().text();
    }
    while(query.next()){
        emit ShowTable(QString(query.value(0).toString()), QString(query.value(1).toString()), QString(query.value(2).toString()), query.value(3).toString());
    }
}

/**
 * @brief sqlCheck::getNames
 * get every name in the database
 */
void sqlCheck::getNames(){
    QStringList result;
    QSqlQuery query;
    //perpare the query and execute it, if successfully emits the results
    query.prepare("SELECT name FROM worker");
    if(!query.exec()){
        qWarning() << "ERROR: " << query.lastError().text();
    }
    while(query.next()){
        result.append(query.value(0).toString());
    }
    emit GetNames(result);
}

/**
 * @brief sqlCheck::receiveRequest
 * emits the results of the scanned worker
 * @param RFID
 * scanned RFID
 * @param loc
 * location of scan
 */
void sqlCheck::receiveRequest(QString RFID, QString loc){
    QStringList results;
    if(RFID.length() == 10){
        qDebug() << "RFID is in correct format at sqlCheck";
        results = request(RFID, loc);
        if(results.size() == 1){
            emit Result(false, RFID, loc, results.at(0));
            return;
        }
        if(results.at(1).toInt()){
            emit Result(true, RFID, loc, results.at(0));
        }else{
            emit Result(false, RFID, loc, results.at(0));
        }
    }else{
        qDebug() << "RFID is in faulty format at sqlCheck";
    }
}

/**
 * @brief sqlCheck::request
 * sql query to get the scanned worker
 * @param RFID
 * scanned RFID
 * @param loc
 * location of scan
 * @return
 * result of the worker query
 */
QStringList sqlCheck::request(QString RFID, QString loc){
    QStringList results;

    if(!sDB.isOpen()){
        qDebug() << "DB is closed";
        return QStringList("DB closed");
    }

    QSqlQuery query;
    //perpare the query and execute it, if successfully emits the results
    query.prepare("SELECT name, access FROM worker WHERE RFID = ?");
    query.addBindValue(RFID);
    if(query.exec()){
        if(query.next()){
            qDebug() << "DB found" << RFID << query.value(0).toString();
            emit logMessage(QString("Worker found for %1;sqlCheck;%2").arg(loc).arg(query.value(0).toString()), (int)LOG_SCAN);
            results << query.value(0).toString() << query.value(1).toString();
            return results;
        }else{
            query.clear();
            query.prepare("SELECT name, access FROM worker WHERE RFID = 'ClassID.Fehler'");
            if(query.exec()){
                if(query.next()){
                    qDebug() << "DB not found" << RFID << query.value(0).toString();
                    emit logMessage(QString("ERR;DB not found;sqlCheck;").append(RFID), (int)LOG_SCAN);
                    return QStringList(query.value(0).toString());
                }else{
                    qDebug() << "Error query next";
                    emit logMessage(QString("ERR;Worker not found;sqlCheck;").append(RFID), (int)LOG_SCAN);
                    return QStringList("Worker not found");
                }
            }else{
                qDebug() << "Error query execution";
                emit logMessage(QString("ERR;Worker not found;sqlCheck;").append(RFID), (int)LOG_SCAN);
                return QStringList("Worker not found");
            }

        }
    }else{
        qDebug() << "Error query execution";
        emit logMessage(QString("ERR;Worker not found;sqlCheck;").append(RFID), (int)LOG_SCAN);
        return QStringList("Worker not found");
    }
}

bool sqlCheck::isOpen(){
    return sDB.isOpen();
}
