/****************************************************************************
** Meta object code from reading C++ file 'logging.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Zugangssystem/logging.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'logging.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Logging_t {
    QByteArrayData data[11];
    char stringdata0[123];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Logging_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Logging_t qt_meta_stringdata_Logging = {
    {
QT_MOC_LITERAL(0, 0, 7), // "Logging"
QT_MOC_LITERAL(1, 8, 16), // "stopCopyLogfiles"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 14), // "LogMessageTest"
QT_MOC_LITERAL(4, 41, 3), // "msg"
QT_MOC_LITERAL(5, 45, 10), // "logMessage"
QT_MOC_LITERAL(6, 56, 5), // "index"
QT_MOC_LITERAL(7, 62, 12), // "copyLogfiles"
QT_MOC_LITERAL(8, 75, 11), // "destination"
QT_MOC_LITERAL(9, 87, 14), // "logTimeIsvalid"
QT_MOC_LITERAL(10, 102, 20) // "checkExternalLogging"

    },
    "Logging\0stopCopyLogfiles\0\0LogMessageTest\0"
    "msg\0logMessage\0index\0copyLogfiles\0"
    "destination\0logTimeIsvalid\0"
    "checkExternalLogging"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Logging[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x06 /* Public */,
       3,    1,   50,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    2,   53,    2, 0x0a /* Public */,
       5,    1,   58,    2, 0x2a /* Public | MethodCloned */,
       7,    1,   61,    2, 0x0a /* Public */,
       9,    0,   64,    2, 0x0a /* Public */,
      10,    0,   65,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    4,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::Int,    4,    6,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Logging::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Logging *_t = static_cast<Logging *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->stopCopyLogfiles(); break;
        case 1: _t->LogMessageTest((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->logMessage((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->logMessage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->copyLogfiles((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->logTimeIsvalid(); break;
        case 6: _t->checkExternalLogging(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Logging::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Logging::stopCopyLogfiles)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Logging::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Logging::LogMessageTest)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Logging::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_Logging.data,
      qt_meta_data_Logging,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Logging::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Logging::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Logging.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int Logging::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void Logging::stopCopyLogfiles()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void Logging::LogMessageTest(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE