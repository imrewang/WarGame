/****************************************************************************
** Meta object code from reading C++ file 'base.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../base.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'base.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Base_t {
    QByteArrayData data[10];
    char stringdata0[95];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Base_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Base_t qt_meta_stringdata_Base = {
    {
QT_MOC_LITERAL(0, 0, 4), // "Base"
QT_MOC_LITERAL(1, 5, 11), // "infoChanged"
QT_MOC_LITERAL(2, 17, 0), // ""
QT_MOC_LITERAL(3, 18, 11), // "beAttracked"
QT_MOC_LITERAL(4, 30, 7), // "attrack"
QT_MOC_LITERAL(5, 38, 10), // "dieOneBase"
QT_MOC_LITERAL(6, 49, 5), // "Base*"
QT_MOC_LITERAL(7, 55, 13), // "repaintScreen"
QT_MOC_LITERAL(8, 69, 14), // "attrackedEvent"
QT_MOC_LITERAL(9, 84, 10) // "updateInfo"

    },
    "Base\0infoChanged\0\0beAttracked\0attrack\0"
    "dieOneBase\0Base*\0repaintScreen\0"
    "attrackedEvent\0updateInfo"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Base[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x06 /* Public */,
       3,    1,   45,    2, 0x06 /* Public */,
       5,    1,   48,    2, 0x06 /* Public */,
       7,    0,   51,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    1,   52,    2, 0x0a /* Public */,
       9,    0,   55,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, 0x80000000 | 6,    2,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void,

       0        // eod
};

void Base::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Base *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->infoChanged(); break;
        case 1: _t->beAttracked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->dieOneBase((*reinterpret_cast< Base*(*)>(_a[1]))); break;
        case 3: _t->repaintScreen(); break;
        case 4: _t->attrackedEvent((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 5: _t->updateInfo(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Base* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Base::*)() const;
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Base::infoChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Base::*)(int ) const;
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Base::beAttracked)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Base::*)(Base * ) const;
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Base::dieOneBase)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (Base::*)() const;
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Base::repaintScreen)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Base::staticMetaObject = { {
    QMetaObject::SuperData::link<QLabel::staticMetaObject>(),
    qt_meta_stringdata_Base.data,
    qt_meta_data_Base,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Base::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Base::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Base.stringdata0))
        return static_cast<void*>(this);
    return QLabel::qt_metacast(_clname);
}

int Base::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLabel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void Base::infoChanged()const
{
    QMetaObject::activate(const_cast< Base *>(this), &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void Base::beAttracked(int _t1)const
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(const_cast< Base *>(this), &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Base::dieOneBase(Base * _t1)const
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(const_cast< Base *>(this), &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Base::repaintScreen()const
{
    QMetaObject::activate(const_cast< Base *>(this), &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
