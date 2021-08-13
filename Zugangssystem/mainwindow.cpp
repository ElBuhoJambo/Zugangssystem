#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    RFID.setPattern("[0-9]{,10}");
    name.setPattern("^[a-zA-Z\\s,.'-]+$");
    access.setPattern("[01]");

    //TabWidget and tab definition
    mainGridLayout = new QGridLayout;
    mainTabWidget = new QTabWidget;
    mainTabFrame = new QFrame;
    loggingTabFrame = new QFrame;
    openTabFrame = new QFrame;
    settingsTabFrame = new QFrame;
    sqlTabFrame = new QFrame;
    visualTabFrame = new QFrame;
    csvTabFrame = new QFrame;

    //Layout of tabs definition
    loggingLayout = new QGridLayout;
    openLayout = new QGridLayout;
    settingsLayout = new QGridLayout;
    sqlLayout = new QGridLayout;
    visualLayout = new QGridLayout;
    csvLayout = new QGridLayout;

    //Definitons for main screen which is for emulation
    testLoc1But1 = new QPushButton("Location 1 \nCorrect RFID");
    testLoc2But1 = new QPushButton("Location 2 \nCorrect RFID");
    testLoc3But1 = new QPushButton("Location 3 \nCorrect RFID");
    testLoc1But2 = new QPushButton("Location 1 \nFaulty RFID");
    testLoc2But2 = new QPushButton("Location 2 \nFaulty RFID");
    testLoc3But2 = new QPushButton("Location 3 \nFaulty RFID");
    testAdminBut = new QPushButton("Admin Emulation");
    testLocLayout = new QGridLayout;

    //Definitions and property changes for sql screen which is for displaying the worker table
    showTableButton = new QPushButton("Show worker table");
    showTableButton->setCheckable(true);
    showTableButton->setFixedWidth(460);
    showAddButton = new QPushButton("Add worker");
    showDeleteButton = new QPushButton("Delete worker");
    showUpdateButton = new QPushButton("Update worker");
    showEmulateSearch = new QPushButton("Emulate a search");
    showAllButton = new QPushButton("Show all worker");
    showEmulateSearch->setCheckable(true);
    showAdminLineEdit = new QLineEdit;
    showAdminUserIdEdit = new QLineEdit;
    showAdminRFIDLineEdit = new QLineEdit;
    showAdminNameLineEdit = new QLineEdit;
    showAdminGroupsLineEdit = new QLineEdit;
    showAdminActivateLineEdit = new QLineEdit;
    showAdminSubmit = new QPushButton("Submit");
    showAdminCancel = new QPushButton("Cancel");
    showAdminLineEdit->setFocusPolicy(Qt::NoFocus);
    showAdminUserIdEdit->setFocusPolicy(Qt::NoFocus);
    showAdminRFIDLineEdit->setFocusPolicy(Qt::NoFocus);
    showAdminNameLineEdit->setFocusPolicy(Qt::NoFocus);
    showAdminGroupsLineEdit->setFocusPolicy(Qt::NoFocus);
    showAdminActivateLineEdit->setFocusPolicy(Qt::NoFocus);
    showAdminLineEdit->hide();
    showAdminUserIdEdit->hide();
    showAdminRFIDLineEdit->hide();
    showAdminNameLineEdit->hide();
    showAdminGroupsLineEdit->hide();
    showAdminActivateLineEdit->hide();
    showAdminSubmit->hide();
    showAdminCancel->hide();
    showSortByNameAsc = new QPushButton("Ascending");
    showSortByIdAsc = new QPushButton("Ascending");
    showSortByNameDesc = new QPushButton("Descending");
    showSortByIdDesc = new QPushButton("Descending");
    showSearchTable = new QLineEdit();
    showSearchTable->setPlaceholderText("RFID");
    showSearchTable->setFocusPolicy(Qt::NoFocus);
    showSortByName = new QLabel("Sort by name");
    showSortById = new QLabel("Sort by id");
    showFrame = new QFrame;
    showFrame->setMaximumWidth(460);
    showFrame->resize(460,460);
    showFrame->hide();
    showSortFrame = new QFrame;
    showSpaceFrame = new QFrame;
    showAdminFrame = new QFrame;
    showAdminFrame->hide();
    showTableWidget = new QTableWidget(0,5,this);
    showTableWidget->setColumnWidth(0,10);
    showTableWidget->setColumnWidth(2,100);
    showTableWidget->setColumnWidth(4,75);
    showTableWidget->setHorizontalHeaderLabels(columns);
    showTableWidget->setSelectionMode(QAbstractItemView::MultiSelection);
    showTableWidget->verticalHeader()->setVisible(false);
    showLayout = new QVBoxLayout;
    showAdminLayout = new QGridLayout;
    showSortLayout = new QGridLayout;
    showAdminLayout->setAlignment(Qt::AlignTop);
    showLayout->setAlignment(Qt::AlignTop);
    showLayout->setSpacing(0);
    showLayout->addWidget(showTableWidget);
    showSortLayout->addWidget(showSearchTable,0,0,1,2,Qt::AlignBottom);
    showSortLayout->addWidget(showSortByName,1,0,Qt::AlignBottom);
    showSortLayout->addWidget(showSortById,1,1,Qt::AlignBottom);
    showSortLayout->addWidget(showSortByNameAsc,2,0,Qt::AlignBottom);
    showSortLayout->addWidget(showSortByIdAsc,2,1,Qt::AlignBottom);
    showSortLayout->addWidget(showSortByNameDesc,3,0);
    showSortLayout->addWidget(showSortByIdDesc,3,1);
    sqlLayout->addWidget(showTableButton,0,0, Qt::AlignTop);
    sqlLayout->addWidget(showFrame, 1,0);
    showAdminLayout->addWidget(showAddButton,0,0,1,2);
    showAdminLayout->addWidget(showDeleteButton,1,0,1,2,Qt::AlignTop);
    showAdminLayout->addWidget(showUpdateButton,2,0,1,2,Qt::AlignTop);
    showAdminLayout->addWidget(showEmulateSearch,3,0,1,2,Qt::AlignTop);
    showAdminLayout->addWidget(showAllButton,4,0,1,2,Qt::AlignTop);
    showAdminLayout->addWidget(showAdminLineEdit,5,0,1,2,Qt::AlignTop);
    showAdminLayout->addWidget(showAdminUserIdEdit,6,0,1,2,Qt::AlignTop);
    showAdminLayout->addWidget(showAdminRFIDLineEdit,7,0,1,2,Qt::AlignTop);
    showAdminLayout->addWidget(showAdminNameLineEdit,8,0,1,2,Qt::AlignTop);
    showAdminLayout->addWidget(showAdminGroupsLineEdit,9,0,1,2,Qt::AlignTop);
    showAdminLayout->addWidget(showAdminActivateLineEdit,10,0,1,2,Qt::AlignTop);
    showAdminLayout->addWidget(showAdminSubmit,11,0,Qt::AlignTop);
    showAdminLayout->addWidget(showAdminCancel,11,1,Qt::AlignTop);
    sqlLayout->addWidget(showSortFrame, 3,1);
    sqlLayout->addWidget(showSpaceFrame, 2,1);
    sqlLayout->addWidget(showAdminFrame, 0,1,2,1);
    showAdminFrame->setLayout(showAdminLayout);
    showFrame->setLayout(showLayout);
    showSortFrame->setLayout(showSortLayout);
    sqlTabFrame->setLayout(sqlLayout);

    //Definitions for csv tab which is for the displaying the csv file in a table
    writeToFile = new QPushButton("Write to CSV file");
    fillCsvTable = new QPushButton("Fill table");
    csvTable = new QTableWidget(0,2,this);
    csvTable->setColumnWidth(1,155);
    calcWeeklyHours = new QPushButton("Hours this week");
    calcMonthlyHours = new QPushButton("Hours this month");
    calcOvertime = new QPushButton("Overtime");
    calcNeededTime = new QPushButton("Needed time");

    //initliazing display keyboard
    lineEditKeyboard = new Keyboard(this);
    lineEditKeyboard->hide();
    lineEditKeyboard->setGeometry(0,300,800,300);

    //definitions for settings tab
    settings = new QSettings("LarSys", "Zugangssystem");
    keyboardEnabled = new QCheckBox("Enable display keyboard?");
    settingsSaveCancel = new QDialogButtonBox(QDialogButtonBox::Save | QDialogButtonBox::Cancel);
    standardSortDrop = new QComboBox;
    colorSchemeDrop = new QComboBox;
    fontDrop = new QFontComboBox;
    autoLogout = new QCheckBox("Disable auto logout?");
    keyboardEnabled->setFocusPolicy(Qt::NoFocus);
    standardSortDrop->addItems(standardSort);
    colorSchemeDrop->addItems(colorScheme);
    fontDrop->setWritingSystem(QFontDatabase::Latin);
    fontDrop->setFontFilters(QFontComboBox::ScalableFonts);
    autoLogout->hide();

    ui->centralwidget->setLayout(mainGridLayout);

    //statusbar setup
    statusLabel->setFixedWidth(150);
    toolTipBut->setFixedWidth(100);
    statusLabel->setText("Version 1.0");
    //statusLayout->addWidget(spacerLabel,0,Qt::AlignLeft);
    //statusLayout->addWidget(statusLabel,0,Qt::AlignLeft);
    //statusLayout->addWidget(toolTipBut,0,Qt::AlignCenter);
    ui->statusbar->addWidget(statusLabel,0);
    ui->statusbar->addPermanentWidget(toolTipBut,1);

    //tabwidget and tab setup for main tabwidget
    mainTabWidget->addTab(mainTabFrame, "Hauptmenu");
    mainTabWidget->addTab(loggingTabFrame, "Logging");
    mainTabWidget->addTab(openTabFrame, "Öffne Tür");
    mainTabWidget->addTab(sqlTabFrame, "SQL");
    mainTabWidget->addTab(csvTabFrame, "CSV");
    mainTabWidget->addTab(visualTabFrame, "Visual on Screen");
    mainTabWidget->addTab(settingsTabFrame, "Einstellungen");

    mainGridLayout->addWidget(mainTabWidget);
    mainTabWidget->setFixedSize(790,550);

    //emulation/main screen setup
    testLocLayout->addWidget(testLoc1But1,1,1);
    testLocLayout->addWidget(testLoc2But1,1,2);
    testLocLayout->addWidget(testLoc3But1,1,3);
    testLocLayout->addWidget(testLoc1But2,2,1);
    testLocLayout->addWidget(testLoc2But2,2,2);
    testLocLayout->addWidget(testLoc3But2,2,3);
    testLocLayout->addWidget(testAdminBut,3,2);
    mainTabFrame->setLayout(testLocLayout);

    //visual setup for showing the current worker
    visualLayout->setAlignment(Qt::AlignTop);
    visualLayout->setSpacing(0);
    visualTabFrame->setLayout(visualLayout);
    visualLayout->addWidget(logOutButton,10,0, 1, 1, Qt::AlignBottom);
    visualLayout->addItem(logOutSpacer,3,0,1,1);
    logOutButton->hide();

    //setup for displaying every log
    loggingLayout->setAlignment(Qt::AlignTop);
    loggingLayout->setSpacing(0);
    loggingTabFrame->setLayout(loggingLayout);

    //setup for csv screen
    csvLayout->addWidget(writeToFile,0,0,1,2);
    csvLayout->addWidget(fillCsvTable,0,2,1,2);
    csvLayout->addWidget(csvTable,1,0,1,4);
    csvLayout->addWidget(calcWeeklyHours,2,0);
    csvLayout->addWidget(calcMonthlyHours,2,1);
    csvLayout->addWidget(calcOvertime,2,2);
    csvLayout->addWidget(calcNeededTime,2,3);
    csvTabFrame->setLayout(csvLayout);

    //setup for settings screen
    settingsLayout->addWidget(keyboardEnabled,0,0,Qt::AlignTop);
    settingsLayout->addWidget(standardSortDrop,1,1,1,2,Qt::AlignTop);
    settingsLayout->addWidget(colorSchemeDrop,1,0,Qt::AlignTop);
    settingsLayout->addWidget(fontDrop,2,0,1,3,Qt::AlignTop);
    settingsLayout->addWidget(autoLogout,0,2,Qt::AlignTop);
    settingsLayout->addWidget(settingsSaveCancel,3,1,1,2,Qt::AlignBottom);
    settingsTabFrame->setLayout(settingsLayout);
    settingsLayout->setAlignment(Qt::AlignTop);

    //setting every WhatsThis text
    testLoc1But1->setWhatsThis("Emulate scan for Location 1");
    testLoc2But1->setWhatsThis("Emulate scan for Location 2");
    testLoc3But1->setWhatsThis("Emulate scan for Location 3");
    testLoc1But2->setWhatsThis("Emulate scan for Location 1");
    testLoc2But2->setWhatsThis("Emulate scan for Location 2");
    testLoc3But2->setWhatsThis("Emulate scan for Location 3");
    testAdminBut->setWhatsThis("Emulate scan of Admin");
    showTableButton->setWhatsThis("Show the worker table");
    showAddButton->setWhatsThis("Add a worker via text input");
    showDeleteButton->setWhatsThis("Delete a worker via text input");
    showUpdateButton->setWhatsThis("Update a worker via text input");
    showEmulateSearch->setWhatsThis("Emulate a search in the table\nToggles to have two possible search terms");
    showSortByNameAsc->setWhatsThis("Sort the table by name ascending\nA-Z");
    showSortByNameDesc->setWhatsThis("Sort the table by name descending\nZ-A");
    showSortByIdAsc->setWhatsThis("Sort the table by User Id ascending");
    showSortByIdDesc->setWhatsThis("Sort the table by User Id descending");
    showSearchTable->setWhatsThis("Look for any term in the table\nRFID suggested");
    showTableWidget->setWhatsThis("Worker table");
    writeToFile->setWhatsThis("Add an entry to the csv manually");
    fillCsvTable->setWhatsThis("Fill the table with the CSV-File of the current worker");
    csvTable->setWhatsThis("CSV-File of a worker");
    calcWeeklyHours->setWhatsThis("Calculates the current hours of this week");
    calcMonthlyHours->setWhatsThis("Calculates the current hours of this month");
    calcOvertime->setWhatsThis("Calculates the current overtime hours of this month");
    calcNeededTime->setWhatsThis("Calculates the current hours still needed of this week");
    logOutButton->setWhatsThis("Log out of admin mode");
    nameLabel->setWhatsThis("Name of the currently scanned worker");
    locLabel->setWhatsThis("Location of the currently scanned worker");
    accessLabel->setWhatsThis("Output whether or not access is to this location is granted");
    timeLabel->setWhatsThis("Time the currently scanned worker scanned in");
    keyboardEnabled->setWhatsThis("Check if display keyboard should be enabled\nUncheck if display keyboard should be disabled");
    standardSortDrop->setWhatsThis("Set the standard sort criterium for the worker table");
    colorSchemeDrop->setWhatsThis("Set the color scheme of the application");
    fontDrop->setWhatsThis("Set the font of the application");

    //connecting signals and slots used for sending data between and in classes
    connect(openDoor::getInstance(),&openDoor::Rights,accessRights::getInstance(),&accessRights::checkAccess);
    connect(accessRights::getInstance(),&accessRights::SQLRequest,sqlCheck::getInstance(),&sqlCheck::receiveRequest);
    connect(accessRights::getInstance(), &accessRights::Visual, this, &MainWindow::visual);
    connect(accessRights::getInstance(),&accessRights::Door,openDoor::getInstance(), &openDoor::rightsReturned);
    connect(sqlCheck::getInstance(),&sqlCheck::Result,accessRights::getInstance(), &accessRights::receiveResult);
    connect(this, &MainWindow::ScanInitiated, openDoor::getInstance(), &openDoor::checkAccess);
    connect(sqlCheck::getInstance(), SIGNAL(ShowTable(QList<QStringList>)), this, SLOT(sql(QList<QStringList>)));
    connect(this, &MainWindow::FirstShow, sqlCheck::getInstance(), &sqlCheck::showTable);
    connect(this, &MainWindow::AddWorker, sqlCheck::getInstance(), &sqlCheck::addWorker);
    connect(this, &MainWindow::DeleteWorker, sqlCheck::getInstance(), &sqlCheck::deleteWorker);
    connect(sqlCheck::getInstance(), &sqlCheck::DeleteRow, this, &MainWindow::deleteRowInTable);
    connect(this, &MainWindow::UpdateWorker, sqlCheck::getInstance(), &sqlCheck::updateWorker);
    connect(sqlCheck::getInstance(), &sqlCheck::UpdateWorker, this, &MainWindow::updateRowInTable);
    connect(this, &MainWindow::PutCurrentOnTop, this, &MainWindow::putCurrentOnTop);
    connect(csvHandling::getInstance(), &csvHandling::WriteToTable, this, &MainWindow::updateCSVTable);
    connect(this, &MainWindow::WriteToFile, csvHandling::getInstance(), &csvHandling::WriteToFile);
    connect(this, &MainWindow::FillCSVTable, csvHandling::getInstance(), &csvHandling::readWholeFile);
    connect(csvHandling::getInstance(), SIGNAL(FillTable(QList<QStringList>)), this, SLOT(fillCSVTable(QList<QStringList>)));
    connect(this, SIGNAL(GetCurrentTime(bool, QString)), Logging::getInstance(), SLOT(getCurrTime(bool, QString)));
    connect(Logging::getInstance(), SIGNAL(SendCurrentTime(QDateTime, QString)), this, SLOT(writeToFileFuc(QDateTime, QString)));
    connect(Scanner::getInstance(), &Scanner::ChipScanned, this, &MainWindow::scanTest);
    connect(logoutUser::getInstance(), &logoutUser::Logout, this, &MainWindow::logoutWorker);

    //connecting signals and slots for button clicks
    connect(testLoc1But1, &QPushButton::clicked, this, &MainWindow::loc1Clicked1);
    connect(testLoc2But1, &QPushButton::clicked, this, &MainWindow::loc2Clicked1);
    connect(testLoc3But1, &QPushButton::clicked, this, &MainWindow::loc3Clicked1);
    connect(testLoc1But2, &QPushButton::clicked, this, &MainWindow::loc1Clicked2);
    connect(testLoc2But2, &QPushButton::clicked, this, &MainWindow::loc2Clicked2);
    connect(testLoc3But2, &QPushButton::clicked, this, &MainWindow::loc3Clicked2);
    connect(testAdminBut, &QPushButton::clicked, this, &MainWindow::adminClicked);
    connect(showTableButton, &QPushButton::toggled, this, &MainWindow::showTable);
    connect(logOutButton, &QPushButton::clicked,this, &MainWindow::hideAdminScreen);
    connect(toolTipBut, &QPushButton::clicked, this, &MainWindow::showTabToolTips);
    connect(showAddButton, &QPushButton::clicked, this, &MainWindow::addWorker);
    connect(showDeleteButton, &QPushButton::clicked, this, &MainWindow::deleteWorker);
    connect(showUpdateButton, &QPushButton::clicked, this, &MainWindow::updateWorker);
    connect(showEmulateSearch, &QPushButton::toggled, this, &MainWindow::emulateSearch);
    connect(showAllButton, &QPushButton::clicked, this, &MainWindow::showAll);
    connect(showSortByNameAsc, &QPushButton::clicked, this, &MainWindow::sortTableByNameAsc);
    connect(showSortByIdAsc, &QPushButton::clicked, this, &MainWindow::sortTableByIdAsc);
    connect(showSortByNameDesc, &QPushButton::clicked, this, &MainWindow::sortTableByNameDesc);
    connect(showSortByIdDesc, &QPushButton::clicked, this, &MainWindow::sortTableByIdDesc);
    connect(showSearchTable, &QLineEdit::textChanged, this, &MainWindow::searchInTable);
    connect(writeToFile, &QPushButton::clicked, this, &MainWindow::emulateWriteToFile);
    connect(fillCsvTable, SIGNAL(clicked()), this, SLOT(fillCSVTable()));
    connect(calcWeeklyHours, &QPushButton::clicked, this, &MainWindow::calcWeekHours);
    connect(calcMonthlyHours, &QPushButton::clicked, this, &MainWindow::calcMonthHours);
    connect(calcOvertime, &QPushButton::clicked, this, &MainWindow::calcOverTime);
    connect(calcNeededTime, &QPushButton::clicked, this, &MainWindow::calcNeedTime);
    connect(showAdminSubmit, &QPushButton::clicked, this, &MainWindow::adminAccept);
    connect(showAdminCancel, &QPushButton::clicked, this, &MainWindow::adminCancel);
    connect(settingsSaveCancel, &QDialogButtonBox::accepted, this, &MainWindow::saveSettings);
    connect(settingsSaveCancel, &QDialogButtonBox::rejected, this, &MainWindow::restoreSettings);

    //connecting signals and slots for logging in the classes
    connect(this, &MainWindow::LoggingTest, Logging::getInstance(), &Logging::logMessage);
    connect(Logging::getInstance(), &Logging::LogMessageTest, this, &MainWindow::logMessage);
    connect(openDoor::getInstance(), &openDoor::logMessage, Logging::getInstance(), &Logging::logMessage);
    connect(accessRights::getInstance(), &accessRights::logMessage, Logging::getInstance(), &Logging::logMessage);
    connect(sqlCheck::getInstance(), &sqlCheck::logMessage, Logging::getInstance(), &Logging::logMessage);
    connect(Scanner::getInstance(), &Scanner::logMessage, Logging::getInstance(), &Logging::logMessage);
    connect(csvHandling::getInstance(), &csvHandling::logMessage, Logging::getInstance(), &Logging::logMessage);

    emit LoggingTest("program started", (int)LOG_COMMON);

    restoreSettings();
}

