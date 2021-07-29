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
    csvTabFrame = new QFrame;

    loggingLayout = new QGridLayout;
    openLayout = new QGridLayout;
    rightsLayout = new QGridLayout;
    sqlLayout = new QGridLayout;
    visualLayout = new QGridLayout;
    csvLayout = new QGridLayout;

    testLoc1But1 = new QPushButton("Location 1 \nCorrect RFID");
    testLoc2But1 = new QPushButton("Location 2 \nCorrect RFID");
    testLoc3But1 = new QPushButton("Location 3 \nCorrect RFID");
    testLoc1But2 = new QPushButton("Location 1 \nFaulty RFID");
    testLoc2But2 = new QPushButton("Location 2 \nFaulty RFID");
    testLoc3But2 = new QPushButton("Location 3 \nFaulty RFID");
    testAdminBut = new QPushButton("Admin Emulation");
    testTextEdit = new QLineEdit;
    testTextEdit->setFocus(Qt::OtherFocusReason);
    testTextEdit->grabKeyboard();
    testLocLayout = new QGridLayout;

    showTableButton = new QPushButton("Show worker table");
    showTableButton->setCheckable(true);
    showTableButton->setFixedWidth(460);
    showAddButton = new QPushButton("Add worker");
    showDeleteButton = new QPushButton("Delete worker");
    showUpdateButton = new QPushButton("Update worker");
    showEmulateSearch = new QPushButton("Emulate a search");
    showEmulateSearch->setCheckable(true);
    showSortByNameAsc = new QPushButton("Ascending");
    showSortByAccessAsc = new QPushButton("Ascending");
    showSortByNameDesc = new QPushButton("Descending");
    showSortByAccessDesc = new QPushButton("Descending");
    showSearchTable = new QLineEdit();
    showSearchTable->setPlaceholderText("RFID");
    showSortByName = new QLabel("Sort by name");
    showSortByAccess = new QLabel("Sort by access");
    showFrame = new QFrame;
    showFrame->setMaximumWidth(460);
    showFrame->resize(460,460);
    showFrame->hide();
    showSortFrame = new QFrame;
    showSpaceFrame = new QFrame;
    showAdminFrame = new QFrame;
    showAdminFrame->hide();
    showTableWidget = new QTableWidget(0,4,this);
    showTableWidget->setColumnWidth(1,125);
    showTableWidget->setColumnWidth(3,84);
    showTableWidget->setHorizontalHeaderLabels(columns);
    showLayout = new QVBoxLayout;
    showAdminLayout = new QGridLayout;
    showSortLayout = new QGridLayout;
    showAdminLayout->setAlignment(Qt::AlignTop);
    showLayout->setAlignment(Qt::AlignTop);
    showLayout->setSpacing(0);
    showLayout->addWidget(showTableWidget);
    showSortLayout->addWidget(showSearchTable,0,0,1,2,Qt::AlignBottom);
    showSortLayout->addWidget(showSortByName,1,0,Qt::AlignBottom);
    showSortLayout->addWidget(showSortByAccess,1,1,Qt::AlignBottom);
    showSortLayout->addWidget(showSortByNameAsc,2,0,Qt::AlignBottom);
    showSortLayout->addWidget(showSortByAccessAsc,2,1,Qt::AlignBottom);
    showSortLayout->addWidget(showSortByNameDesc,3,0);
    showSortLayout->addWidget(showSortByAccessDesc,3,1);
    sqlLayout->addWidget(showTableButton,0,0, Qt::AlignTop);
    sqlLayout->addWidget(showFrame, 1,0);
    showAdminLayout->addWidget(showAddButton,0,0);
    showAdminLayout->addWidget(showDeleteButton,1,0,Qt::AlignTop);
    showAdminLayout->addWidget(showUpdateButton,2,0,Qt::AlignTop);
    showAdminLayout->addWidget(showEmulateSearch,3,0,Qt::AlignTop);
    sqlLayout->addWidget(showSortFrame, 3,1);
    sqlLayout->addWidget(showSpaceFrame, 2,1);
    sqlLayout->addWidget(showAdminFrame, 0,1,2,1);
    showAdminFrame->setLayout(showAdminLayout);
    showFrame->setLayout(showLayout);
    showSortFrame->setLayout(showSortLayout);
    sqlTabFrame->setLayout(sqlLayout);

    ui->centralwidget->setLayout(mainGridLayout);

    statusLabel->setFixedWidth(150);
    toolTipBut->setFixedWidth(100);
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
    mainTabWidget->addTab(csvTabFrame, "CSV");
    mainTabWidget->addTab(visualTabFrame, "Visual on Screen");

    mainGridLayout->addWidget(mainTabWidget);

    testLocLayout->addWidget(testLoc1But1,1,1);
    testLocLayout->addWidget(testLoc2But1,1,2);
    testLocLayout->addWidget(testLoc3But1,1,3);
    testLocLayout->addWidget(testLoc1But2,2,1);
    testLocLayout->addWidget(testLoc2But2,2,2);
    testLocLayout->addWidget(testLoc3But2,2,3);
    testLocLayout->addWidget(testAdminBut,3,2);
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

    testLoc1But1->setWhatsThis("Emulate scan for Location 1");
    testLoc2But1->setWhatsThis("Emulate scan for Location 2");
    testLoc3But1->setWhatsThis("Emulate scan for Location 3");
    testLoc1But2->setWhatsThis("Emulate scan for Location 1");
    testLoc2But2->setWhatsThis("Emulate scan for Location 2");
    testLoc3But2->setWhatsThis("Emulate scan for Location 3");
    testTextEdit->setWhatsThis("Reads the RFID from the chip");
    showTableButton->setWhatsThis("Show the worker table");
    showAddButton->setWhatsThis("Add a worker via text input");
    showDeleteButton->setWhatsThis("Delete a worker via text input");
    showUpdateButton->setWhatsThis("Update a worker via text input");
    showTableWidget->setWhatsThis("Worker table");
    logOutButton->setWhatsThis("Log out of admin mode");
    nameLabel->setWhatsThis("Name of the currently scanned worker");
    locLabel->setWhatsThis("Location of the currently scanned worker");
    accessLabel->setWhatsThis("Output whether or not access is to this location is granted");
    timeLabel->setWhatsThis("Time the currently scanned worker scanned in");

    connect(openDoor::getInstance(),SIGNAL(Rights(QString, QString)),accessRights::getInstance(),SLOT(checkAccess(QString, QString)));
    connect(accessRights::getInstance(),SIGNAL(SQLRequest(QString, QString)),sqlCheck::getInstance(),SLOT(receiveRequest(QString, QString)));
    connect(accessRights::getInstance(),SIGNAL(Visual(QString, QString, bool)),this, SLOT(visual(QString, QString, bool)));
    connect(accessRights::getInstance(),SIGNAL(Door(bool, QString)),openDoor::getInstance(), SLOT(rightsReturned(bool, QString)));
    connect(sqlCheck::getInstance(),SIGNAL(Result(bool, QString, QString, QString)),accessRights::getInstance(), SLOT(receiveResult(bool, QString, QString, QString)));
    connect(this, SIGNAL(ScanInitiated(QString, QString)), openDoor::getInstance(), SLOT(checkAccess(QString, QString)));
    connect(sqlCheck::getInstance(), SIGNAL(ShowTable(QString,QString,QString,QString)), this, SLOT(sql(QString,QString,QString,QString)));
    connect(this, SIGNAL(AddWorker(QString, QString, QString, QString)), sqlCheck::getInstance(), SLOT(addWorker(QString, QString, QString, QString)));
    connect(this, SIGNAL(DeleteWorker(QString)), sqlCheck::getInstance(), SLOT(deleteWorker(QString)));
    connect(sqlCheck::getInstance(), SIGNAL(DeleteRow(QString)), this, SLOT(deleteRowInTable(QString)));
    connect(this, SIGNAL(UpdateWorker(QString, QString, QString, QString, QString)), sqlCheck::getInstance(), SLOT(updateWorker(QString, QString, QString, QString, QString)));
    connect(sqlCheck::getInstance(), SIGNAL(UpdateWorker(QString, QString, QString, QString, QString)), this, SLOT(updateRowInTable(QString, QString, QString, QString, QString)));

    connect(testLoc1But1, SIGNAL(clicked()), this, SLOT(loc1Clicked1()));
    connect(testLoc2But1, SIGNAL(clicked()), this, SLOT(loc2Clicked1()));
    connect(testLoc3But1, SIGNAL(clicked()), this, SLOT(loc3Clicked1()));
    connect(testLoc1But2, SIGNAL(clicked()), this, SLOT(loc1Clicked2()));
    connect(testLoc2But2, SIGNAL(clicked()), this, SLOT(loc2Clicked2()));
    connect(testLoc3But2, SIGNAL(clicked()), this, SLOT(loc3Clicked2()));
    connect(testAdminBut, SIGNAL(clicked()), this, SLOT(adminClicked()));
    connect(testTextEdit, SIGNAL(returnPressed()), this, SLOT(scanTest()));
    connect(showTableButton, SIGNAL(toggled(bool)), this, SLOT(showTable(bool)));
    connect(this, SIGNAL(FirstShow()), sqlCheck::getInstance(), SLOT(showTable()));
    connect(logOutButton, SIGNAL(clicked(bool)),this, SLOT(hideAdminScreen(bool)));
    connect(toolTipBut, SIGNAL(clicked()), this, SLOT(showTabToolTips()));
    connect(showAddButton, SIGNAL(clicked()), this, SLOT(addWorker()));
    connect(showDeleteButton, SIGNAL(clicked()), this, SLOT(deleteWorker()));
    connect(showUpdateButton, SIGNAL(clicked()), this, SLOT(updateWorker()));
    connect(showEmulateSearch, SIGNAL(toggled(bool)), this, SLOT(emulateSearch(bool)));
    connect(showSortByNameAsc, SIGNAL(clicked()), this, SLOT(sortTableByNameAsc()));
    connect(showSortByAccessAsc, SIGNAL(clicked()), this, SLOT(sortTableByAccessAsc()));
    connect(showSortByNameDesc, SIGNAL(clicked()), this, SLOT(sortTableByNameDesc()));
    connect(showSortByAccessDesc, SIGNAL(clicked()), this, SLOT(sortTableByAccessDesc()));
    connect(showSearchTable, SIGNAL(textChanged(QString)), this, SLOT(searchInTable(QString)));

    connect(this, SIGNAL(LoggingTest(QString,int)), Logging::getInstance(), SLOT(logMessage(QString, int)));
    connect(Logging::getInstance(), SIGNAL(LogMessageTest(QString)), this, SLOT(logMessage(QString)));
    connect(openDoor::getInstance(), SIGNAL(logMessage(QString, int)), Logging::getInstance(), SLOT(logMessage(QString, int)));
    connect(accessRights::getInstance(), SIGNAL(logMessage(QString, int)), Logging::getInstance(), SLOT(logMessage(QString, int)));
    connect(sqlCheck::getInstance(), SIGNAL(logMessage(QString, int)), Logging::getInstance(), SLOT(logMessage(QString, int)));

    emit LoggingTest("program started", (int)LOG_COMMON);
}

