QT       += core gui sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

PKGCONFIG += libusb
# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    accessrights.cpp \
    csvhandling.cpp \
    keyboard/keyboard.cpp \
    logging.cpp \
    logoutuser.cpp \
    main.cpp \
    mainwindow.cpp \
    opendoor.cpp \
    scanner.cpp \
    sqlcheck.cpp

HEADERS += \
    accessrights.h \
    csvhandling.h \
    keyboard/keyboard.h \
    keyboard/ui_keyboard.h \
    logging.h \
    logoutuser.h \
    mainwindow.h \
    opendoor.h \
    scanner.h \
    sqlcheck.h

FORMS += \
    keyboard/keyboard.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

include(ThirdParty/qtcsv/qtcsv.pri)

DISTFILES += \
    keyboard/icons/delete_black_24x24.png \
    keyboard/icons/exit_24.png \
    keyboard/icons/keyboard_arrow_up_black_24x24.png \
    keyboard/icons/keyboard_backspace_black_24x24.png \
    keyboard/icons/keyboard_return_black_24x24.png \
    keyboard/icons/space_bar_black_24x24.png

RESOURCES += \
    resources.qrc
