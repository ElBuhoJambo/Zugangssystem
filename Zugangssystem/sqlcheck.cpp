#include "sqlcheck.h"

sqlCheck* sqlCheck::sInstance = new sqlCheck();

sqlCheck* sqlCheck::getInstance(){
    return sInstance;
}

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

void sqlCheck::showTable(){
    QSqlQuery query;
    query.prepare("SELECT name, RFID, loc, access FROM worker");
    if(!query.exec()){
        qWarning() << "ERROR: " << query.lastError().text();
    }
    while(query.next()){
        emit ShowTable(QString(query.value(0).toString()), QString(query.value(1).toString()), QString(query.value(2).toString()), query.value(3).toString());
    }
}

void sqlCheck::receiveRequest(QString RFID, QString loc){
    QStringList results;
    if(RFID.length() == 10){
        qDebug() << "RFID is in correct format at sqlCheck";
        results = request(RFID, loc);
        if(results.at(1).toInt()){
            emit Result(true, RFID, loc, results.at(0));
        }else{
            emit Result(true, RFID, loc, results.at(0));
        }
    }else{
        qDebug() << "RFID is in faulty format at sqlCheck";
    }
}

QStringList sqlCheck::request(QString RFID, QString loc){
    QStringList results;

    if(!sDB.isOpen()){
        qDebug() << "DB is closed";
        return QStringList("DB closed");
    }

    QSqlQuery query;
    query.prepare("SELECT name, access FROM worker WHERE RFID = ?");
    query.addBindValue(RFID);

    if(query.exec()){
        if(query.next()){
            qDebug() << "DB found" << RFID << query.value(0).toString();
            emit logMessage(QString(";Worker found for %1;sqlCheck;%2").arg(loc).arg(query.value(0).toString()), (int)LOG_SCAN);
            results << query.value(0).toString() << query.value(1).toString();
            return results;
        }else{
            query.clear();
            query.prepare("SELECT name, access FROM worker WHERE RFID = 'ClassID.Fehler'");
            if(query.exec()){
                if(query.next()){
                    qDebug() << "DB not found" << RFID << query.value(0).toString();
                    emit logMessage(QString(";ERR;DB not found;sqlCheck;").append(RFID), (int)LOG_SCAN);
                    return QStringList(query.value(0).toString());
                }else{
                    qDebug() << "Error query next";
                    emit logMessage(QString(";ERR;Worker not found;sqlCheck;").append(RFID), (int)LOG_SCAN);
                    return QStringList("Worker not found");
                }
            }else{
                qDebug() << "Error query execution";
                emit logMessage(QString(";ERR;Worker not found;sqlCheck;").append(RFID), (int)LOG_SCAN);
                return QStringList("Worker not found");
            }

        }
    }else{
        qDebug() << "Error query execution";
        emit logMessage(QString(";ERR;Worker not found;sqlCheck;").append(RFID), (int)LOG_SCAN);
        return QStringList("Worker not found");
    }
}

bool sqlCheck::isOpen(){
    return sDB.isOpen();
}