MainWindow::~MainWindow()
{
    delete ui;

}

/**
 * @brief MainWindow::updateWorker
 * update a worker via text input
 */
void MainWindow::updateWorker(){
    //Some way of getting a text input
    //emit UpdateWorker("001234567","Location 2","Justin","false","0005155165");
    qDebug() << "no worker updated because no text input";
    emit LoggingTest(";update worker button pressed", (int)LOG_BUTTON);
}

/**
 * @brief MainWindow::deleteWorker
 * delete a worker via text input
 */
void MainWindow::deleteWorker(){
    //Some way of getting a text input
    //Maybe Qt Virtual Keyboard
    //emit DeleteWorker("0001907202");
    qDebug() << "no worker deleted because no text input";
    emit LoggingTest("delete worker button pressed", (int)LOG_BUTTON);
}

/**
 * @brief MainWindow::addWorker
 * add a worker via text input
 */
void MainWindow::addWorker(){
    //Some way of getting a text input?
    //emit AddWorker("0001907202","Location 1","Simon","true");
    qDebug() << "no worker added because no text input";
    emit LoggingTest("add worker button pressed", (int)LOG_BUTTON);
}

/**
 * @brief MainWindow::showTabToolTips
 * enter whatsthis mode
 */
void MainWindow::showTabToolTips(){
    QWhatsThis::enterWhatsThisMode();
    emit LoggingTest("info button pressed", (int)LOG_BUTTON);
}

