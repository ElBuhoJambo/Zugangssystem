#include "csvhandling.h"

csvHandling* csvHandling::cInstance = new csvHandling();

csvHandling* csvHandling::getInstance(){
    return cInstance;
}

csvHandling::csvHandling()
{

}

void csvHandling::readWholeFile(const QString& filePath){
    class WholeProcessor : public QtCSV::Reader::AbstractProcessor{
    public:
        QList<QStringList> data;

        virtual void preProccessRawLine(QString& line){
            if(line.isEmpty()){
                line = "Missing Entry";
            }
        }

        virtual bool processRowElements(const QStringList& elements){
            QList<QString> revertedElements(elements);

            data.push_back(QStringList(revertedElements));
            return true;
        }

    };

    WholeProcessor processor;
    if(!QtCSV::Reader::readToProcessor(filePath, processor)){
        qWarning() << "Failed to read file";
        return;
    }
    qDebug() << processor.data.size();
    emit FillTable(processor.data);
}

void csvHandling::readLastEntry(const QString& filePath){

    class LastEntryProcessor : public QtCSV::Reader::AbstractProcessor{
    public:
        QList<QStringList> data;

        virtual void preProcessRawLine(QString& line){
            if(line.isEmpty()){
                line = "NaN";
            }
        }

        virtual bool processRowElements(const QStringList& elements){
            QList<QString> revertedElements(elements);

            data.push_back(QStringList(revertedElements));
            return true;
        }
    };

    LastEntryProcessor processor;
    if(false == QtCSV::Reader::readToProcessor(filePath, processor)){
        qDebug() << "Failed to read file";
        return;
    }

    for(int i = 0; i < processor.data.size(); ++i){
        processor.data.at(i).join(",");
    }

    emit WriteToTable(processor.data.at(processor.data.size()-1).join(","));

}

void csvHandling::WriteToFile(const QString &filePath, QString data){
    QStringList dataList = data.split(QLatin1Char(','));

    QtCSV::VariantData varData;
    varData.addRow(dataList);

    if(!QtCSV::Writer::write(filePath, varData, ",", "\"", QtCSV::Writer::WriteMode::APPEND, {}, {})){
        qDebug() << "Failed to write to file: " << filePath;
    }

    qDebug() << "Write to " << filePath << " is okay";
    readLastEntry(filePath);
}
