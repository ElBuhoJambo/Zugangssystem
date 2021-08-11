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

    //set the driver of the database and try to open the correct database
    if(QSqlDatabase::isDriverAvailable(DRIVER)){
        sDB = QSqlDatabase::addDatabase(DRIVER);
        qDebug() << "Driver set successfully";
        sDB.setDatabaseName("sqlTestForeign.db");
        if(!sDB.open()){
            qWarning() << "ERROR: " << sDB.lastError();
        }

        QSqlQuery query(sDB);
        query.exec("PRAGMA foreign_keys=ON;");

        /*
        if(!query.exec("CREATE TABLE worker (id INTEGER PRIMARY KEY, name TEXT, RFID TEXT, loc TEXT, access INTEGER)")){
            qWarning() << "ERROR: " << query.lastError().text();
        }

        if(!query.exec("INSERT INTO worker(name, RFID, loc, access) VALUES('Magda', '0004787793', 'Location 1', '1')")){
            qWarning() << "ERROR: " << query.lastError().text();
        }
        if(!query.exec("UPDATE worker SET name = 'Daniel', RFID = '0004365639', loc = 'Location 1', access = '1' WHERE id = 3")){
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
void sqlCheck::updateWorker(QString currUserId, QString userId, QString RFID, QString name, QList<int> groups, QString active){
    QSqlQuery query;
    QStringList data;

    query.prepare("SELECT name, active FROM User WHERE id = ?");
    query.addBindValue(currUserId);
    if(!query.exec()){
        qWarning() << "ERROR: " << query.lastError().text();
    }
    while(query.next()){
        data << query.value(0).toString() << query.value(1).toString();
    }

    query.prepare("SELECT RFID FROM Keys WHERE userid = ?");
    query.addBindValue(currUserId);
    if(!query.exec()){
        qWarning() << "ERROR: " << query.lastError().text();
    }
    while(query.next()){
        data << query.value(0).toString();
    }

    query.prepare("SELECT groupid FROM UserGroup WHERE userid = ?");
    query.addBindValue(currUserId);
    if(!query.exec()){
        qWarning() << "ERROR: " << query.lastError().text();
    }
    while(query.next()){
        data << query.value(0).toString();
    }

    if(userId.trimmed().isEmpty()){
        userId=currUserId;
    }
    if(RFID.trimmed().isEmpty()){
        RFID = data.at(2);
    }
    if(name.trimmed().isEmpty()){
        name = data.at(0);
    }
    if(groups.isEmpty()){
        for(int i = 3; i < data.size(); i++){
            groups << data.at(i).toInt();
        }
    }
    if(active.isEmpty()){
        active = data.at(1);
    }

    query.prepare("DELETE FROM User WHERE id = ?");
    query.addBindValue(currUserId);
    if(query.exec()){
        qDebug() << "Delete for update succesfully";
    }else{
        qWarning() << "ERROR: " << query.lastError().text();
    }
    addWorker(userId, RFID, name, groups);

    query.prepare("UPDATE User SET active = ? WHERE id = ?");
    query.addBindValue(active);
    query.addBindValue(userId);
    if(query.exec()){
        qDebug() << "Update succesfully";
    }else{
        qWarning() << "ERROR: " << query.lastError().text();
    }

}

/**
 * @brief sqlCheck::deleteWorker
 * sql query to delete a worker
 * @param RFID
 * RFID of the worker to delete
 */
void sqlCheck::deleteWorker(QString userId){
    QSqlQuery query;

    //perpare the query and execute it, if successfully emits the results
    query.prepare("DELETE FROM User WHERE id = ?");
    query.addBindValue(userId);
    if(query.exec()){
        qDebug() << "worker deleted successfully";
    }else{
        qWarning() << "ERROR: " << query.lastError().text();
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
void sqlCheck::addWorker(QString userId, QString RFID, QString name, QList<int> groups){
    QSqlQuery query;
    bool worked = true;

    //perpare the query and execute it, if successfully emits the results
    query.prepare("INSERT INTO User(id, name, active) VALUES(?, ?, 1)");
    query.addBindValue(userId);
    query.addBindValue(name);
    if(query.exec()){
        qDebug() << "User added successfully";
    }else{
        qWarning() << "ERROR: " << query.lastError().text();
        worked = false;
    }

    query.prepare("INSERT INTO Keys(RFID, userid) VALUES(?, ?)");
    query.addBindValue(RFID);
    query.addBindValue(userId);
    if(query.exec()){
        qDebug() << "Key added successfully";
    }else{
        qWarning() << "ERROR: " << query.lastError().text();
        worked = false;
    }

    for(int i = 0; i < groups.size(); i++){
        query.prepare("INSERT INTO UserGroup(userid, groupid) VALUES(?, ?)");
        query.addBindValue(userId);
        query.addBindValue(groups[i]);
        if(query.exec()){
            qDebug() << "UserGroup added successfully";
        }else{
            qWarning() << "ERROR: " << query.lastError().text();
            worked = false;
        }
    }

    if(!worked){
        query.prepare("DELETE FROM User WHERE id = ?");
        query.addBindValue(userId);
        if(query.exec()){
            qDebug() << "Add undone";
        }else{
            qWarning() << "ERROR: " << query.lastError().text();
        }
    }
}

/**
 * @brief sqlCheck::showTable
 * sql query to show the whole table
 */
void sqlCheck::showTable(){
    QSqlQuery query;
    QList<QStringList> result;
    //perpare the query and execute it, if successfully emits the results
    query.prepare("SELECT User.id, name, RFID, groupname, rightname FROM User "
                  "INNER JOIN Keys ON User.id = Keys.userid "
                  "INNER JOIN UserGroup ON User.id = UserGroup.userid "
                  "INNER JOIN Groups ON Groups.id = UserGroup.groupid "
                  "INNER JOIN GroupRights ON Groups.id = GroupRights.groupid "
                  "INNER JOIN Rights ON Rights.id = GroupRights.rightid");
    if(!query.exec()){
        qWarning() << "ERROR: " << query.lastError().text();
    }
    while(query.next()){
        QStringList temp;
        temp << query.value(0).toString() << query.value(1).toString() << query.value(2).toString() << query.value(3).toString() << query.value(4).toString();
        result << temp;
    }

    emit ShowTable(result);
}

/**
 * @brief sqlCheck::getNames
 * get every name in the database
 */
void sqlCheck::getNames(){
    QStringList result;
    QSqlQuery query;
    //perpare the query and execute it, if successfully emits the results
    query.prepare("SELECT name FROM User");
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
        emit Result(RFID, results.at(0));
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
    query.prepare("SELECT name FROM User "
                  "INNER JOIN Keys ON User.id = Keys.userid WHERE RFID = ?");
    query.addBindValue(RFID);
    if(query.exec()){
        if(query.next()){
            qDebug() << "DB found" << RFID << query.value(0).toString();
            emit logMessage(QString("Worker found for %1;sqlCheck;%2").arg(loc).arg(query.value(0).toString()), (int)LOG_SCAN);
            results << query.value(0).toString();
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
