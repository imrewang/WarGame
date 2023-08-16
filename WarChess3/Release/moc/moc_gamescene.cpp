/****************************************************************************
** Meta object code from reading C++ file 'gamescene.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../gamescene.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gamescene.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_GameScene_t {
    QByteArrayData data[18];
    char stringdata0[201];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GameScene_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GameScene_t qt_meta_stringdata_GameScene = {
    {
QT_MOC_LITERAL(0, 0, 9), // "GameScene"
QT_MOC_LITERAL(1, 10, 6), // "myLossSignal"
QT_MOC_LITERAL(2, 17, 0), // ""
QT_MOC_LITERAL(3, 18, 5), // "myWinSignal"
QT_MOC_LITERAL(4, 24, 7), // "restartSignal"
QT_MOC_LITERAL(5, 32, 4), // "exitSignal"
QT_MOC_LITERAL(6, 37, 15), // "redrawRoleSlot"
QT_MOC_LITERAL(7, 53, 10), // "redrawBaseSlot"
QT_MOC_LITERAL(8, 64, 18), // "findPathSlot"
QT_MOC_LITERAL(9, 83, 10), // "Character*"
QT_MOC_LITERAL(10, 94, 21), // "roleAttackSlot"
QT_MOC_LITERAL(11, 116, 20), // "roleEndSlot"
QT_MOC_LITERAL(12, 137, 20), // "roleDiesSlot"
QT_MOC_LITERAL(13, 158, 15), // "baseDestroyedSlot"
QT_MOC_LITERAL(14, 174, 5), // "Base*"
QT_MOC_LITERAL(15, 180, 11), // "showHintSlot"
QT_MOC_LITERAL(16, 192, 3), // "str"
QT_MOC_LITERAL(17, 196, 4) // "next"

    },
    "GameScene\0myLoss\0\0myWin\0restart\0exit\0"
    "redrawCharacter\0redrawBase\0"
    "characterMoveEvent\0Character*\0"
    "characterAttrackEvent\0endOneCharacterEvent\0"
    "dieOneCharacterEvent\0dieOneBaseEvent\0"
    "Base*\0receiveHint\0str\0next"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GameScene[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   79,    2, 0x06 /* Public */,
       3,    0,   80,    2, 0x06 /* Public */,
       4,    0,   81,    2, 0x06 /* Public */,
       5,    0,   82,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   83,    2, 0x0a /* Public */,
       7,    0,   84,    2, 0x0a /* Public */,
       8,    1,   85,    2, 0x0a /* Public */,
      10,    1,   88,    2, 0x0a /* Public */,
      11,    1,   91,    2, 0x0a /* Public */,
      12,    1,   94,    2, 0x0a /* Public */,
      13,    1,   97,    2, 0x0a /* Public */,
      15,    2,  100,    2, 0x0a /* Public */,
      15,    1,  105,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 9,    2,
    QMetaType::Void, 0x80000000 | 9,    2,
    QMetaType::Void, 0x80000000 | 9,    2,
    QMetaType::Void, 0x80000000 | 9,    2,
    QMetaType::Void, 0x80000000 | 14,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,   16,   17,
    QMetaType::Void, QMetaType::QString,   16,

       0        // eod
};

void GameScene::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<GameScene *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->myLossSignal(); break;
        case 1: _t->myWinSignal(); break;
        case 2: _t->restartSignal(); break;
        case 3: _t->exitSignal(); break;
        case 4: _t->redrawRoleSlot(); break;
        case 5: _t->redrawBaseSlot(); break;
        case 6: _t->roleMoveSlot((*reinterpret_cast< Character*(*)>(_a[1]))); break;
        case 7: _t->roleAttackSlot((*reinterpret_cast< Character*(*)>(_a[1]))); break;
        case 8: _t->roleEndSlot((*reinterpret_cast< Character*(*)>(_a[1]))); break;
        case 9: _t->roleDiesSlot((*reinterpret_cast< Character*(*)>(_a[1]))); break;
        case 10: _t->baseDestroyedSlot((*reinterpret_cast< Base*(*)>(_a[1]))); break;
        case 11: _t->showHintSlot((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const bool(*)>(_a[2]))); break;
        case 12: _t->showHintSlot((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 6:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Character* >(); break;
            }
            break;
        case 7:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Character* >(); break;
            }
            break;
        case 8:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Character* >(); break;
            }
            break;
        case 9:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Character* >(); break;
            }
            break;
        case 10:
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
            using _t = void (GameScene::*)() const;
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GameScene::myLossSignal)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (GameScene::*)() const;
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GameScene::myWinSignal)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (GameScene::*)() const;
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GameScene::restartSignal)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (GameScene::*)() const;
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GameScene::exitSignal)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject GameScene::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_GameScene.data,
    qt_meta_data_GameScene,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *GameScene::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GameScene::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_GameScene.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int GameScene::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void GameScene::myLossSignal()const
{
    QMetaObject::activate(const_cast< GameScene *>(this), &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void GameScene::myWinSignal()const
{
    QMetaObject::activate(const_cast< GameScene *>(this), &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void GameScene::restartSignal()const
{
    QMetaObject::activate(const_cast< GameScene *>(this), &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void GameScene::exitSignal()const
{
    QMetaObject::activate(const_cast< GameScene *>(this), &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
