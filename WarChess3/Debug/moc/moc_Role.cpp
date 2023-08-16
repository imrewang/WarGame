/****************************************************************************
** Meta object code from reading C++ file 'Role.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../Role.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Role.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Role_t {
    QByteArrayData data[14];
    char stringdata0[189];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Role_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Role_t qt_meta_stringdata_Role = {
    {
QT_MOC_LITERAL(0, 0, 4), // "Role"
QT_MOC_LITERAL(1, 5, 14), // "roleMoveSignal"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 5), // "Role*"
QT_MOC_LITERAL(4, 27, 16), // "roleAttackSignal"
QT_MOC_LITERAL(5, 44, 14), // "roleSkipSignal"
QT_MOC_LITERAL(6, 59, 14), // "killRoleSignal"
QT_MOC_LITERAL(7, 74, 22), // "displayHintLabelSignal"
QT_MOC_LITERAL(8, 97, 22), // "hideCancelButtonSignal"
QT_MOC_LITERAL(9, 120, 14), // "beAttackedSlot"
QT_MOC_LITERAL(10, 135, 12), // "attackPoints"
QT_MOC_LITERAL(11, 148, 12), // "roleMoveSlot"
QT_MOC_LITERAL(12, 161, 14), // "roleAttackSlot"
QT_MOC_LITERAL(13, 176, 12) // "roleSkipSlot"

    },
    "Role\0roleMoveSignal\0\0Role*\0roleAttackSignal\0"
    "roleSkipSignal\0killRoleSignal\0"
    "displayHintLabelSignal\0hideCancelButtonSignal\0"
    "beAttackedSlot\0attackPoints\0roleMoveSlot\0"
    "roleAttackSlot\0roleSkipSlot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Role[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   64,    2, 0x06 /* Public */,
       4,    1,   67,    2, 0x06 /* Public */,
       5,    1,   70,    2, 0x06 /* Public */,
       6,    1,   73,    2, 0x06 /* Public */,
       7,    1,   76,    2, 0x06 /* Public */,
       8,    0,   79,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    1,   80,    2, 0x0a /* Public */,
      11,    0,   83,    2, 0x0a /* Public */,
      12,    0,   84,    2, 0x0a /* Public */,
      13,    0,   85,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Role::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Role *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->roleMoveSignal((*reinterpret_cast< Role*(*)>(_a[1]))); break;
        case 1: _t->roleAttackSignal((*reinterpret_cast< Role*(*)>(_a[1]))); break;
        case 2: _t->roleSkipSignal((*reinterpret_cast< Role*(*)>(_a[1]))); break;
        case 3: _t->killRoleSignal((*reinterpret_cast< Role*(*)>(_a[1]))); break;
        case 4: _t->displayHintLabelSignal((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->hideCancelButtonSignal(); break;
        case 6: _t->beAttackedSlot((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 7: _t->roleMoveSlot(); break;
        case 8: _t->roleAttackSlot(); break;
        case 9: _t->roleSkipSlot(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Role* >(); break;
            }
            break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Role* >(); break;
            }
            break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Role* >(); break;
            }
            break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Role* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Role::*)(Role * ) const;
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Role::roleMoveSignal)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Role::*)(Role * ) const;
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Role::roleAttackSignal)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Role::*)(Role * ) const;
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Role::roleSkipSignal)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (Role::*)(Role * ) const;
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Role::killRoleSignal)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (Role::*)(QString ) const;
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Role::displayHintLabelSignal)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (Role::*)() const;
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Role::hideCancelButtonSignal)) {
                *result = 5;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Role::staticMetaObject = { {
    QMetaObject::SuperData::link<Piece::staticMetaObject>(),
    qt_meta_stringdata_Role.data,
    qt_meta_data_Role,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Role::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Role::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Role.stringdata0))
        return static_cast<void*>(this);
    return Piece::qt_metacast(_clname);
}

int Role::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Piece::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void Role::roleMoveSignal(Role * _t1)const
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(const_cast< Role *>(this), &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Role::roleAttackSignal(Role * _t1)const
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(const_cast< Role *>(this), &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Role::roleSkipSignal(Role * _t1)const
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(const_cast< Role *>(this), &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Role::killRoleSignal(Role * _t1)const
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(const_cast< Role *>(this), &staticMetaObject, 3, _a);
}

// SIGNAL 4
void Role::displayHintLabelSignal(QString _t1)const
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(const_cast< Role *>(this), &staticMetaObject, 4, _a);
}

// SIGNAL 5
void Role::hideCancelButtonSignal()const
{
    QMetaObject::activate(const_cast< Role *>(this), &staticMetaObject, 5, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