MainWindow::~MainWindow()
{
    delete ui;

}

/**
 * @brief MainWindow::grabKeyboard
 * enable display keyboard
 */
void MainWindow::grabKeyboard(){
    QList<QLineEdit*> lineEditList = this->findChildren<QLineEdit*>();
    foreach(QLineEdit* lineEdit, lineEditList)
    {
        lineEdit->setFocusPolicy(Qt::NoFocus);
        connect(lineEdit,&QLineEdit::selectionChanged,this,&MainWindow::showKeyboardLineEdit);
    }
}

/**
 * @brief MainWindow::disableDisplayKeyboard
 * disable display keyboard
 */
void MainWindow::disableDisplayKeyboard(){
    QList<QLineEdit*> lineEditList = this->findChildren<QLineEdit*>();
    foreach(QLineEdit* lineEdit, lineEditList)
    {
        lineEdit->setFocusPolicy(Qt::NoFocus);
        disconnect(lineEdit,&QLineEdit::selectionChanged,this,&MainWindow::showKeyboardLineEdit);
    }
}

/**
 * @brief MainWindow::saveSettings
 * save current settings and apply them
 */
void MainWindow::saveSettings(){
    settings->setValue("checkbox/value", keyboardEnabled->isChecked());
    settings->setValue("combobox/index", standardSortDrop->currentIndex());
    settings->setValue("combobox/data", standardSortDrop->currentData());
    settings->setValue("colorscheme/index", colorSchemeDrop->currentIndex());
    settings->setValue("colorscheme/data", colorSchemeDrop->currentData());
    settings->setValue("font/index", fontDrop->currentIndex());
    settings->setValue("font/text", fontDrop->currentText());
    settings->setValue("autoLogout/value", autoLogout->isChecked());

    restoreSettings();
}

