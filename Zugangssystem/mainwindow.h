#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include <QTime>

#include <QThread>
#include <QWhatsThis>

#include <QAbstractSocket>
#include <QUdpSocket>
#include <QHostInfo>
#include <QHostAddress>
#include <QDateTime>

#include <QDir>
#include <QSettings>

#include "sqlcheck.h"
#include "accessrights.h"
#include "opendoor.h"
#include "logging.h"
#include "csvhandling.h"
#include "scanner.h"
#include "keyboard/keyboard.h"
#include "logoutuser.h"

#include "math.h"

//#include "libusb.h"

#define ADMIN_RFID "0004365639"

typedef enum{
    EmptySpacer,
    Software,
    Hardware,
    Produktion,
    Buero
} UserGroups_type;

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
    void grabKeyboard();
    void disableDisplayKeyboard();
    void setColorScheme(int index, QString font);

    QGridLayout *mainGridLayout;
    QTabWidget *mainTabWidget;
    QFrame *mainTabFrame;
    QFrame *loggingTabFrame;
    QFrame *openTabFrame;
    QFrame *settingsTabFrame;
    QFrame *sqlTabFrame;
    QFrame *visualTabFrame;
    QFrame *csvTabFrame;

    QGridLayout *loggingLayout;
    QGridLayout *openLayout;
    QGridLayout *settingsLayout;
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

    QPushButton *showTableButton;
    QGridLayout *showAdminLayout;
    QGridLayout *showSortLayout;
    QPushButton *showAddButton;
    QPushButton *showDeleteButton;
    QPushButton *showUpdateButton;
    QPushButton *showEmulateSearch;
    QPushButton *showAllButton;
    QLineEdit *showAdminLineEdit;
    QLineEdit *showAdminUserIdEdit;
    QLineEdit *showAdminRFIDLineEdit;
    QLineEdit *showAdminNameLineEdit;
    QLineEdit *showAdminGroupsLineEdit;
    QLineEdit *showAdminActivateLineEdit;
    QPushButton *showAdminSubmit;
    QPushButton *showAdminCancel;
    QPushButton *showSortByNameAsc;
    QPushButton *showSortByNameDesc;
    QPushButton *showSortByIdAsc;
    QPushButton *showSortByIdDesc;
    QLineEdit *showSearchTable;
    QLabel *showSortByName;
    QLabel *showSortById;
    QFrame *showFrame;
    QFrame *showAdminFrame;
    QFrame *showSortFrame;
    QFrame *showSpaceFrame;
    QTableWidget *showTableWidget;
    QVBoxLayout *showLayout;
    QStringList columns = {"Id", "Name", "RFID", "Groups", "Rights"};
    QString currAdminEdit;

    QPushButton *writeToFile;
    QPushButton *fillCsvTable;
    QTableWidget *csvTable;
    QPushButton *calcWeeklyHours;
    QPushButton *calcMonthlyHours;
    QPushButton *calcOvertime;
    QPushButton *calcNeededTime;

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

    QSettings *settings;
    QCheckBox *keyboardEnabled;
    QComboBox *standardSortDrop;
    QStringList standardSort = {"User Id Asc","User Id Desc","Name A-Z","Name Z-A"};
    QComboBox *colorSchemeDrop;
    QStringList colorScheme = {"Light Mode", "Dark Mode", "Ocean", "Fire"};
    QFontComboBox *fontDrop;
    QCheckBox *autoLogout;
    QDialogButtonBox *settingsSaveCancel;


    QRegExp RFID;
    QRegExp name;
    QRegExp access;

    Keyboard *lineEditKeyboard;

    int loc;
    int currentScan = 0;
    bool firstShow = true;
    bool adminLogged = false;
    bool toolTip = false;
    bool csvShow = false;
    bool hourBox = true;

private:
    Ui::MainWindow *ui;

signals:
    /**
     * @brief ScanInitiated
     * emits when a chip was scanned or a button to emulate was pressed to start the checking process
     * @param RFID
     * scanned RFID
     * @param Location
     * location of scan
     */
    void ScanInitiated(QString RFID, QString Location);

    /**
     * @brief LoggingTest
     * emits to log a certain event
     * @param msg
     * logging message
     * @param index
     * specifies which file it should be logged in
     */
    void LoggingTest(QString msg, int index);

    /**
     * @brief FirstShow
     * emits when the worker table gets shown for the first time to fill it up
     */
    void FirstShow();

    /**
     * @brief AddWorker
     * emits to add a worker to the database and table
     * @param RFID
     * RFID of worker
     * @param location
     * location of worker
     * @param name
     * name of worker
     * @param access
     * access status of worker
     */
    void AddWorker(QString userId, QString RFID, QString name, QList<int> groups);

    /**
     * @brief DeleteWorker
     * emits to delete a worker from the database and table
     * @param RFID
     * RFID of worker to be deleted
     */
    void DeleteWorker(QString userId);

    /**
     * @brief UpdateWorker
     * emits to update worker in the database and table
     * @param RFID
     * new or same RFID
     * @param location
     * new or same location
     * @param name
     * new or same name
     * @param access
     * new or same access status
     * @param currRFID
     * current RFID
     */
    void UpdateWorker(QString currUserId, QString userId, QString RFID, QString name, QList<int> groups, QString active);

    /**
     * @brief GetWorker
     * emits to get all names of the worker
     */
    void GetWorker();

    /**
     * @brief WriteToFile
     * emits to write to csv file when chip was scanned
     * @param filePath
     * filepath of the csv file for the worker
     * @param data
     * data to write into the csv file
     */
    void WriteToFile(const QString &filePath, QString data);

    /**
     * @brief FillCSVTable
     * emits to fill the table with the data of the csv file of the worker
     * @param filePath
     * filepath of the csv file for the worker
     */
    void FillCSVTable(const QString &filePath);

    /**
     * @brief GetCurrentTime
     * emits to get the last saved time
     * @param csv
     * always true
     * @param name
     * name of the current worker
     */
    void GetCurrentTime(bool csv,QString name);

    /**
     * @brief PutCurrentOnTop
     * emits to put the current worker on top of the sql table
     * @param RFID
     * RFID of the worker
     */
    void PutCurrentOnTop(QString RFID);

public slots:
    void loc1Clicked1();
    void loc2Clicked1();
    void loc3Clicked1();
    void loc1Clicked2();
    void loc2Clicked2();
    void loc3Clicked2();
    void adminClicked();
    void scanTest(QString rfid);
    void visual(QString name, QString RFID);
    void logMessage(QString msg);
    void sql(QList<QStringList> result);
    void showTable(bool show);
    void hideAdminScreen(bool chip);
    void showTabToolTips();
    void addWorker();
    void deleteWorker();
    void deleteRowInTable(QString userId);
    void updateWorker();
    void updateRowInTable(QString userId, QList<QStringList> result);
    void sortTableByNameAsc();
    void sortTableByIdAsc();
    void sortTableByNameDesc();
    void sortTableByIdDesc();
    void searchInTable(QString term);
    void emulateSearch(bool toggle);
    void showAll();
    void putCurrentOnTop(QString RFID);
    void emulateWriteToFile();
    void writeToFileFuc(QDateTime time, QString name);
    void updateCSVTable(QString data);
    void fillCSVTable();
    void fillCSVTable(QList<QStringList> data);
    double calcWeekHours();
    void calcMonthHours();
    void calcOverTime();
    void calcNeedTime();
    void showKeyboardLineEdit();
    void adminAccept();
    void adminCancel();
    void saveSettings();
    void restoreSettings();
    void logoutWorker();

};
#endif // MAINWINDOW_H
