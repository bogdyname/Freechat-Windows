/****************************************************************************
** Meta object code from reading C++ file 'connectionf2f.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../test/connectionf2f.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'connectionf2f.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ConnectionF2F_t {
    QByteArrayData data[12];
    char stringdata0[130];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ConnectionF2F_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ConnectionF2F_t qt_meta_stringdata_ConnectionF2F = {
    {
QT_MOC_LITERAL(0, 0, 13), // "ConnectionF2F"
QT_MOC_LITERAL(1, 14, 22), // "WriteIpAddressFromPeer"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 9), // "ReadyRead"
QT_MOC_LITERAL(4, 48, 9), // "DoConnect"
QT_MOC_LITERAL(5, 58, 9), // "Connected"
QT_MOC_LITERAL(6, 68, 12), // "Disconnected"
QT_MOC_LITERAL(7, 81, 10), // "TaskResult"
QT_MOC_LITERAL(8, 92, 5), // "uint&"
QT_MOC_LITERAL(9, 98, 6), // "Number"
QT_MOC_LITERAL(10, 105, 18), // "BytesWrittenOfData"
QT_MOC_LITERAL(11, 124, 5) // "bytes"

    },
    "ConnectionF2F\0WriteIpAddressFromPeer\0"
    "\0ReadyRead\0DoConnect\0Connected\0"
    "Disconnected\0TaskResult\0uint&\0Number\0"
    "BytesWrittenOfData\0bytes"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ConnectionF2F[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x0a /* Public */,
       3,    0,   50,    2, 0x0a /* Public */,
       4,    0,   51,    2, 0x0a /* Public */,
       5,    0,   52,    2, 0x0a /* Public */,
       6,    0,   53,    2, 0x0a /* Public */,
       7,    1,   54,    2, 0x0a /* Public */,
      10,    1,   57,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void, QMetaType::LongLong,   11,

       0        // eod
};

void ConnectionF2F::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ConnectionF2F *_t = static_cast<ConnectionF2F *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->WriteIpAddressFromPeer(); break;
        case 1: _t->ReadyRead(); break;
        case 2: _t->DoConnect(); break;
        case 3: _t->Connected(); break;
        case 4: _t->Disconnected(); break;
        case 5: _t->TaskResult((*reinterpret_cast< uint(*)>(_a[1]))); break;
        case 6: _t->BytesWrittenOfData((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ConnectionF2F::staticMetaObject = { {
    &QTcpSocket::staticMetaObject,
    qt_meta_stringdata_ConnectionF2F.data,
    qt_meta_data_ConnectionF2F,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ConnectionF2F::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ConnectionF2F::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ConnectionF2F.stringdata0))
        return static_cast<void*>(this);
    return QTcpSocket::qt_metacast(_clname);
}

int ConnectionF2F::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTcpSocket::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