/**
 * @brief MainWindow::restoreSettings
 * read the current saved settings and apply them
 */
void MainWindow::restoreSettings(){
    bool enableKeyboard = settings->value("checkbox/value").value<bool>();
    int currentSortIndex = settings->value("combobox/index").value<int>();
    int currentColorIndex = settings->value("colorscheme/index").value<int>();
    int currentFontIndex = settings->value("font/index").value<int>();
    QString currenFont = settings->value("font/text").toString();
    bool disableAutoLogin = settings->value("autoLogout/value").value<bool>();

    keyboardEnabled->setChecked(enableKeyboard);
    standardSortDrop->setCurrentIndex(currentSortIndex);
    colorSchemeDrop->setCurrentIndex(currentColorIndex);
    fontDrop->setCurrentIndex(currentFontIndex);
    autoLogout->setChecked(disableAutoLogin);
    logoutUser::getInstance()->setIsAutoLogoutDisabled(disableAutoLogin);

    if(enableKeyboard){
        grabKeyboard();
    }else{
        disableDisplayKeyboard();
    }
    switch(currentSortIndex){
    case 0:
        showTableWidget->sortByColumn(0, Qt::AscendingOrder);
        break;
    case 1:
        showTableWidget->sortByColumn(0, Qt::DescendingOrder);
        break;
    case 2:
        showTableWidget->sortByColumn(1, Qt::AscendingOrder);
        break;
    case 3:
        showTableWidget->sortByColumn(1, Qt::DescendingOrder);
        break;
    default:
        showTableWidget->sortByColumn(0, Qt::AscendingOrder);
        break;
    }
    setColorScheme(currentColorIndex,currenFont);
}

