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
    void WriteToTable(QString data);
    void FillTable(QList<QStringList> data);
    void logMessage(QString msg, int index);

private:
    csvHandling();
    static csvHandling* cInstance;
};

#endif // CSVHANDLING_H
