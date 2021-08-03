#ifndef CSVHANDLING_H
#define CSVHANDLING_H

#include "qtcsv/variantdata.h"
#include "qtcsv/reader.h"
#include "qtcsv/writer.h"
#include "logging.h"

#include <QDebug>


class csvHandling : public QObject
{
    Q_OBJECT

    //function to access class in any other class
public:
    static csvHandling* getInstance(void);

    //slots for reading the bottom most row,
    //writing in the csv file at the bottom of the file,
    //and reading the whole file
public slots:
    void readLastEntry(const QString& filePath);
    void WriteToFile(const QString &filePath, QString data);
    void readWholeFile(const QString& filePath);

    //signals for writing in the csv file,
    //sending the whole file,
    //and logging
signals:
    void WriteToTable(QString data);
    void FillTable(QList<QStringList> data);
    void logMessage(QString msg, int index);

    //constructor and instance for use in other classes
private:
    csvHandling();
    static csvHandling* cInstance;
};

#endif // CSVHANDLING_H