/**
 * @brief MainWindow::setColorScheme
 * set the color scheme and the font
 * @param index
 * current index of the color scheme
 * @param font
 * current font family
 */
void MainWindow::setColorScheme(int index, QString font){
    switch(index){
    case 0:
        mainTabWidget->setStyleSheet(QString("background-color:#F1F1F1; "
                                             "color: #000000;"
                                             "font-family:"+font+";"));
        this->setStyleSheet(QString("background-color:#F1F1F1; "
                                             "color: #000000;"
                                             "font-family:"+font+";"));
        break;
    case 1:
        mainTabWidget->setStyleSheet(QString("background-color:#AFAFAF;"
                                             "color: #FFFFFF;"
                                             "font-family:"+font+";"));
        this->setStyleSheet(QString("background-color:#AFAFAF;"
                                             "color: #FFFFFF;"
                                             "font-family:"+font+";"));
        break;
    case 2:
        mainTabWidget->setStyleSheet(QString("background-color:#8FDDFB;"
                                             "color: #253E92;"
                                             "font-family:"+font+";"));
        this->setStyleSheet(QString("background-color:#8FDDFB;"
                                             "color: #253E92;"
                                             "font-family:"+font+";"));
        break;
    case 3:
        mainTabWidget->setStyleSheet(QString("background-color:#FFE808;"
                                             "color: #FF0000;"
                                             "font-family:"+font+";"));
        this->setStyleSheet(QString("background-color:#FFE808;"
                                             "color: #FF0000;"
                                             "font-family:"+font+";"));
        break;
    default:
        mainTabWidget->setStyleSheet(QString("background-color:#F1F1F1; "
                                             "color: #000000;"
                                             "font-family:"+font+";"));
        this->setStyleSheet(QString("background-color:#999999;"
                                             "color: #FFFFFF;"
                                             "font-family:"+font+";"));
        break;
    }
}

/**
 * @brief MainWindow::showKeyboardLineEdit
 * open the display keyboard and assign the clicked lineedit
 */
void MainWindow::showKeyboardLineEdit(){
    QLineEdit *line = (QLineEdit *)sender();
    lineEditKeyboard->setLineEdit(line);
    lineEditKeyboard->show();
}

/**
 * @brief MainWindow::calcWeekHours
 * calculates the current hours saved in the current week of the current worker
 * @return
 * calculated hours rounded to the nearest quarter
 */
