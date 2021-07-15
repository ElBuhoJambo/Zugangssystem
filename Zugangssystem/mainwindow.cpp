#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "sqlcheck.h"
#include "accessrights.h"
#include "opendoor.h"
#include "logging.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mainGridLayout = new QGridLayout;
    mainTabWidget = new QTabWidget;
    mainTabFrame = new QFrame;
    loggingTabFrame = new QFrame;
    openTabFrame = new QFrame;
    rightsTabFrame = new QFrame;
    sqlTabFrame = new QFrame;
    visualTabFrame = new QFrame;

    loggingLayout = new QGridLayout;
    openLayout = new QGridLayout;
    rightsLayout = new QGridLayout;
    sqlLayout = new QGridLayout;
    visualLayout = new QGridLayout;

    testLoc1But1 = new QPushButton("Location 1");
    testLoc2But1 = new QPushButton("Location 2");
    testLoc3But1 = new QPushButton("Location 3");
    testLoc1But2 = new QPushButton("Location 1");
    testLoc2But2 = new QPushButton("Location 2");
    testLoc3But2 = new QPushButton("Location 3");
    testTextEdit = new QLineEdit;
    testTextEdit->setFocus(Qt::OtherFocusReason);
    testTextEdit->grabKeyboard();
    testLocLayout = new QGridLayout;

    showTableButton = new QPushButton("Show Worker Table");
    showTableButton->setCheckable(true);
    showTableButton->setFixedWidth(460);
    showSpaceButton = new QPushButton("Spacer");
    showSpaceButton->hide();
    showFrame = new QFrame;
    showFrame->setMaximumWidth(460);
    showFrame->hide();
    showSpaceFrame = new QFrame;
    showTableWidget = new QTableWidget(0,4,this);
    showLayout = new QVBoxLayout;
    showLayout->setAlignment(Qt::AlignTop);
    showLayout->setSpacing(0);
    showLayout->addWidget(showTableWidget);
    sqlLayout->addWidget(showTableButton,0,0);
    sqlLayout->addWidget(showFrame, 1,0);
    sqlLayout->addWidget(showSpaceButton,0,1);
    sqlLayout->addWidget(showSpaceFrame, 1,1);
    showFrame->setLayout(showLayout);
    sqlTabFrame->setLayout(sqlLayout);

    ui->centralwidget->setLayout(mainGridLayout);

    statusLabel->setFixedWidth(150);
    toolTipBut->setFixedWidth(100);
    toolTipBut->setCheckable(true);
    statusLabel->setText("Version 1.0");
    //statusLayout->addWidget(spacerLabel,0,Qt::AlignLeft);
    //statusLayout->addWidget(statusLabel,0,Qt::AlignLeft);
    //statusLayout->addWidget(toolTipBut,0,Qt::AlignCenter);

    ui->statusbar->addWidget(statusLabel,0);
    ui->statusbar->addPermanentWidget(toolTipBut,1);

    mainTabWidget->addTab(mainTabFrame, "Hauptmenu");
    mainTabWidget->addTab(loggingTabFrame, "Logging");
    mainTabWidget->addTab(openTabFrame, "Öffne Tür");
    mainTabWidget->addTab(rightsTabFrame, "Rechte");
    mainTabWidget->addTab(sqlTabFrame, "SQL");
    mainTabWidget->addTab(visualTabFrame, "Visual on Screen");

    mainGridLayout->addWidget(mainTabWidget);

    testLocLayout->addWidget(testLoc1But1,1,1);
    testLocLayout->addWidget(testLoc2But1,1,2);
    testLocLayout->addWidget(testLoc3But1,1,3);
    testLocLayout->addWidget(testLoc1But2,2,1);
    testLocLayout->addWidget(testLoc2But2,2,2);
    testLocLayout->addWidget(testLoc3But2,2,3);
    testLocLayout->addWidget(testTextEdit,4,4);
    mainTabFrame->setLayout(testLocLayout);

    visualLayout->setAlignment(Qt::AlignTop);
    visualLayout->setSpacing(0);
    visualTabFrame->setLayout(visualLayout);


    loggingLayout->setAlignment(Qt::AlignTop);
    loggingLayout->setSpacing(0);
    loggingTabFrame->setLayout(loggingLayout);

    visualLayout->addWidget(logOutButton,10,0, 1, 1, Qt::AlignBottom);
    visualLayout->addItem(logOutSpacer,3,0,1,1);
    logOutButton->hide();

    connect(openDoor::getInstance(),SIGNAL(Rights(QString, QString)),accessRights::getInstance(),SLOT(checkAccess(QString, QString)));
    connect(accessRights::getInstance(),SIGNAL(SQLRequest(QString, QString)),sqlCheck::getInstance(),SLOT(receiveRequest(QString, QString)));
    connect(accessRights::getInstance(),SIGNAL(Visual(QString, QString, bool)),this, SLOT(visual(QString, QString, bool)));
    connect(accessRights::getInstance(),SIGNAL(Door(bool, QString)),openDoor::getInstance(), SLOT(rightsReturned(bool, QString)));
    connect(sqlCheck::getInstance(),SIGNAL(Result(bool, QString, QString, QString)),accessRights::getInstance(), SLOT(receiveResult(bool, QString, QString, QString)));
    connect(this, SIGNAL(ScanInitiated(QString, QString)), openDoor::getInstance(), SLOT(checkAccess(QString, QString)));
    connect(sqlCheck::getInstance(), SIGNAL(ShowTable(QString,QString,QString,QString)), this, SLOT(sql(QString,QString,QString,QString)));

    connect(testLoc1But1, SIGNAL(clicked()), this, SLOT(loc1Clicked1()));
    connect(testLoc2But1, SIGNAL(clicked()), this, SLOT(loc2Clicked1()));
    connect(testLoc3But1, SIGNAL(clicked()), this, SLOT(loc3Clicked1()));
    connect(testLoc1But2, SIGNAL(clicked()), this, SLOT(loc1Clicked2()));
    connect(testLoc2But2, SIGNAL(clicked()), this, SLOT(loc2Clicked2()));
    connect(testLoc3But2, SIGNAL(clicked()), this, SLOT(loc3Clicked2()));
    connect(testTextEdit, SIGNAL(returnPressed()), this, SLOT(scanTest()));
    connect(showTableButton, SIGNAL(toggled(bool)), this, SLOT(showTable(bool)));
    connect(this, SIGNAL(FirstShow()), sqlCheck::getInstance(), SLOT(showTable()));
    connect(logOutButton, SIGNAL(clicked()),this, SLOT(hideAdminScreen()));
    connect(toolTipBut, SIGNAL(clicked(bool)), this, SLOT(showTabToolTips(bool)));

    connect(this, SIGNAL(LoggingTest(QString,int)), Logging::getInstance(), SLOT(logMessage(QString, int)));
    connect(Logging::getInstance(), SIGNAL(LogMessageTest(QString)), this, SLOT(logMessage(QString)));
    connect(openDoor::getInstance(), SIGNAL(logMessage(QString, int)), Logging::getInstance(), SLOT(logMessage(QString, int)));
    connect(accessRights::getInstance(), SIGNAL(logMessage(QString, int)), Logging::getInstance(), SLOT(logMessage(QString, int)));
    connect(sqlCheck::getInstance(), SIGNAL(logMessage(QString, int)), Logging::getInstance(), SLOT(logMessage(QString, int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showTabToolTips(bool show){
    int index = mainTabWidget->currentIndex();
    toolTip = show;

    switch(index){
    case 0:
        while(toolTip){
            QToolTip::showText(QPoint(80,155),"Scan Location 1 Test", testLoc1But1, QRect(), 1000);
            delay(1000);
            QToolTip::showText(QPoint(185,155),"Scan Location 2 Test", testLoc2But1, QRect(), 1000);
            delay(1000);
            QToolTip::showText(QPoint(290,155),"Scan Location 3 Test", testLoc3But1, QRect(), 1000);
            delay(1000);
            QToolTip::showText(QPoint(80,290),"Scan Location 1 Test", testLoc1But2, QRect(), 1000);
            delay(1000);
            QToolTip::showText(QPoint(185,290),"Scan Location 2 Test", testLoc2But2, QRect(), 1000);
            delay(1000);
            QToolTip::showText(QPoint(290,290),"Scan Location 3 Test", testLoc3But2, QRect(), 1000);
            delay(1000);
            QToolTip::showText(QPoint(600,425),"QLineEdit for scanning the RFID", testTextEdit, QRect(), 2000);
            delay(2000);
        }
        break;
    case 1:
        while(toolTip){
            QToolTip::showText(QPoint(100,100), "Logging Output", loggingTabFrame, QRect(), 1000);
            delay(1000);
        }
        break;
    case 2:
        while(toolTip){
            QToolTip::showText(QPoint(100,100), "Nothing yet", openTabFrame, QRect(), 1000);
            delay(1000);
        }
        break;
    case 3:
        while(toolTip){
            QToolTip::showText(QPoint(100,100), "Nothing yet", rightsTabFrame, QRect(), 1000);
            delay(1000);
        }
        break;
    case 4:
        while(toolTip){
            QToolTip::showText(QPoint(460,50),"Toggle whether the worker table is shown or not!", showTableButton, QRect(), 1000);
            delay(1000);
            QToolTip::showText(QPoint(400,200),"Worker table", showTableWidget, QRect(), 1000);
            delay(1000);
        }

        break;
    case 5:
        while(toolTip){
            QToolTip::showText(QPoint(100,100), "Visual output for the scan", openTabFrame, QRect(), 1000);
            delay(1000);
            if(logOutButton->isVisible()){
                QToolTip::showText(QPoint(400,500), "Logout button for the admin", logOutButton, QRect(), 1000);
                delay(1000);
            }

        }
        break;
    }

}

void MainWindow::delay(int millisecondsWait){
    QEventLoop loop;
    QTimer t;
    t.connect(&t, &QTimer::timeout, &loop, &QEventLoop::quit);
    t.start(millisecondsWait);
    loop.exec();
}

void MainWindow::showTable(bool show){
    if(firstShow){
        emit FirstShow();
        firstShow = false;
        showFrame->show();
    }else{
        if(show){
            showFrame->show();
        }else{
            showFrame->hide();
        }
    }
}

void MainWindow::sql(QString name, QString RFID, QString loc, QString access){
    showTableWidget->setRowCount(showTableWidget->rowCount()+1);
    QTableWidgetItem *nameItem = new QTableWidgetItem(name);
    QTableWidgetItem *rfidItem = new QTableWidgetItem(RFID);
    QTableWidgetItem *locItem = new QTableWidgetItem(loc);
    QTableWidgetItem *accessItem = new QTableWidgetItem();

    if(access == 1){
        accessItem->setText("Granted");
    }else{
        accessItem->setText("Denied");
    }

    showTableWidget->setItem(showTableWidget->rowCount()-1, 0, nameItem);
    showTableWidget->setItem(showTableWidget->rowCount()-1, 1, rfidItem);
    showTableWidget->setItem(showTableWidget->rowCount()-1, 2, locItem);
    showTableWidget->setItem(showTableWidget->rowCount()-1, 3, accessItem);

}

void MainWindow::scanTest(){
    QString RFID = testTextEdit->text();
    testTextEdit->clear();
    scanned(RFID, QString("Location 1"));
    if(adminLogged && RFID == ADMIN_RFID){
        qDebug() << "Admin already logged in";
    }else if(adminLogged && RFID != ADMIN_RFID){
        qDebug() << "Admin is gone";
        hideAdminScreen();
    }else{
        if(RFID == ADMIN_RFID){
            qDebug() << "Admin RFID";
            showAdminScreen();
        }else{
            qDebug() << "Regular worker";
            hideAdminScreen();
        }
    }

}

void MainWindow::showAdminScreen(){
    adminLogged = true;
    logOutButton->show();
    ui->statusbar->showMessage("admin logged in");
    emit LoggingTest(";admin logged in",(int)LOG_COMMON);
}

void MainWindow::hideAdminScreen(){
    logOutButton->hide();
    ui->statusbar->showMessage("admin gone");
    adminLogged = false;
    emit LoggingTest(";admin logged out",(int)LOG_COMMON);
}

/**
 * @brief MainWindow::visual
 * Slot for the visual output of the access check
 * @param name
 * Name of the chip owner
 * @param loc
 * Location that the chip was scanned at
 * @param access
 * True if access is granted
 * False if not
 */
void MainWindow::visual(QString name, QString loc, bool access){
    QDateTime curTime = QDateTime::currentDateTime();
    nameLabel->setText(QString("Willkommen %1").arg(name));
    locLabel->setText(loc);
    if(access){
        accessLabel->setText("Access granted");
    }else{
        accessLabel->setText("Access denied");
    }
    timeLabel->setText(QString("Einstechzeit: %1").arg(curTime.toString("hh:mm:ss")));

    locLabel->setStyleSheet("");

    visualLayout->addWidget(nameLabel, 1, 0);
    visualLayout->addWidget(locLabel, 2, 0);
    visualLayout->addWidget(accessLabel, 1, 2);
    visualLayout->addWidget(timeLabel,2,2);

    mainTabWidget->setCurrentIndex(5);
}

/**
 * @brief MainWindow::loc1Clicked
 * slot for scan at location 1
 */
void MainWindow::loc1Clicked1(){
    scanned(QString::number(120721), QString("Location 1"));
}

/**
 * @brief MainWindow::loc2Clicked
 * slot for scan at location 2
 */
void MainWindow::loc2Clicked1(){
    scanned(QString::number(1207), QString("Location 2"));
}

/**
 * @brief MainWindow::loc3Clicked
 * slot for scan at location 3
 */
void MainWindow::loc3Clicked1(){
    scanned(QString::number(160302),QString("Location 3"));
}

/**
 * @brief MainWindow::loc1Clicked
 * slot for scan at location 1
 */
void MainWindow::loc1Clicked2(){
    scanned(QString::number(210712), QString("Location 1"));
}

/**
 * @brief MainWindow::loc2Clicked
 * slot for scan at location 2
 */
void MainWindow::loc2Clicked2(){
    scanned(QString::number(120316), QString("Location 2"));
}

/**
 * @brief MainWindow::loc3Clicked
 * slot for scan at location 3
 */
void MainWindow::loc3Clicked2(){
    scanned(QString::number(0712), QString("Location 3"));
}

/**
 * @brief MainWindow::scanned
 * function for scan processing
 * @param loc
 * Location that the chip was scanned at
 */
void MainWindow::scanned(QString RFID, QString loc){
    emit ScanInitiated(RFID, loc);

    if(RFID.length() == 10){
        loc.append(";RFID: ").append(RFID);
        emit LoggingTest(loc, 0);
    }else{
        qDebug() << "RFID is in a faulty format";
        //emit LoggingTest(QString("UID is in a faulty format; UID: ").append(QString::number(UID)), 1);
    }


}

/**
 * @brief MainWindow::logTest
 * test function for logging
 * @param msg
 * Message that was logged
 */
void MainWindow::logMessage(QString msg){
    QString log = msg.remove(msg.length()-1, msg.length());
    QLabel *testLabel = new QLabel(log);
    loggingLayout->addWidget(testLabel, currentScan, 0);
    currentScan += 1;
}