/**
 * @brief MainWindow::delay
 * programm sleeps for a certain time without halting the ui
 * @param millisecondsWait
 * time of sleep in milliseconds
 */
void MainWindow::delay(int millisecondsWait){
    QEventLoop loop;
    QTimer t;
    t.connect(&t, &QTimer::timeout, &loop, &QEventLoop::quit);
    t.start(millisecondsWait);
    loop.exec();
}

/**
 * @brief MainWindow::showTable
 * show or hide worker table
 * @param show
 * decides whether the table is shown or hidden
 */
void MainWindow::showTable(bool show){
    if(firstShow){
        emit FirstShow();
        firstShow = false;
        showFrame->show();
        emit LoggingTest("show table button pressed;first time", (int)LOG_BUTTON);
    }else{
        if(show){
            showFrame->show();
            emit LoggingTest("show table button pressed;show", (int)LOG_BUTTON);
        }else{
            showFrame->hide();
            emit LoggingTest("show table button pressed;hide", (int)LOG_BUTTON);
        }
    }
}

/**
 * @brief MainWindow::sql
 * add worker to table
 * @param name
 * name of the current worker getting added
 * @param RFID
 * RFID of the current worker getting added
 * @param loc
 * location of the current worker getting added
 * @param access
 * access status of the current worker getting added
 */
