/****************************************************************************
** Meta object code from reading C++ file 'Piece.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../Piece.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Piece.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Piece_t {
    QByteArrayData data[8];
    char stringdata0[105];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Piece_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Piece_t qt_meta_stringdata_Piece = {
    {
QT_MOC_LITERAL(0, 0, 5), // "Piece"
QT_MOC_LITERAL(1, 6, 17), // "infoChangedSignal"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 16), // "beAttackedSignal"
QT_MOC_LITERAL(4, 42, 12), // "attackPoints"
QT_MOC_LITERAL(5, 55, 19), // "repaintScreenSignal"
QT_MOC_LITERAL(6, 75, 14), // "beAttackedSlot"
QT_MOC_LITERAL(7, 90, 14) // "updateInfoSlot"

    },
    "Piece\0infoChangedSignal\0\0beAttackedSignal\0"
    "attackPoints\0repaintScreenSignal\0"
    "beAttackedSlot\0updateInfoSlot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Piece[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x06 /* Public */,
       3,    1,   40,    2, 0x06 /* Public */,
       5,    0,   43,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    1,   44,    2, 0x0a /* Public */,
       7,    0,   47,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void,

       0        // eod
};

void Piece::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Piece *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->infoChangedSignal(); break;
        case 1: _t->beAttackedSignal((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->repaintScreenSignal(); break;
        case 3: _t->beAttackedSlot((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 4: _t->updateInfoSlot(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Piece::*)() const;
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Piece::infoChangedSignal)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Piece::*)(int ) const;
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Piece::beAttackedSignal)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Piece::*)() const;
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Piece::repaintScreenSignal)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Piece::staticMetaObject = { {
    QMetaObject::SuperData::link<QLabel::staticMetaObject>(),
    qt_meta_stringdata_Piece.data,
    qt_meta_data_Piece,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Piece::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Piece::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Piece.stringdata0))
        return static_cast<void*>(this);
    return QLabel::qt_metacast(_clname);
}

int Piece::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLabel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void Piece::infoChangedSignal()const
{
    QMetaObject::activate(const_cast< Piece *>(this), &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void Piece::beAttackedSignal(int _t1)const
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(const_cast< Piece *>(this), &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Piece::repaintScreenSignal()const
{
    QMetaObject::activate(const_cast< Piece *>(this), &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