double MainWindow::calcWeekHours(){
    double weekTime = 0;
    for(int i = csvTable->rowCount()-1; i > 0; i--){
        QString sDate1 = csvTable->item(i,1)->text();
        QString sTime1 = csvTable->item(i,0)->text();
        QDateTime dDate1 = QDateTime::fromString(sDate1, "dd.MM.yyyy");
        QDateTime tDate1 = QDateTime::fromString(sTime1, "hh:mm");
        double h1 = tDate1.toString("hh").toDouble() + (tDate1.toString("mm").toDouble() / 60);
        h1 = std::round(h1*4)/4;
        QString sDate2 = csvTable->item(i-1,1)->text();
        QString sTime2 = csvTable->item(i-1,0)->text();
        QDateTime dDate2 = QDateTime::fromString(sDate2, "dd.MM.yyyy");
        QDateTime tDate2 = QDateTime::fromString(sTime2, "hh:mm");
        double h2 = tDate2.toString("hh").toDouble() + (tDate2.toString("mm").toDouble() / 60);
        h2 = std::round(h2*4)/4;
        if(dDate1.toString("dd.MM.yyyy") != dDate2.toString("dd.MM.yyyy")){
            qDebug() << "Day incomplete";
        }else{
            weekTime = weekTime + (h1 - h2);
        }
        if(dDate1.toString("ddd") == "Mon" && dDate2.toString("ddd") != "Mon"){
            qDebug() << "week done";
            break;
        }
    }
    if(hourBox){
        QMessageBox hourBox;
        hourBox.setText(QString("Hours this week: %1h").arg(weekTime));
        hourBox.exec();
    }
    return weekTime;
}

/**
 * @brief MainWindow::calcMonthHours
 * calculates the current hours saved in the current month of the current worker
 */
void MainWindow::calcMonthHours(){
    double weekTime = 0;
    for(int i = csvTable->rowCount()-1; i > 0; i--){
        QString sDate1 = csvTable->item(i,1)->text();
        QString sTime1 = csvTable->item(i,0)->text();
        QDateTime dDate1 = QDateTime::fromString(sDate1, "dd.MM.yyyy");
        QDateTime tDate1 = QDateTime::fromString(sTime1, "hh:mm");
        double h1 = tDate1.toString("hh").toDouble() + (tDate1.toString("mm").toDouble() / 60);
        h1 = std::round(h1*4)/4;
        QString sDate2 = csvTable->item(i-1,1)->text();
        QString sTime2 = csvTable->item(i-1,0)->text();
        QDateTime dDate2 = QDateTime::fromString(sDate2, "dd.MM.yyyy");
        QDateTime tDate2 = QDateTime::fromString(sTime2, "hh:mm");
        double h2 = tDate2.toString("hh").toDouble() + (tDate2.toString("mm").toDouble() / 60);
        h2 = std::round(h2*4)/4;
        if(dDate1.toString("dd.MM.yyyy") != dDate2.toString("dd.MM.yyyy")){
            qDebug() << "Day incomplete";
        }else{
            weekTime = weekTime + (h1 - h2);

        }
        if(dDate1.toString("MM") != dDate2.toString("MM")){
            qDebug() << "month done";
            break;
        }
    }
    QMessageBox monthBox;
    monthBox.setText(QString("Hours this month: %1h").arg(weekTime));
    monthBox.exec();
}

/**
 * @brief MainWindow::calcOverTime
 * calculates the amount of hours done overtime if any
 */
void MainWindow::calcOverTime(){
    hourBox = false;
    double weekTime = calcWeekHours();
    hourBox = true;
    QMessageBox overBox;

    if(weekTime <= 38.5){
        overBox.setText("No overtime yet");
        overBox.exec();
    }else{
        overBox.setText(QString("Overtime this week: %1h").arg(weekTime-38.5));
        overBox.exec();
    }
}

/**
 * @brief MainWindow::calcNeedTime
 * calculates the amount of hours still needed if any
 */
void MainWindow::calcNeedTime(){
    hourBox = false;
    double weekTime = calcWeekHours();
    hourBox = true;
    QMessageBox needBox;

    if(weekTime >= 38.5){
        needBox.setText("Hour minimum already reached");
        needBox.exec();
    }else{
        needBox.setText(QString("Needed hours this week: %1h").arg(38.5 - weekTime));
        needBox.exec();
    }
}

/**
 * @brief MainWindow::fillCSVTable
 * send signal to gather data for table
 */
void MainWindow::fillCSVTable(){
    if(!nameLabel->text().isEmpty()){
        QString name = nameLabel->text();
        name.replace("Willkommen ","");
        QString filePath = QDir::currentPath() + "/" + name + ".csv";
        emit FillCSVTable(filePath);
        //emit FillCSVTable(QString(QDir::currentPath() + "/test.csv"));
        emit LoggingTest("fill csv table button pressed", (int)LOG_BUTTON);
    }else{
        emit LoggingTest("fill csv table button pressed;no worker", (int)LOG_BUTTON);
    }
}

/**
 * @brief MainWindow::fillCSVTable
 * fill table with recieved csv data
 * @param data
 * csv-file
 */
void MainWindow::fillCSVTable(QList<QStringList> data){
    //check if csv file is empty
    if(data.isEmpty()){
        qWarning() << "CSV is empty";
        return;
    }
    csvTable->setRowCount(0);

    //make sure that the tablewidget is big enough for the csv file and enlarged if needed
    if(data.size() > csvTable->rowCount()){
        csvTable->setRowCount(data.size());
    }
    for(int i = 0; i < data.size(); i++){
        if(data.at(i).size() > csvTable->columnCount()){
            csvTable->setColumnCount(data.at(i).size());
        }
    }

    //fill the table with the csv file
    for(int i = 0; i < data.size(); i++){
        for(int j = 0; j < data.at(i).size(); j++){
            QTableWidgetItem *item = new QTableWidgetItem(data.at(i).at(j));
            csvTable->setItem(i,j,item);
        }
    }
    csvShow = true;
}

/**
 * @brief MainWindow::updateCSVTable
 * update new entry in table after scan
 * @param data
 * last scan to append
 */
void MainWindow::updateCSVTable(QString data){
    //check if csv file is empty
    if(data.isEmpty()){
        qWarning() << "CSV is empty";
        return;
    }

    //append last entry into table but only if the full table is already shown
    if(csvShow){
        QStringList dataList = data.split(QLatin1Char(','));
        QTableWidgetItem *itemTime = new QTableWidgetItem(dataList.at(0));
        QTableWidgetItem *itemDate = new QTableWidgetItem(dataList.at(1));

        csvTable->setRowCount(csvTable->rowCount()+1);
        csvTable->setItem(csvTable->rowCount()-1,0, itemTime);
        csvTable->setItem(csvTable->rowCount()-1,1, itemDate);
    }else{
        qDebug() << "table not yet shown";
    }

}

/**
 * @brief MainWindow::emulateWriteToFile
 * emulate a scan but only for the csv file
 */
