#include "csvhandling.h"

csvHandling* csvHandling::cInstance = new csvHandling();

/**
 * @brief csvHandling::getInstance
 * returns instance for use in other classes
 * @return
 */
csvHandling* csvHandling::getInstance(){
    return cInstance;
}

csvHandling::csvHandling()
{

}

/**
 * @brief csvHandling::readWholeFile
 * read the csv file and emit the whole file for further use
 * @param filePath
 * path to the csv file in question
 */
void csvHandling::readWholeFile(const QString& filePath){
    class WholeProcessor : public QtCSV::Reader::AbstractProcessor{
    public:
        QList<QStringList> data;

        /**
         * @brief preProccessRawLine
         * fills up empty cells
         * @param line
         * current line getting checked
         */
        virtual void preProccessRawLine(QString& line){
            if(line.isEmpty()){
                line = "Missing Entry";
            }
        }

        /**
         * @brief processRowElements
         * process format of csv file, here it's doing nothing
         * @param elements
         * csv file data
         * @return
         */
        virtual bool processRowElements(const QStringList& elements){
            QList<QString> revertedElements(elements);

            data.push_back(QStringList(revertedElements));
            return true;
        }

    };

    //reads the file and emits the data read
    WholeProcessor processor;
    if(!QtCSV::Reader::readToProcessor(filePath, processor)){
        qWarning() << "Failed to read file";
        emit logMessage("Failed to read csv file;csvHandling", (int)LOG_COMMON);
        return;
    }
    emit logMessage("Read csv file successful;csvHandling", (int)LOG_COMMON);
    emit FillTable(processor.data);
}

/**
 * @brief csvHandling::readLastEntry
 * read only the last line of the csv file
 * @param filePath
 * path to the file in question
 */
void csvHandling::readLastEntry(const QString& filePath){

    class LastEntryProcessor : public QtCSV::Reader::AbstractProcessor{
    public:
        QList<QStringList> data;

        /**
         * @brief preProccessRawLine
         * fills up empty cells
         * @param line
         * current line getting checked
         */
        virtual void preProcessRawLine(QString& line){
            if(line.isEmpty()){
                line = "Missing Entry";
            }
        }

        /**
         * @brief processRowElements
         * process format of csv file, here it's doing nothing
         * @param elements
         * csv file data
         * @return
         */
        virtual bool processRowElements(const QStringList& elements){
            QList<QString> revertedElements(elements);

            data.push_back(QStringList(revertedElements));
            return true;
        }
    };

    //read the file but only emit the last row
    LastEntryProcessor processor;
    if(false == QtCSV::Reader::readToProcessor(filePath, processor)){
        qDebug() << "Failed to read file";
        emit logMessage("Failed to read csv file;csvHandling", (int)LOG_COMMON);
        return;
    }
    emit WriteToTable(processor.data.at(processor.data.size()-1).join(","));

}

/**
 * @brief csvHandling::WriteToFile
 * write the sent data into the csv file at bottom of the file
 * @param filePath
 * path to the csv file in question
 * @param data
 * data to write in the csv file
 */
void csvHandling::WriteToFile(const QString &filePath, QString data){
    QStringList dataList = data.split(QLatin1Char(','));

    QtCSV::VariantData varData;
    varData.addRow(dataList);

    if(!QtCSV::Writer::write(filePath, varData, ",", "\"", QtCSV::Writer::WriteMode::APPEND, {}, {})){
        qDebug() << "Failed to write to file: " << filePath;
        emit logMessage("Failed to write to csv file;csvHandling", (int)LOG_COMMON);
    }

    qDebug() << "Write to " << filePath << " is okay";
    emit logMessage("Write to csv file successfull;csvHandling", (int)LOG_COMMON);
    readLastEntry(filePath);
}
