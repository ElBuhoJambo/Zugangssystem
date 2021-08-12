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
 */
void logoutUser::checkForUser(){
    if(userLoggedIn){
        setUserLoggedIn(false);
        QTimer::singleShot(7000, this, &logoutUser::logout);
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
 * sets the new status if a user is logged in for use in the main class
 * @param userLoggedIn
 * new status if a user is logged in
 */
void logoutUser::setUserLoggedIn(bool userLoggedIn){
    this->userLoggedIn = userLoggedIn;
}