void MainWindow::sql(QString name, QString RFID, QString loc, QString access){
    showTableWidget->setRowCount(showTableWidget->rowCount()+1);
    QTableWidgetItem *nameItem = new QTableWidgetItem(name);
    QTableWidgetItem *rfidItem = new QTableWidgetItem(RFID);
    QTableWidgetItem *locItem = new QTableWidgetItem(loc);
    QTableWidgetItem *accessItem = new QTableWidgetItem();

    if(access == "1"){
        accessItem->setText("Granted");
    }else{
        accessItem->setText("Denied");
    }

    showTableWidget->setItem(showTableWidget->rowCount()-1, 0, nameItem);
    showTableWidget->setItem(showTableWidget->rowCount()-1, 1, rfidItem);
    showTableWidget->setItem(showTableWidget->rowCount()-1, 2, locItem);
    showTableWidget->setItem(showTableWidget->rowCount()-1, 3, accessItem);
}

/**
 * @brief MainWindow::deleteRowInTable
 * update the showing table;delete
 * @param RFID
 * RFID of the deleted worker
 */
void MainWindow::deleteRowInTable(QString RFID){
    QList<QTableWidgetItem *> toRemove = showTableWidget->findItems(RFID,Qt::MatchExactly);
    if(!toRemove.isEmpty()){
        showTableWidget->removeRow(toRemove[0]->row());
    }else{
        qDebug() << "Nothing removed, no worker found";
    }
}

/**
 * @brief MainWindow::updateRowInTable
 * update the showing table;update
 * @param RFID
 * new RFID
 * @param location
 * new location
 * @param name
 * new name
 * @param access
 * new access status
 * @param currRFID
 * old RFID
 */
void MainWindow::updateRowInTable(QString RFID, QString location, QString name, QString access, QString currRFID){
    QList<QTableWidgetItem *> toUpdate = showTableWidget->findItems(currRFID,Qt::MatchExactly);

    if(access == "true"){
        access = "Granted";
    }else{
        access = "Denied";
    }

    if(!toUpdate.isEmpty()){
        showTableWidget->item(toUpdate[0]->row(), 0)->setText(name);
        showTableWidget->item(toUpdate[0]->row(), 1)->setText(RFID);
        showTableWidget->item(toUpdate[0]->row(), 2)->setText(location);
        showTableWidget->item(toUpdate[0]->row(), 3)->setText(access);
    }else{

    }
}

/**
 * @brief MainWindow::sortTableByNameAsc
 * does what it says on the tin
 */
void MainWindow::sortTableByNameAsc(){
    showTableWidget->sortItems(0,Qt::AscendingOrder);
}
/**
 * @brief MainWindow::sortTableByAccessAsc
 * does what it says on the tin
 */
void MainWindow::sortTableByAccessAsc(){
    showTableWidget->sortItems(3,Qt::AscendingOrder);
}
/**
 * @brief MainWindow::sortTableByNameDesc
 * does what it says on the tin
 */
void MainWindow::sortTableByNameDesc(){
    showTableWidget->sortItems(0,Qt::DescendingOrder);
}
/**
 * @brief MainWindow::sortTableByAccessDesc
 * does what it says on the tin
 */
void MainWindow::sortTableByAccessDesc(){
    showTableWidget->sortItems(3,Qt::DescendingOrder);
}

void MainWindow::searchInTable(QString term){
    QList<QTableWidgetItem *> search = showTableWidget->findItems(term, Qt::MatchExactly);
    if(!search.isEmpty()){
        showTableWidget->selectRow(search[0]->row());
    }else{
        qDebug() << "Worker not found, search";
    }
}

void MainWindow::emulateSearch(bool toggle){
    if(toggle){
        showSearchTable->setText("0004787864");
    }else{
        showSearchTable->setText("0000160302");
    }
}

/**
 * @brief MainWindow::scanTest
 * admin control and scan processing
 */
