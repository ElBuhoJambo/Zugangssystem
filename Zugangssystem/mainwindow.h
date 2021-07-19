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

    QGridLayout *loggingLayout;
    QGridLayout *openLayout;
    QGridLayout *rightsLayout;
    QGridLayout *sqlLayout;
    QGridLayout *visualLayout;

    QGridLayout *testLocLayout;
    QPushButton *testLoc1But1;
    QPushButton *testLoc2But1;
    QPushButton *testLoc3But1;
    QPushButton *testLoc1But2;
    QPushButton *testLoc2But2;
    QPushButton *testLoc3But2;
    QLineEdit *testTextEdit;

    QPushButton *showTableButton;
    QPushButton *showAddButton;
    QPushButton *showDeleteButton;
    QFrame *showFrame;
    QFrame *showSpaceFrame;
    QTableWidget *showTableWidget;
    QVBoxLayout *showLayout;

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

private:
    Ui::MainWindow *ui;

signals:
    void ScanInitiated(QString RFID, QString Location);
    void LoggingTest(QString msg, int index);
    void FirstShow();
    void AddWorker(QString RFID, QString location, QString name, QString access);
    void DeleteWorker(QString RFID);

public slots:
    void loc1Clicked1();
    void loc2Clicked1();
    void loc3Clicked1();
    void loc1Clicked2();
    void loc2Clicked2();
    void loc3Clicked2();
    void scanTest();
    void visual(QString name, QString loc, bool access);
    void logMessage(QString msg);
    void sql(QString name, QString RFID, QString loc, QString access);
    void showTable(bool show);
    void hideAdminScreen(bool chip);
    void showTabToolTips();
    void addWorker();
    void deleteWorker();
};
#endif // MAINWINDOW_H
