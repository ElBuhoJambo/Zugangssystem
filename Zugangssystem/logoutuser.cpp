#include "logoutuser.h"

logoutUser* logoutUser::lInstance = new logoutUser;

/**
 * @brief logoutUser::getInstance
 * returns instance for use in other classes
 * @return
 */
logoutUser* logoutUser::getInstance(void){
    return lInstance;
}

logoutUser::logoutUser(QObject *parent) : QThread(parent){
    moveToThread(this);
    start();
}

logoutUser::~logoutUser(){

}

/**
 * @brief logoutUser::run
 * run function for thread
 */
void logoutUser::run(){
    initTimer();
    QThread::exec();
}

/**
 * @brief logoutUser::initTimer
 * initializes timer for checking for a user
 */
void logoutUser::initTimer(){
    logoutTimer = new QTimer(this);
    logoutTimer->setInterval(100);
    logoutTimer->setSingleShot(false);
    connect(logoutTimer, &QTimer::timeout, this, &logoutUser::checkForUser);
    logoutTimer->start();
}

/**
 * @brief logoutUser::checkForUser
 * checks if a user is logged in and starts a singleshot timer for logging a user out after 7 secs
 * if auto logout is disabled and the it is the admin that is logged in than don't start the timer
 */
void logoutUser::checkForUser(){
    if(userLoggedIn){
        if(isAutoLogoutDisabled && isAdmin){
            if(singleShotLogout != NULL){
                singleShotLogout->stop();
            }
            return;
        }
        setUserLoggedIn(false);
        singleShotLogout = new QTimer;
        singleShotLogout->setSingleShot(true);
        singleShotLogout->setInterval(7000);
        connect(singleShotLogout, &QTimer::timeout, this, &logoutUser::logout);
        singleShotLogout->start();
    }
}

/**
 * @brief logoutUser::logout
 * emit to clear everything of the logged out user
 */
void logoutUser::logout(){
    emit Logout();
}

/**
 * @brief logoutUser::getUserLoggedIn
 * returns the current status if a user is logged in for use in the main class
 * @return
 * current status if a user is logged in
 */
bool logoutUser::getUserLoggedIn(){
    return userLoggedIn;
}

/**
 * @brief logoutUser::setUserLoggedIn
 * sets the new status if any user is logged in for use in the main class
 * @param userLoggedIn
 * new status if any user is logged in
 */
void logoutUser::setUserLoggedIn(bool userLoggedIn){
    this->userLoggedIn = userLoggedIn;
}

/**
 * @brief logoutUser::setIsAdmin
 * sets the new status if the admin is logged in for use in the main class
 * @param isAdmin
 * new status if the admin is logged in
 */
void logoutUser::setIsAdmin(bool isAdmin){
    this->isAdmin = isAdmin;
}

/**
 * @brief logoutUser::setIsAutoLogoutEnabled
 * sets the new status if the auto logout is enabled for use in the main class
 * @param isAutoLogoutEnabled
 * new status if auto logout is enabled
 */
void logoutUser::setIsAutoLogoutDisabled(bool isAutoLogoutDisabled){
    this->isAutoLogoutDisabled = isAutoLogoutDisabled;
}
