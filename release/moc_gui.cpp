/****************************************************************************
** Meta object code from reading C++ file 'gui.h'
**
** Created: Mon 8. Oct 21:45:28 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../gui.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gui.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Gui[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      10,    5,    4,    4, 0x0a,
      37,    4,    4,    4, 0x0a,
      58,    4,    4,    4, 0x08,
      87,   82,    4,    4, 0x08,
     119,    4,    4,    4, 0x08,
     143,    4,    4,    4, 0x08,
     177,  169,    4,    4, 0x08,
     212,  203,    4,    4, 0x08,
     249,  203,    4,    4, 0x08,
     279,  273,    4,    4, 0x08,
     310,  304,    4,    4, 0x08,
     349,    4,    4,    4, 0x08,
     375,    4,    4,    4, 0x08,
     401,  304,    4,    4, 0x08,
     434,    4,    4,    4, 0x08,
     460,    4,    4,    4, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Gui[] = {
    "Gui\0\0item\0groupMoved(QStandardItem*)\0"
    "on_editDialog_done()\0on_buttonBox_accepted()\0"
    "arg1\0on_filePath_textEdited(QString)\0"
    "on_buttonBox_rejected()\0"
    "on_scrollArea_destroyed()\0checked\0"
    "on_checkBox_toggled(bool)\0position\0"
    "on_horizontalSlider_sliderMoved(int)\0"
    "on_cgt_sliderMoved(int)\0value\0"
    "on_cgt_valueChanged(int)\0index\0"
    "on_treeView_doubleClicked(QModelIndex)\0"
    "on_pushButton_6_clicked()\0"
    "on_pushButton_3_clicked()\0"
    "on_treeView_clicked(QModelIndex)\0"
    "on_pushButton_5_clicked()\0"
    "on_pushButton_7_clicked()\0"
};

void Gui::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Gui *_t = static_cast<Gui *>(_o);
        switch (_id) {
        case 0: _t->groupMoved((*reinterpret_cast< QStandardItem*(*)>(_a[1]))); break;
        case 1: _t->on_editDialog_done(); break;
        case 2: _t->on_buttonBox_accepted(); break;
        case 3: _t->on_filePath_textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->on_buttonBox_rejected(); break;
        case 5: _t->on_scrollArea_destroyed(); break;
        case 6: _t->on_checkBox_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->on_horizontalSlider_sliderMoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->on_cgt_sliderMoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->on_cgt_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->on_treeView_doubleClicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 11: _t->on_pushButton_6_clicked(); break;
        case 12: _t->on_pushButton_3_clicked(); break;
        case 13: _t->on_treeView_clicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 14: _t->on_pushButton_5_clicked(); break;
        case 15: _t->on_pushButton_7_clicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Gui::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Gui::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_Gui,
      qt_meta_data_Gui, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Gui::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Gui::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Gui::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Gui))
        return static_cast<void*>(const_cast< Gui*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int Gui::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
