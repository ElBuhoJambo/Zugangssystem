/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Zugangssystem/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[26];
    char stringdata0[244];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 13), // "ScanInitiated"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 4), // "RFID"
QT_MOC_LITERAL(4, 31, 8), // "Location"
QT_MOC_LITERAL(5, 40, 11), // "LoggingTest"
QT_MOC_LITERAL(6, 52, 3), // "msg"
QT_MOC_LITERAL(7, 56, 5), // "index"
QT_MOC_LITERAL(8, 62, 9), // "FirstShow"
QT_MOC_LITERAL(9, 72, 12), // "loc1Clicked1"
QT_MOC_LITERAL(10, 85, 12), // "loc2Clicked1"
QT_MOC_LITERAL(11, 98, 12), // "loc3Clicked1"
QT_MOC_LITERAL(12, 111, 12), // "loc1Clicked2"
QT_MOC_LITERAL(13, 124, 12), // "loc2Clicked2"
QT_MOC_LITERAL(14, 137, 12), // "loc3Clicked2"
QT_MOC_LITERAL(15, 150, 8), // "scanTest"
QT_MOC_LITERAL(16, 159, 6), // "visual"
QT_MOC_LITERAL(17, 166, 4), // "name"
QT_MOC_LITERAL(18, 171, 3), // "loc"
QT_MOC_LITERAL(19, 175, 6), // "access"
QT_MOC_LITERAL(20, 182, 10), // "logMessage"
QT_MOC_LITERAL(21, 193, 3), // "sql"
QT_MOC_LITERAL(22, 197, 9), // "showTable"
QT_MOC_LITERAL(23, 207, 4), // "show"
QT_MOC_LITERAL(24, 212, 15), // "hideAdminScreen"
QT_MOC_LITERAL(25, 228, 15) // "showTabToolTips"

    },
    "MainWindow\0ScanInitiated\0\0RFID\0Location\0"
    "LoggingTest\0msg\0index\0FirstShow\0"
    "loc1Clicked1\0loc2Clicked1\0loc3Clicked1\0"
    "loc1Clicked2\0loc2Clicked2\0loc3Clicked2\0"
    "scanTest\0visual\0name\0loc\0access\0"
    "logMessage\0sql\0showTable\0show\0"
    "hideAdminScreen\0showTabToolTips"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   94,    2, 0x06 /* Public */,
       5,    2,   99,    2, 0x06 /* Public */,
       8,    0,  104,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    0,  105,    2, 0x0a /* Public */,
      10,    0,  106,    2, 0x0a /* Public */,
      11,    0,  107,    2, 0x0a /* Public */,
      12,    0,  108,    2, 0x0a /* Public */,
      13,    0,  109,    2, 0x0a /* Public */,
      14,    0,  110,    2, 0x0a /* Public */,
      15,    0,  111,    2, 0x0a /* Public */,
      16,    3,  112,    2, 0x0a /* Public */,
      20,    1,  119,    2, 0x0a /* Public */,
      21,    4,  122,    2, 0x0a /* Public */,
      22,    1,  131,    2, 0x0a /* Public */,
      24,    0,  134,    2, 0x0a /* Public */,
      25,    1,  135,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    3,    4,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,    6,    7,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::Bool,   17,   18,   19,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString,   17,    3,   18,   19,
    QMetaType::Void, QMetaType::Bool,   23,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   23,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->ScanInitiated((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 1: _t->LoggingTest((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->FirstShow(); break;
        case 3: _t->loc1Clicked1(); break;
        case 4: _t->loc2Clicked1(); break;
        case 5: _t->loc3Clicked1(); break;
        case 6: _t->loc1Clicked2(); break;
        case 7: _t->loc2Clicked2(); break;
        case 8: _t->loc3Clicked2(); break;
        case 9: _t->scanTest(); break;
        case 10: _t->visual((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 11: _t->logMessage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 12: _t->sql((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4]))); break;
        case 13: _t->showTable((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 14: _t->hideAdminScreen(); break;
        case 15: _t->showTabToolTips((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MainWindow::*)(QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::ScanInitiated)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(QString , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::LoggingTest)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::FirstShow)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::ScanInitiated(QString _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MainWindow::LoggingTest(QString _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MainWindow::FirstShow()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