void MainWindow::emulateWriteToFile(){
    emit GetCurrentTime(true, "Workernotfound");
    emit LoggingTest("emulate write in csv file button pressed", (int)LOG_BUTTON);
}

/**
 * @brief MainWindow::writeToFileFuc
 * write into csv file after scan
 * @param time
 * time of the scan
 */
void MainWindow::writeToFileFuc(QDateTime time, QString name){

    if(csvTable->accessibleName() != name){
        csvTable->setAccessibleName(name);
        csvTable->setRowCount(0);
        csvShow = false;
    }

    QString filePath = QString(QDir::currentPath() + "/%1.csv").arg(name);
    emit WriteToFile(filePath, time.toString("hh:mm,dd.MM.yyyy"));
}

/**
 * @brief MainWindow::updateWorker
 * update a worker via text input
 */
void MainWindow::updateWorker(){
    showDeleteButton->hide();
    showAddButton->hide();
    showUpdateButton->hide();
    showEmulateSearch->hide();
    showAllButton->hide();
    showAdminLineEdit->show();
    showAdminUserIdEdit->show();
    showAdminRFIDLineEdit->show();
    showAdminNameLineEdit->show();
    showAdminGroupsLineEdit->show();
    showAdminActivateLineEdit->show();
    showAdminSubmit->show();
    showAdminCancel->show();
    showAdminLineEdit->setPlaceholderText("Current User ID");
    showAdminUserIdEdit->setPlaceholderText("New/Same User ID");
    showAdminRFIDLineEdit->setPlaceholderText("New/Same RFID");
    showAdminNameLineEdit->setPlaceholderText("New/Same name");
    showAdminGroupsLineEdit->setPlaceholderText("New/Same Groups");
    showAdminActivateLineEdit->setPlaceholderText("New/Same Active status (1/0)");
    //showAdminLineEdit->setValidator(new QRegExpValidator(RFID));
    //showAdminRFIDLineEdit->setValidator(new QRegExpValidator(RFID));
    //showAdminNameLineEdit->setValidator(new QRegExpValidator(name));
    //showAdminActivateLineEdit->setValidator(new QRegExpValidator(access));
    currAdminEdit = "Update";

    emit LoggingTest(";update worker button pressed", (int)LOG_BUTTON);
}

/**
 * @brief MainWindow::deleteWorker
 * delete a worker via text input
 */
void MainWindow::deleteWorker(){
    showDeleteButton->hide();
    showAddButton->hide();
    showUpdateButton->hide();
    showEmulateSearch->hide();
    showAllButton->hide();
    showAdminLineEdit->show();
    showAdminSubmit->show();
    showAdminCancel->show();
    showAdminLineEdit->setPlaceholderText("User Id");
    currAdminEdit = "Delete";

    emit LoggingTest("delete worker button pressed", (int)LOG_BUTTON);
}

/**
 * @brief MainWindow::addWorker
 * add a worker via text input
 */
void MainWindow::addWorker(){
    showDeleteButton->hide();
    showAddButton->hide();
    showUpdateButton->hide();
    showEmulateSearch->hide();
    showAllButton->hide();
    showAdminLineEdit->show();
    showAdminRFIDLineEdit->show();
    showAdminNameLineEdit->show();
    showAdminGroupsLineEdit->show();
    showAdminActivateLineEdit->show();
    showAdminSubmit->show();
    showAdminCancel->show();
    showAdminLineEdit->setPlaceholderText("User ID");
    showAdminRFIDLineEdit->setPlaceholderText("RFID");
    showAdminNameLineEdit->setPlaceholderText("name");
    showAdminGroupsLineEdit->setPlaceholderText("Group1,Group2,Group3,...");
    showAdminActivateLineEdit->setPlaceholderText("Active 1/0");
    currAdminEdit = "Add";

    emit LoggingTest("add worker button pressed", (int)LOG_BUTTON);
}

/**
 * @brief MainWindow::adminAccept
 * add, update or delete a worker after apply was clicked by admin
 */
void MainWindow::adminAccept(){
    QString *currUserId = new QString(showAdminLineEdit->text());
    QString *userId = new QString(showAdminUserIdEdit->text());
    QString *RFID = new QString(showAdminRFIDLineEdit->text());
    QString *name = new QString(showAdminNameLineEdit->text());
    QString *groups = new QString(showAdminGroupsLineEdit->text());
    QString *active = new QString(showAdminActivateLineEdit->text());

    *groups = groups->replace(" ","");
    *groups = groups->toLower();
    QStringList groupList = groups->split(QLatin1Char(','));
    QList<int> groupArr;
    for(int i = 0; i < groupList.size(); i++){
        if(groupList.at(i) == "software"){
            groupArr << (int)Software;
        }else if(groupList.at(i) == "hardware"){
            groupArr << (int)Hardware;
        }else if(groupList.at(i) == "produktion"){
            groupArr << (int)Produktion;
        }else if(groupList.at(i) == "buero"){
            groupArr << (int)Buero;
        }else{
            qDebug() << "Invalid group";
        }
    }

    if(!currUserId->isEmpty()){
        showAdminLineEdit->hide();
        showAdminUserIdEdit->hide();
        showAdminRFIDLineEdit->hide();
        showAdminNameLineEdit->hide();
        showAdminGroupsLineEdit->hide();
        showAdminActivateLineEdit->hide();
        showAdminLineEdit->clear();
        showAdminUserIdEdit->clear();
        showAdminRFIDLineEdit->clear();
        showAdminNameLineEdit->clear();
        showAdminGroupsLineEdit->clear();
        showAdminActivateLineEdit->clear();
        showAdminSubmit->hide();
        showAdminCancel->hide();
        showDeleteButton->show();
        showAddButton->show();
        showUpdateButton->show();
        showEmulateSearch->show();
        showAllButton->show();
        if(currAdminEdit.isEmpty()){
            qWarning() << "What?! Empty but in adminAccept? How?!";
        }else if(currAdminEdit == "Add"){
            emit AddWorker(*currUserId,*RFID,*name,groupArr);
            currAdminEdit.clear();
        }else if(currAdminEdit == "Delete"){
            emit DeleteWorker(*currUserId);
        }else if(currAdminEdit == "Update"){
            emit UpdateWorker(*currUserId,*userId,*RFID,*name,groupArr,*active);
            currAdminEdit.clear();
        }

    }else{
        qDebug() << "Current RFID is empty -> no change";
    }
}

/**
 * @brief MainWindow::adminCancel
 * clear out lineedits of admin input after cancel was clicked
 */
void MainWindow::adminCancel(){
    showAdminLineEdit->hide();
    showAdminUserIdEdit->hide();
    showAdminRFIDLineEdit->hide();
    showAdminNameLineEdit->hide();
    showAdminGroupsLineEdit->hide();
    showAdminActivateLineEdit->hide();
    showAdminLineEdit->clear();
    showAdminUserIdEdit->clear();
    showAdminRFIDLineEdit->clear();
    showAdminNameLineEdit->hide();
    showAdminGroupsLineEdit->clear();
    showAdminActivateLineEdit->clear();
    showAdminSubmit->hide();
    showAdminCancel->hide();
    showDeleteButton->show();
    showAddButton->show();
    showUpdateButton->show();
    showEmulateSearch->show();
    showAllButton->show();
}

