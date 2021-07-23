#ifndef EXCELHANDLING_H
#define EXCELHANDLING_H

#include <QStandardPaths>
#include <QtGlobal>
#include <QtCore>
#include <QVariant>
#include <iostream>
using namespace std;

#include "xlsxdocument.h"
#include "xlsxchart.h"
#include "xlsxcellrange.h"
#include "xlsxchartsheet.h"
#include "xlsxrichstring.h"
#include "xlsxworkbook.h"
using namespace QXlsx;

class ExcelHandling : public QObject
{
    Q_OBJECT

public:
    static ExcelHandling* getInstance(void);

    void addWorker(QString name);
    void toLowerCase(QStringList *names);
    bool compareStringList(QStringList one, QStringList two);
    void addMissingSheets(QStringList sql);

signals:
    void GetNames();
    void GetWorker(QStringList worker);

public slots:
    void recieveNames(QStringList names);
    void getWorker();


private:
    ExcelHandling();
    static ExcelHandling* eInstance;

    QStringList worker;
};

#endif // EXCELHANDLING_H
