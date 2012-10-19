/****************************************************************************
** Meta object code from reading C++ file 'sendkeys.h'
**
** Created: Mon 8. Oct 21:45:32 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../sendkeys.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sendkeys.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SendKeys[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      15,   10,    9,    9, 0x08,
      46,   10,    9,    9, 0x08,
      81,   76,    9,    9, 0x08,
     111,    9,    9,    9, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_SendKeys[] = {
    "SendKeys\0\0arg1\0on_keyBox_textChanged(QString)\0"
    "on_keyBox_textEdited(QString)\0text\0"
    "on_keyBox_keyCatched(QString)\0"
    "on_pushButton_clicked()\0"
};

void SendKeys::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        SendKeys *_t = static_cast<SendKeys *>(_o);
        switch (_id) {
        case 0: _t->on_keyBox_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->on_keyBox_textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->on_keyBox_keyCatched((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->on_pushButton_clicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData SendKeys::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject SendKeys::staticMetaObject = {
    { &QFrame::staticMetaObject, qt_meta_stringdata_SendKeys,
      qt_meta_data_SendKeys, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SendKeys::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SendKeys::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SendKeys::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SendKeys))
        return static_cast<void*>(const_cast< SendKeys*>(this));
    return QFrame::qt_metacast(_clname);
}

int SendKeys::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
