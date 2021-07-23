#include "excelhandling.h"
#include "sqlcheck.h"

ExcelHandling* ExcelHandling::eInstance = new ExcelHandling();

ExcelHandling* ExcelHandling::getInstance(){
    return eInstance;
}

ExcelHandling::ExcelHandling(){
    Document workerSheet("/worker.xlsx");
    emit getWorker();
    QStringList tempSheets = workerSheet.sheetNames();
    QStringList tempSql = worker;

    if(!compareStringList(tempSql, tempSheets)){
        qDebug() << "Some sheets missing";
    }
}

void ExcelHandling::recieveNames(QStringList names){
    worker = names;
}

void ExcelHandling::addWorker(QString name){
    worker.append(name);
}

void ExcelHandling::toLowerCase(QStringList *names){
    for(int i = 0; i < names->size(); i++){
        names->replace(i, names->at(i).toLower());
    }
}

bool ExcelHandling::compareStringList(QStringList one, QStringList two){
    one.sort(Qt::CaseInsensitive);
    two.sort(Qt::CaseInsensitive);

    toLowerCase(&one);
    toLowerCase(&two);

    if(one.size() >= two.size()){
        for(int i = 0; i < one.size(); i++){
            if(one.at(i) != two.at(i)){
                return false;
            }
        }
    }else{
        for(int i = 0; i < two.size(); i++){
            if(one.at(i) != two.at(i)){
                return false;
            }
        }
    }

    return true;
}

void ExcelHandling::addMissingSheets(QStringList sql){
    Document workerSheet("/worker.xlsx");
    QStringList temp = workerSheet.sheetNames();
    QStringList missingWorker;

    temp.sort(Qt::CaseInsensitive);
    sql.sort(Qt::CaseInsensitive);

    toLowerCase(&temp);
    toLowerCase(&sql);

    if(temp.size() >= sql.size()){
        for(int i = 0; i < temp.size(); i++){
            if(temp.at(i) != sql.at(i)){
                missingWorker << sql.at(i);
            }
        }
    }else{
        for(int i = 0; i < sql.size(); i++){
            if(temp.at(i) != sql.at(i)){
                missingWorker << sql.at(i);
            }
        }
    }

    for(int i = 0; missingWorker.size(); i++){
        workerSheet.addSheet(missingWorker.at(i));
    }

    worker.erase(worker.begin(), worker.end());
    worker = workerSheet.sheetNames();
}

void ExcelHandling::getWorker(){
    emit GetWorker(worker);
}
