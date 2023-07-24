/****************************************************************************
** Meta object code from reading C++ file 'character.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../character.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'character.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Character_t {
    QByteArrayData data[18];
    char stringdata0[233];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Character_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Character_t qt_meta_stringdata_Character = {
    {
QT_MOC_LITERAL(0, 0, 9), // "Character"
QT_MOC_LITERAL(1, 10, 19), // "characterMoveAction"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 10), // "Character*"
QT_MOC_LITERAL(4, 42, 22), // "characterAttrackAction"
QT_MOC_LITERAL(5, 65, 11), // "infoChanged"
QT_MOC_LITERAL(6, 77, 11), // "beAttracked"
QT_MOC_LITERAL(7, 89, 7), // "attrack"
QT_MOC_LITERAL(8, 97, 15), // "dieOneCharacter"
QT_MOC_LITERAL(9, 113, 15), // "endOneCharacter"
QT_MOC_LITERAL(10, 129, 10), // "submitHint"
QT_MOC_LITERAL(11, 140, 16), // "hideCancelButton"
QT_MOC_LITERAL(12, 157, 13), // "repaintScreen"
QT_MOC_LITERAL(13, 171, 10), // "moveAction"
QT_MOC_LITERAL(14, 182, 13), // "attrackAction"
QT_MOC_LITERAL(15, 196, 10), // "skipAction"
QT_MOC_LITERAL(16, 207, 14), // "attrackedEvent"
QT_MOC_LITERAL(17, 222, 10) // "updateInfo"

    },
    "Character\0characterMoveAction\0\0"
    "Character*\0characterAttrackAction\0"
    "infoChanged\0beAttracked\0attrack\0"
    "dieOneCharacter\0endOneCharacter\0"
    "submitHint\0hideCancelButton\0repaintScreen\0"
    "moveAction\0attrackAction\0skipAction\0"
    "attrackedEvent\0updateInfo"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Character[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       9,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   84,    2, 0x06 /* Public */,
       4,    1,   87,    2, 0x06 /* Public */,
       5,    0,   90,    2, 0x06 /* Public */,
       6,    1,   91,    2, 0x06 /* Public */,
       8,    1,   94,    2, 0x06 /* Public */,
       9,    1,   97,    2, 0x06 /* Public */,
      10,    1,  100,    2, 0x06 /* Public */,
      11,    0,  103,    2, 0x06 /* Public */,
      12,    0,  104,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      13,    0,  105,    2, 0x0a /* Public */,
      14,    0,  106,    2, 0x0a /* Public */,
      15,    0,  107,    2, 0x0a /* Public */,
      16,    1,  108,    2, 0x0a /* Public */,
      17,    0,  111,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void,

       0        // eod
};

void Character::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Character *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->characterMoveAction((*reinterpret_cast< Character*(*)>(_a[1]))); break;
        case 1: _t->characterAttrackAction((*reinterpret_cast< Character*(*)>(_a[1]))); break;
        case 2: _t->infoChanged(); break;
        case 3: _t->beAttracked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->dieOneCharacter((*reinterpret_cast< Character*(*)>(_a[1]))); break;
        case 5: _t->endOneCharacter((*reinterpret_cast< Character*(*)>(_a[1]))); break;
        case 6: _t->submitHint((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: _t->hideCancelButton(); break;
        case 8: _t->repaintScreen(); break;
        case 9: _t->moveAction(); break;
        case 10: _t->attrackAction(); break;
        case 11: _t->skipAction(); break;
        case 12: _t->attrackedEvent((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 13: _t->updateInfo(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Character* >(); break;
            }
            break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Character* >(); break;
            }
            break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Character* >(); break;
            }
            break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Character* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Character::*)(Character * ) const;
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Character::characterMoveAction)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Character::*)(Character * ) const;
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Character::characterAttrackAction)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Character::*)() const;
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Character::infoChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (Character::*)(int ) const;
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Character::beAttracked)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (Character::*)(Character * ) const;
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Character::dieOneCharacter)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (Character::*)(Character * ) const;
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Character::endOneCharacter)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (Character::*)(QString ) const;
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Character::submitHint)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (Character::*)() const;
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Character::hideCancelButton)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (Character::*)() const;
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Character::repaintScreen)) {
                *result = 8;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Character::staticMetaObject = { {
    QMetaObject::SuperData::link<QLabel::staticMetaObject>(),
    qt_meta_stringdata_Character.data,
    qt_meta_data_Character,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Character::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Character::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Character.stringdata0))
        return static_cast<void*>(this);
    return QLabel::qt_metacast(_clname);
}

int Character::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLabel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void Character::characterMoveAction(Character * _t1)const
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(const_cast< Character *>(this), &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Character::characterAttrackAction(Character * _t1)const
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(const_cast< Character *>(this), &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Character::infoChanged()const
{
    QMetaObject::activate(const_cast< Character *>(this), &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void Character::beAttracked(int _t1)const
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(const_cast< Character *>(this), &staticMetaObject, 3, _a);
}

// SIGNAL 4
void Character::dieOneCharacter(Character * _t1)const
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(const_cast< Character *>(this), &staticMetaObject, 4, _a);
}

// SIGNAL 5
void Character::endOneCharacter(Character * _t1)const
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(const_cast< Character *>(this), &staticMetaObject, 5, _a);
}

// SIGNAL 6
void Character::submitHint(QString _t1)const
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(const_cast< Character *>(this), &staticMetaObject, 6, _a);
}

// SIGNAL 7
void Character::hideCancelButton()const
{
    QMetaObject::activate(const_cast< Character *>(this), &staticMetaObject, 7, nullptr);
}

// SIGNAL 8
void Character::repaintScreen()const
{
    QMetaObject::activate(const_cast< Character *>(this), &staticMetaObject, 8, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
