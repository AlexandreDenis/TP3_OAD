/****************************************************************************
** Meta object code from reading C++ file 'vue.hpp'
**
** Created: Sun Dec 29 18:54:43 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "vue.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'vue.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Vue[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       5,    4,    4,    4, 0x0a,
      12,    4,    4,    4, 0x0a,
      26,    4,    4,    4, 0x0a,
      40,    4,    4,    4, 0x0a,
      46,    4,    4,    4, 0x0a,
      52,    4,    4,    4, 0x0a,
      67,    4,    4,    4, 0x0a,
      73,    4,    4,    4, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Vue[] = {
    "Vue\0\0init()\0afficherClt()\0afficherTrn()\0"
    "sav()\0ins()\0deux_opt_vue()\0sht()\0"
    "multi()\0"
};

const QMetaObject Vue::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Vue,
      qt_meta_data_Vue, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Vue::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Vue::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Vue::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Vue))
        return static_cast<void*>(const_cast< Vue*>(this));
    return QWidget::qt_metacast(_clname);
}

int Vue::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: init(); break;
        case 1: afficherClt(); break;
        case 2: afficherTrn(); break;
        case 3: sav(); break;
        case 4: ins(); break;
        case 5: deux_opt_vue(); break;
        case 6: sht(); break;
        case 7: multi(); break;
        default: ;
        }
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
