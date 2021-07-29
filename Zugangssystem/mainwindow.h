#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QTabWidget>
#include <QFrame>
#include <QGridLayout>
#include <QPushButton>
#include <QDateTime>
#include <QTime>
#include <QLineEdit>
#include <QTableWidget>
#include <QTableWidgetItem>

#include <QThread>
#include <QToolTip>
#include <QWhatsThis>

#include <QAbstractSocket>
#include <QUdpSocket>
#include <QHostInfo>
#include <QHostAddress>
#include <QDateTime>

#include <QDir>

//#include "libusb.h"

#define ADMIN_RFID "0004365639"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void scanned(QString RFID, QString loc);
    void showAdminScreen();
    void delay(int millisecondsWait);

    QGridLayout *mainGridLayout;
    QTabWidget *mainTabWidget;
    QFrame *mainTabFrame;
    QFrame *loggingTabFrame;
    QFrame *openTabFrame;
    QFrame *rightsTabFrame;
    QFrame *sqlTabFrame;
    QFrame *visualTabFrame;
    QFrame *csvTabFrame;

    QGridLayout *loggingLayout;
    QGridLayout *openLayout;
    QGridLayout *rightsLayout;
    QGridLayout *sqlLayout;
    QGridLayout *visualLayout;
    QGridLayout *csvLayout;

    QGridLayout *testLocLayout;
    QPushButton *testLoc1But1;
    QPushButton *testLoc2But1;
    QPushButton *testLoc3But1;
    QPushButton *testLoc1But2;
    QPushButton *testLoc2But2;
    QPushButton *testLoc3But2;
    QPushButton *testAdminBut;
    QLineEdit *testTextEdit;

    QPushButton *showTableButton;
    QGridLayout *showAdminLayout;
    QGridLayout *showSortLayout;
    QPushButton *showAddButton;
    QPushButton *showDeleteButton;
    QPushButton *showUpdateButton;
    QPushButton *showEmulateSearch;
    QPushButton *showSortByNameAsc;
    QPushButton *showSortByNameDesc;
    QPushButton *showSortByAccessAsc;
    QPushButton *showSortByAccessDesc;
    QLineEdit *showSearchTable;
    QLabel *showSortByName;
    QLabel *showSortByAccess;
    QFrame *showFrame;
    QFrame *showAdminFrame;
    QFrame *showSortFrame;
    QFrame *showSpaceFrame;
    QTableWidget *showTableWidget;
    QVBoxLayout *showLayout;
    QStringList columns = {"Name", "RFID", "Location", "Access"};

    QPushButton *writeToFile;
    QPushButton *fillCsvTable;
    QTableWidget *csvTable;

    QPushButton *logOutButton = new QPushButton("Log out");
    QLabel *nameLabel = new QLabel("");
    QLabel *locLabel = new QLabel("");
    QLabel *accessLabel = new QLabel("");
    QLabel *timeLabel = new QLabel("");

    QPushButton *toolTipBut = new QPushButton("Info");
    QLabel *spacerLabel = new QLabel("");
    QLabel *statusLabel = new QLabel("");
    QSpacerItem *logOutSpacer = new QSpacerItem(1, 400);
    QWidget *statusWidget = new QWidget;
    QHBoxLayout *statusLayout = new QHBoxLayout(statusWidget);

    int loc;
    int currentScan = 0;
    bool firstShow = true;
    bool adminLogged = false;
    bool toolTip = false;
    bool csvShow = false;

private:
    Ui::MainWindow *ui;

signals:
    void ScanInitiated(QString RFID, QString Location);
    void LoggingTest(QString msg, int index);
    void FirstShow();
    void AddWorker(QString RFID, QString location, QString name, QString access);
    void DeleteWorker(QString RFID);
    void UpdateWorker(QString RFID, QString location, QString name, QString access, QString currRFID);
    void GetWorker();
    void WriteToFile(const QString &filePath, QString data);
    void FillCSVTable(const QString &filePath);
    void GetCurrentTime(bool csv);
    void SaveCurrentTime(QDateTime time);

public slots:
    void loc1Clicked1();
    void loc2Clicked1();
    void loc3Clicked1();
    void loc1Clicked2();
    void loc2Clicked2();
    void loc3Clicked2();
    void adminClicked();
    void scanTest();
    void visual(QString name, QString loc, bool access);
    void logMessage(QString msg);
    void sql(QString name, QString RFID, QString loc, QString access);
    void showTable(bool show);
    void hideAdminScreen(bool chip);
    void showTabToolTips();
    void addWorker();
    void deleteWorker();
    void deleteRowInTable(QString RFID);
    void updateWorker();
    void updateRowInTable(QString RFID, QString location, QString name, QString access, QString currRFID);
    void sortTableByNameAsc();
    void sortTableByAccessAsc();
    void sortTableByNameDesc();
    void sortTableByAccessDesc();
    void searchInTable(QString term);
    void emulateSearch(bool toggle);
    void emulateWriteToFile();
    void writeToFileFuc(QDateTime time);
    void updateCSVTable(QString data);
    void fillCSVTable();
    void fillCSVTable(QList<QStringList> data);


};
#endif // MAINWINDOW_H
