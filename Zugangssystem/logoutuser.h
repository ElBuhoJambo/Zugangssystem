#ifndef LOGOUTUSER_H
#define LOGOUTUSER_H

#include <QObject>
#include <QThread>
#include <QTimer>

#include "logging.h"

class logoutUser : public QThread
{
    Q_OBJECT

public:
    static logoutUser* getInstance(void);
    bool getUserLoggedIn();
    void setUserLoggedIn(bool userLoggedIn);
    void setIsAdmin(bool isAdmin);
    void setIsAutoLogoutDisabled(bool isAutoLogoutDisabled);

public slots:
    void checkForUser();
    void logout();

signals:
    void Logout();

protected:
    void run();

private:
    logoutUser(QObject *parent = 0);
    ~logoutUser();
    void initTimer(void);

    static logoutUser* lInstance;
    bool userLoggedIn = false;
    QTimer *logoutTimer;
    QTimer *singleShotLogout;
    bool isAdmin = false;
    bool isAutoLogoutDisabled = true;
};

#endif // LOGOUTUSER_H