/**
 * @brief MainWindow::showAll
 * show every worker and their groups; only admin
 */
void MainWindow::showAll(){
    for(int i = 0; i < showTableWidget->rowCount(); i++){
        showTableWidget->showRow(i);
    }
    showTableWidget->sortByColumn(0,Qt::AscendingOrder);
}

/**
 * @brief MainWindow::showTabToolTips
 * enter whatsthis mode to enable showing tool tips
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
    //only if the table hasn't been shown yet fill it up again, if it's not the first time just show or hide the widget
    if(!(nameLabel->text().isEmpty() || nameLabel->text() == "")){
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
    }else{
        QMessageBox tableInfo;
        tableInfo.setText("Nobody logged in!\nNothing to show!");
        tableInfo.exec();
    }
}

/**
 * @brief MainWindow::sql
 * fills the table with every worker, their groups and the corresponding rights
 * @param result
 * the query result in table form
 */
void MainWindow::sql(QList<QStringList> result){
    for(int i = 0; i < result.size(); i++){
        //create items to add to table with correct data
        showTableWidget->setRowCount(i+1);
        QTableWidgetItem *userIdItem = new QTableWidgetItem(result.at(i).at(0));
        QTableWidgetItem *nameItem = new QTableWidgetItem(result.at(i).at(1));
        QTableWidgetItem *rfidItem = new QTableWidgetItem(result.at(i).at(2));
        QTableWidgetItem *groupItem = new QTableWidgetItem(result.at(i).at(3));
        QTableWidgetItem *rightItem = new QTableWidgetItem(result.at(i).at(4));

        //add the items to the correct (last)row and column
        showTableWidget->setItem(showTableWidget->rowCount()-1, 0, userIdItem);
        showTableWidget->setItem(showTableWidget->rowCount()-1, 1, nameItem);
        showTableWidget->setItem(showTableWidget->rowCount()-1, 2, rfidItem);
        showTableWidget->setItem(showTableWidget->rowCount()-1, 3, groupItem);
        showTableWidget->setItem(showTableWidget->rowCount()-1, 4, rightItem);
    }
    showTableWidget->sortByColumn(0,Qt::AscendingOrder);
}

/**
 * @brief MainWindow::deleteRowInTable
 * update the showing table;delete
 * @param RFID
 * RFID of the deleted worker
 */
