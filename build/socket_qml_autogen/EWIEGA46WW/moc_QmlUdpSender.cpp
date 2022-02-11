/****************************************************************************
** Meta object code from reading C++ file 'QmlUdpSender.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "QmlUdpSender.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QmlUdpSender.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_UdpCom__StringSender_t {
    QByteArrayData data[9];
    char stringdata0[90];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_UdpCom__StringSender_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_UdpCom__StringSender_t qt_meta_stringdata_UdpCom__StringSender = {
    {
QT_MOC_LITERAL(0, 0, 20), // "UdpCom::StringSender"
QT_MOC_LITERAL(1, 21, 11), // "portChanged"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 11), // "hostChanged"
QT_MOC_LITERAL(4, 46, 13), // "stringChanged"
QT_MOC_LITERAL(5, 60, 12), // "createSocket"
QT_MOC_LITERAL(6, 73, 4), // "host"
QT_MOC_LITERAL(7, 78, 4), // "port"
QT_MOC_LITERAL(8, 83, 6) // "string"

    },
    "UdpCom::StringSender\0portChanged\0\0"
    "hostChanged\0stringChanged\0createSocket\0"
    "host\0port\0string"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_UdpCom__StringSender[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       3,   38, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x06 /* Public */,
       3,    0,   35,    2, 0x06 /* Public */,
       4,    0,   36,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   37,    2, 0x09 /* Protected */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,

 // properties: name, type, flags
       6, QMetaType::QString, 0x00495103,
       7, QMetaType::QString, 0x00495103,
       8, QMetaType::QString, 0x00495103,

 // properties: notify_signal_id
       1,
       0,
       2,

       0        // eod
};

void UdpCom::StringSender::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<StringSender *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->portChanged(); break;
        case 1: _t->hostChanged(); break;
        case 2: _t->stringChanged(); break;
        case 3: _t->createSocket(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (StringSender::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StringSender::portChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (StringSender::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StringSender::hostChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (StringSender::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StringSender::stringChanged)) {
                *result = 2;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<StringSender *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = _t->host(); break;
        case 1: *reinterpret_cast< QString*>(_v) = _t->port(); break;
        case 2: *reinterpret_cast< QString*>(_v) = _t->string(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<StringSender *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setHost(*reinterpret_cast< QString*>(_v)); break;
        case 1: _t->setPort(*reinterpret_cast< QString*>(_v)); break;
        case 2: _t->setString(*reinterpret_cast< QString*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject UdpCom::StringSender::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_UdpCom__StringSender.data,
    qt_meta_data_UdpCom__StringSender,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *UdpCom::StringSender::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *UdpCom::StringSender::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_UdpCom__StringSender.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int UdpCom::StringSender::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 3;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void UdpCom::StringSender::portChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void UdpCom::StringSender::hostChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void UdpCom::StringSender::stringChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
