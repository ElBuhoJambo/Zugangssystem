/****************************************************************************
** Meta object code from reading C++ file 'sqlcheck.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Zugangssystem/sqlcheck.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sqlcheck.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_sqlCheck_t {
    QByteArrayData data[20];
    char stringdata0[171];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_sqlCheck_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_sqlCheck_t qt_meta_stringdata_sqlCheck = {
    {
QT_MOC_LITERAL(0, 0, 8), // "sqlCheck"
QT_MOC_LITERAL(1, 9, 6), // "Result"
QT_MOC_LITERAL(2, 16, 0), // ""
QT_MOC_LITERAL(3, 17, 6), // "access"
QT_MOC_LITERAL(4, 24, 4), // "RFID"
QT_MOC_LITERAL(5, 29, 3), // "loc"
QT_MOC_LITERAL(6, 33, 4), // "name"
QT_MOC_LITERAL(7, 38, 9), // "ShowTable"
QT_MOC_LITERAL(8, 48, 9), // "DeleteRow"
QT_MOC_LITERAL(9, 58, 12), // "UpdateWorker"
QT_MOC_LITERAL(10, 71, 8), // "location"
QT_MOC_LITERAL(11, 80, 8), // "currRFID"
QT_MOC_LITERAL(12, 89, 10), // "logMessage"
QT_MOC_LITERAL(13, 100, 3), // "msg"
QT_MOC_LITERAL(14, 104, 5), // "index"
QT_MOC_LITERAL(15, 110, 14), // "receiveRequest"
QT_MOC_LITERAL(16, 125, 9), // "showTable"
QT_MOC_LITERAL(17, 135, 9), // "addWorker"
QT_MOC_LITERAL(18, 145, 12), // "deleteWorker"
QT_MOC_LITERAL(19, 158, 12) // "updateWorker"

    },
    "sqlCheck\0Result\0\0access\0RFID\0loc\0name\0"
    "ShowTable\0DeleteRow\0UpdateWorker\0"
    "location\0currRFID\0logMessage\0msg\0index\0"
    "receiveRequest\0showTable\0addWorker\0"
    "deleteWorker\0updateWorker"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_sqlCheck[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    4,   64,    2, 0x06 /* Public */,
       7,    4,   73,    2, 0x06 /* Public */,
       8,    1,   82,    2, 0x06 /* Public */,
       9,    5,   85,    2, 0x06 /* Public */,
      12,    2,   96,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      15,    2,  101,    2, 0x0a /* Public */,
      16,    0,  106,    2, 0x0a /* Public */,
      17,    4,  107,    2, 0x0a /* Public */,
      18,    1,  116,    2, 0x0a /* Public */,
      19,    5,  119,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool, QMetaType::QString, QMetaType::QString, QMetaType::QString,    3,    4,    5,    6,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString,    6,    5,    4,    3,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString,    4,   10,    6,    3,   11,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,   13,   14,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    4,    5,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString,    4,   10,    6,    3,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString,    4,   10,    6,    3,   11,

       0        // eod
};

void sqlCheck::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        sqlCheck *_t = static_cast<sqlCheck *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->Result((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4]))); break;
        case 1: _t->ShowTable((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4]))); break;
        case 2: _t->DeleteRow((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->UpdateWorker((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< QString(*)>(_a[5]))); break;
        case 4: _t->logMessage((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 5: _t->receiveRequest((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 6: _t->showTable(); break;
        case 7: _t->addWorker((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4]))); break;
        case 8: _t->deleteWorker((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 9: _t->updateWorker((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< QString(*)>(_a[5]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (sqlCheck::*)(bool , QString , QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&sqlCheck::Result)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (sqlCheck::*)(QString , QString , QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&sqlCheck::ShowTable)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (sqlCheck::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&sqlCheck::DeleteRow)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (sqlCheck::*)(QString , QString , QString , QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&sqlCheck::UpdateWorker)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (sqlCheck::*)(QString , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&sqlCheck::logMessage)) {
                *result = 4;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject sqlCheck::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_sqlCheck.data,
      qt_meta_data_sqlCheck,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *sqlCheck::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *sqlCheck::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_sqlCheck.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int sqlCheck::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void sqlCheck::Result(bool _t1, QString _t2, QString _t3, QString _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void sqlCheck::ShowTable(QString _t1, QString _t2, QString _t3, QString _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void sqlCheck::DeleteRow(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void sqlCheck::UpdateWorker(QString _t1, QString _t2, QString _t3, QString _t4, QString _t5)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void sqlCheck::logMessage(QString _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