void MainWindow::deleteRowInTable(QString userId){
    //find the item with the exact RFID
    QList<QTableWidgetItem *> toRemove = showTableWidget->findItems(userId,Qt::MatchExactly);
    //remove whole row of worker if it exist
    for(int i = 0; i < toRemove.size(); i++){
        showTableWidget->removeRow(toRemove.at(i)->row());
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
void MainWindow::updateRowInTable(QString userId, QList<QStringList> result){
    //find the item with the exact RFID
    QList<QTableWidgetItem *> toUpdate = showTableWidget->findItems(userId,Qt::MatchExactly);

    for(int i = 0; i < toUpdate.size(); i++){
        showTableWidget->removeRow(toUpdate.at(i)->row());
    }

    for(int i = 0; i < result.size(); i++){
        //create items to add to table with correct data
        showTableWidget->setRowCount(showTableWidget->rowCount()+1);
        QTableWidgetItem *userIdItem = new QTableWidgetItem(result.at(i).at(0));
        QTableWidgetItem *nameItem = new QTableWidgetItem(result.at(i).at(1));
        QTableWidgetItem *rfidItem = new QTableWidgetItem(result.at(i).at(2));
        QTableWidgetItem *groupItem = new QTableWidgetItem(result.at(i).at(3));
        QTableWidgetItem *rightItem = new QTableWidgetItem(result.at(i).at(4));

        //add the items to the correct (last)row and column
        showTableWidget->setItem(showTableWidget->rowCount()-1, 0, userIdItem);
        showTableWidget->setItem(showTableWidget->rowCount()-1, 1, nameItem);
        showTableWidget->setItem(showTableWidget->rowCount()-1, 2, rfidItem);
        showTableWidget->setItem(showTableWidget->rowCount()-1, 3, groupItem);
        showTableWidget->setItem(showTableWidget->rowCount()-1, 4, rightItem);
    }
}

/**
 * @brief MainWindow::sortTableByNameAsc
 * does what it says on the tin
 */
void MainWindow::sortTableByNameAsc(){
    showTableWidget->sortItems(1,Qt::AscendingOrder);
    emit LoggingTest("sort by name ascending pressed",(int)LOG_BUTTON);
}
/**
 * @brief MainWindow::sortTableByIdAsc
 * does what it says on the tin
 */
void MainWindow::sortTableByIdAsc(){
    showTableWidget->sortItems(0,Qt::AscendingOrder);
    emit LoggingTest("sort by id ascending pressed",(int)LOG_BUTTON);
}
/**
 * @brief MainWindow::sortTableByNameDesc
 * does what it says on the tin
 */
void MainWindow::sortTableByNameDesc(){
    showTableWidget->sortItems(1,Qt::DescendingOrder);
    emit LoggingTest("sort by name descending pressed",(int)LOG_BUTTON);
}
/**
 * @brief MainWindow::sortTableByIdDesc
 * does what it says on the tin
 */
void MainWindow::sortTableByIdDesc(){
    showTableWidget->sortItems(0,Qt::DescendingOrder);
    emit LoggingTest("sort by id descending pressed",(int)LOG_BUTTON);
}

/**
 * @brief MainWindow::searchInTable
 * search for a certain worker in the table doesn't matter with what criterium
 * @param term
 * cirterium for search, can be name, RFID, anything
 */
void MainWindow::searchInTable(QString term){
    QList<QTableWidgetItem *> selected = showTableWidget->selectedItems();
    int row = -1;
    if(!selected.isEmpty()){
        for(int i = 0; i < selected.size(); i++){
            if(row != selected[i]->row()){
                row = selected[i]->row();
                showTableWidget->selectRow(row);
            }
        }
    }else{
        qDebug() << "non prev selected, search";
    }
    //find the worker with the exact term, doesn't matter if name, RFID or anything else
    QList<QTableWidgetItem *> search = showTableWidget->findItems(term, Qt::MatchStartsWith);
    //highlight the whole row if the term is found
    if(!search.isEmpty()){
        for(int i = 0; i < search.size(); i++){
            showTableWidget->selectRow(search[i]->row());
        }
    }else{
        qDebug() << "Worker not found, search";
    }
}

/**
 * @brief MainWindow::emulateSearch
 * emulate a search in the worker table
 * @param toggle
 * decides which rfid should be searched for
 */
void MainWindow::emulateSearch(bool toggle){
    if(toggle){
        showSearchTable->setText("0004787864");
        emit LoggingTest("emulate search 1 pressed",(int)LOG_BUTTON);
    }else{
        showSearchTable->setText("0000160302");
        emit LoggingTest("emulate search 2 pressed",(int)LOG_BUTTON);
    }
}

/**
 * @brief MainWindow::putCurrentOnTop
 * puts the currently scanned worker on top of the sql table and hides any other worker
 * @param RFID
 * scanned RFID
 */
void MainWindow::putCurrentOnTop(QString RFID){
    if(firstShow){
        emit FirstShow();
        firstShow = false;
        showFrame->show();
        emit LoggingTest("first show for scan", (int)LOG_SCAN);
    }

    for(int i = 0; i < RFID.length(); i++){
        if(RFID.at(0) != '0'){
            break;
        }
        RFID = RFID.remove(0,1);
    }

    QList<QTableWidgetItem *> search = showTableWidget->findItems(RFID, Qt::MatchExactly);
    int row = 0;

    for(int i = 0; i < showTableWidget->rowCount(); i++){
        showTableWidget->hideRow(i);
    }

    for(int i = 0; i < search.size(); i++){
        row = search[i]->row();
        QTableWidgetItem *temp1 = showTableWidget->takeItem(i,0);
        QTableWidgetItem *temp2 = showTableWidget->takeItem(i,1);
        QTableWidgetItem *temp3 = showTableWidget->takeItem(i,2);
        QTableWidgetItem *temp4 = showTableWidget->takeItem(i,3);
        QTableWidgetItem *temp5 = showTableWidget->takeItem(i,4);

        QTableWidgetItem *curr1 = showTableWidget->takeItem(row,0);
        QTableWidgetItem *curr2 = showTableWidget->takeItem(row,1);
        QTableWidgetItem *curr3 = showTableWidget->takeItem(row,2);
        QTableWidgetItem *curr4 = showTableWidget->takeItem(row,3);
        QTableWidgetItem *curr5 = showTableWidget->takeItem(row,4);

        showTableWidget->setItem(i,0,curr1);
        showTableWidget->setItem(i,1,curr2);
        showTableWidget->setItem(i,2,curr3);
        showTableWidget->setItem(i,3,curr4);
        showTableWidget->setItem(i,4,curr5);

        showTableWidget->setItem(row,0,temp1);
        showTableWidget->setItem(row,1,temp2);
        showTableWidget->setItem(row,2,temp3);
        showTableWidget->setItem(row,3,temp4);
        showTableWidget->setItem(row,4,temp5);
        showTableWidget->showRow(i);
    }
}

/**
 * @brief MainWindow::scanTest
 * admin control and scan processing
 */
void MainWindow::scanTest(QString rfid){
    scanned(rfid, QString("Location 1"));
}

/**
 * @brief MainWindow::showAdminScreen
 * show features only available for admins
 */
void MainWindow::showAdminScreen(){
    adminLogged = true;
    logOutButton->show();
    showAdminFrame->show();
    ui->statusbar->showMessage("admin logged in");
    autoLogout->show();
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
    nameLabel->clear();
    locLabel->clear();
    accessLabel->clear();
    timeLabel->clear();
    putCurrentOnTop("0");
    adminLogged = false;
    autoLogout->hide();
    if(!chip){
        emit LoggingTest("log out button pressed",(int)LOG_BUTTON);
    }

    emit LoggingTest("admin logged out",(int)LOG_COMMON);
}

/**
 * @brief MainWindow::logoutWorker
 * clear visual output and table of current worker
 */
void MainWindow::logoutWorker(){
    if(adminLogged){
        hideAdminScreen(true);
    }else{
        nameLabel->clear();
        locLabel->clear();
        accessLabel->clear();
        timeLabel->clear();
        putCurrentOnTop("0");
        emit LoggingTest("user logged out automatically",(int)LOG_COMMON);
    }
}

/**
 * @brief MainWindow::visual
 * visual output after chip was scanned
 * @param name
 * name of the worker
 * @param RFID
 * scanned RFID
 */
void MainWindow::visual(QString name, QString RFID){

    QString filePath = name.simplified();
    filePath.replace(" ","");
    emit GetCurrentTime(true, filePath);

    //fill labels with data
    QDateTime curTime = Logging::getInstance()->getCurrTime();
    nameLabel->setText(QString("Willkommen %1").arg(name));
    locLabel->setText(RFID);
    timeLabel->setText(QString("Einstechzeit: %1").arg(curTime.toString("hh:mm:ss")));

    //overwrite the current layout with the new data
    visualLayout->addWidget(nameLabel, 1, 0);
    visualLayout->addWidget(locLabel, 2, 0);
    visualLayout->addWidget(accessLabel, 1, 2);
    visualLayout->addWidget(timeLabel,2,2);

    //switch to the visual tab
    mainTabWidget->setCurrentIndex(5);
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

/**
 * @brief MainWindow::adminClicked
 * slot for scan of admin
 */
void MainWindow::adminClicked(){
    scanned(QString("0004365639"), QString("Location 1"));
    emit LoggingTest("emulate admin pressed", (int)LOG_BUTTON);
}

/*!
 * \brief MainWindow::scanned
 * function for scan processing
 * \param RFID
 * RFID of the scanned chip
 * \param loc
 * Location that the chip was scanned at
 */
void MainWindow::scanned(QString RFID, QString loc){
    qDebug() << "----------------------";

    //Check for all possible cases and does what needs to be done accordingly
    //1.admin is logged in and tries to login again
    //2.admin is logged in and someone else scans in
    //3.admin is not logged in and scans in
    //4.admin is not logged in and someone else scans in
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

    //initiates the chain reaction to all classes and saves the time in the csv file
    emit ScanInitiated(RFID, loc);

    //checks if the recieved RFID is in the correct format
    if(RFID.length() == 10){
        loc.append("RFID: ").append(RFID);
        emit LoggingTest(loc, 0);
        emit PutCurrentOnTop(RFID);
        logoutUser::getInstance()->setUserLoggedIn(true);
        logoutUser::getInstance()->setIsAdmin(adminLogged);
        logoutUser::getInstance()->setIsAutoLogoutDisabled(settings->value("autoLogout/value").value<bool>());
    }else{
        qDebug() << "RFID is in a faulty format";
        //emit LoggingTest(QString("UID is in a faulty format; UID: ").append(QString::number(UID)), 1);
    }
}
/*!
 * \brief MainWindow::logMessage
 * test function for logging
 * \param msg
 * Message that was logged
 */
void MainWindow::logMessage(QString msg){

    if(currentScan%10 == 0 && currentScan >= 20){
        QList<QLabel *> labelList = loggingTabFrame->findChildren<QLabel *>();
        for(int i = currentScan-20; i < currentScan-10; i++){
            labelList.at(i)->hide();
        }
    }

    //add the last logged message for visual output in the logging tab
    QString log = msg.remove(msg.length()-1, msg.length());
    QLabel *testLabel = new QLabel(log);
    loggingLayout->addWidget(testLabel, currentScan, 0);
    currentScan += 1;
}