void MainWindow::scanTest(){
    QString RFID = testTextEdit->text();
    testTextEdit->clear();
    scanned(RFID, QString("Location 1"));
}

/**
 * @brief MainWindow::showAdminScreen
 * show features only available
 */
void MainWindow::showAdminScreen(){
    adminLogged = true;
    logOutButton->show();
    showAdminFrame->show();
    ui->statusbar->showMessage("admin logged in");
    emit LoggingTest("admin logged in",(int)LOG_COMMON);
}

/**
 * @brief MainWindow::hideAdminScreen
 * hide features only available for admins
 * @param chip
 * for logging only, logged out or different chip scanned
 */
void MainWindow::hideAdminScreen(bool chip){
    logOutButton->hide();
    showAdminFrame->hide();
    ui->statusbar->showMessage("admin gone");
    adminLogged = false;
    if(!chip){
        emit LoggingTest("log out button pressed",(int)LOG_BUTTON);
    }

    emit LoggingTest("admin logged out",(int)LOG_COMMON);
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
    QDateTime curTime = Logging::getInstance()->getCurrTime();
    nameLabel->setText(QString("Willkommen %1").arg(name));
    locLabel->setText(loc);
    if(access){
        accessLabel->setText("Access granted");
    }else{
        accessLabel->setText("Access denied");
    }
    timeLabel->setText(QString("Einstechzeit: %1").arg(curTime.toString("hh:mm:ss")));

    visualLayout->addWidget(nameLabel, 1, 0);
    visualLayout->addWidget(locLabel, 2, 0);
    visualLayout->addWidget(accessLabel, 1, 2);
    visualLayout->addWidget(timeLabel,2,2);

    mainTabWidget->setCurrentIndex(6);
}

/**
 * @brief MainWindow::loc1Clicked
 * slot for scan at location 1
 */
void MainWindow::loc1Clicked1(){
    scanned(QString("0001010101"), QString("Location 1"));
    emit LoggingTest("emulate location 1 pressed",(int)LOG_BUTTON);
}

/**
 * @brief MainWindow::loc2Clicked
 * slot for scan at location 2
 */
void MainWindow::loc2Clicked1(){
    scanned(QString("0002020202"), QString("Location 2"));
    emit LoggingTest("emulate location 2 pressed",(int)LOG_BUTTON);
}

/**
 * @brief MainWindow::loc3Clicked
 * slot for scan at location 3
 */
void MainWindow::loc3Clicked1(){
    scanned(QString("0003030303"),QString("Location 3"));
    emit LoggingTest("emulate location 3 pressed",(int)LOG_BUTTON);
}

/**
 * @brief MainWindow::loc1Clicked
 * slot for scan at location 1
 */
void MainWindow::loc1Clicked2(){
    scanned(QString("000101010"), QString("Location 1"));
    emit LoggingTest("emulate location 1 pressed",(int)LOG_BUTTON);
}

/**
 * @brief MainWindow::loc2Clicked
 * slot for scan at location 2
 */
void MainWindow::loc2Clicked2(){
    scanned(QString("000202020"), QString("Location 2"));
    emit LoggingTest("emulate location 2 pressed",(int)LOG_BUTTON);
}

/**
 * @brief MainWindow::loc3Clicked
 * slot for scan at location 3
 */
void MainWindow::loc3Clicked2(){
    scanned(QString("000303030"), QString("Location 3"));
    emit LoggingTest("emulate location 3 pressed",(int)LOG_BUTTON);
}

void MainWindow::adminClicked(){
    scanned(QString("0004365639"), QString("Location 1"));
    emit LoggingTest("emulate admin pressed", (int)LOG_BUTTON);
}

/**
 * @brief MainWindow::scanned
 * function for scan processing
 * @param loc
 * Location that the chip was scanned at
 */
void MainWindow::scanned(QString RFID, QString loc){
    qDebug() << "----------------------";
    if(adminLogged && RFID == ADMIN_RFID){
        qDebug() << "Admin already logged in";
    }else if(adminLogged && RFID != ADMIN_RFID){
        qDebug() << "Admin is gone";
        hideAdminScreen(true);
    }else{
        if(RFID == ADMIN_RFID){
            qDebug() << "Admin RFID";
            showAdminScreen();
        }else{
            qDebug() << "Regular worker";
            //hideAdminScreen(true);
        }
    }

    emit ScanInitiated(RFID, loc);

    if(RFID.length() == 10){
        loc.append("RFID: ").append(RFID);
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
