/****************************************************************************
** Meta object code from reading C++ file 'editdialog.h'
**
** Created: Fri 19. Oct 19:45:24 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../editdialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'editdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_EditDialog[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      20,   12,   11,   11, 0x05,
      35,   11,   11,   11, 0x25,

 // slots: signature, parameters, type, tag, flags
      47,   42,   11,   11, 0x08,
      90,   11,   11,   11, 0x08,
     114,   11,   11,   11, 0x08,
     138,   42,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_EditDialog[] = {
    "EditDialog\0\0gesture\0done(Gesture*)\0"
    "done()\0arg1\0on_actionList_currentIndexChanged(QString)\0"
    "on_buttonBox_rejected()\0on_buttonBox_accepted()\0"
    "on_gesture_currentIndexChanged(QString)\0"
};

void EditDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        EditDialog *_t = static_cast<EditDialog *>(_o);
        switch (_id) {
        case 0: _t->done((*reinterpret_cast< Gesture*(*)>(_a[1]))); break;
        case 1: _t->done(); break;
        case 2: _t->on_actionList_currentIndexChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->on_buttonBox_rejected(); break;
        case 4: _t->on_buttonBox_accepted(); break;
        case 5: _t->on_gesture_currentIndexChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData EditDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject EditDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_EditDialog,
      qt_meta_data_EditDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &EditDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *EditDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *EditDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_EditDialog))
        return static_cast<void*>(const_cast< EditDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int EditDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void EditDialog::done(Gesture * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
