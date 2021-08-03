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

public:
    static csvHandling* getInstance(void);

public slots:
    void readLastEntry(const QString& filePath);
    void WriteToFile(const QString &filePath, QString data);
    void readWholeFile(const QString& filePath);

signals:
    /**
     * @brief WriteToTable
     * emits to send the last line of the csv file of a specific worker to add it to the table
     * @param data
     * data of the read line
     */
    void WriteToTable(QString data);

    /**
     * @brief FillTable
     * emits to send the whole csv file of a specific worker to fill the table
     * @param data
     * data of the csv file
     */
    void FillTable(QList<QStringList> data);

    /**
     * @brief logMessage
     * emits to log a certain event
     * @param msg
     * logging message
     * @param index
     * specifies which file it should be logged in
     */
    void logMessage(QString msg, int index);

    //constructor and instance for use in other classes
private:
    csvHandling();
    static csvHandling* cInstance;
};

#endif // CSVHANDLING_H
