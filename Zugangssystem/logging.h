#ifndef LOGGING_H
#define LOGGING_H

#include <QString>
#include <QQueue>
#include <QThread>
#include <QFile>
#include <QTimer>
#include <QVector>

#define LOGGING_LOG_FILE_SIZE   2000000
#define NAME_PIPE_IN "/tmp/Zugangssystem_Logging"

typedef enum
{
    LOG_COMMON,
    LOG_BUTTON,
    LOG_SCAN,
    LOG_NO_LOGFILES
}LOG_Type_e;
typedef struct
{
    QString msg;
    int index;
}LOG_QueueEl_t;

class Logging : public QThread
{
    Q_OBJECT

public:
    static Logging* getInstance(void);
    void setLogFileSize(quint32 const maxFileSize);
    QString getLogFileName(int index);

signals:
    void stopCopyLogfiles(void);

public slots:
    void logMessage(QString msg, int index = 0);
    void copyLogfiles(QString destination);
    void logTimeIsvalid(void);

private slots:
    void checkExternalLogging(void);

protected:
    void    run() override;
private:
    Logging(QObject *parent = 0);
    ~Logging();
    QFile* lPLogFile[LOG_NO_LOGFILES];
    static Logging* _instance;
    quint32 lMaxLogFileSize;
    bool lIsTimeValid;

    const char* lLogNames[LOG_NO_LOGFILES] = { "Allgemein", "Verbindung", "Tasten" };

    int lFdPipeIn;
    QTimer* lPCheckExtLog;

    QVector<LOG_QueueEl_t*> lLogQueue;
};

#endif // LOGGING_H
