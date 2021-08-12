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
};

#endif // LOGOUTUSER_H
