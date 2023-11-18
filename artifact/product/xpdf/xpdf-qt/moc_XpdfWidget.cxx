/****************************************************************************
** Meta object code from reading C++ file 'XpdfWidget.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "XpdfWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'XpdfWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_XpdfWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      15,       // signalCount

 // signals: signature, parameters, type, tag, flags
      20,   12,   11,   11, 0x05,
      36,   12,   11,   11, 0x05,
      55,   11,   11,   11, 0x05,
      65,   11,   11,   11, 0x05,
      78,   76,   11,   11, 0x05,
      99,   76,   11,   11, 0x05,
     124,   76,   11,   11, 0x05,
     151,   76,   11,   11, 0x05,
     175,   76,   11,   11, 0x05,
     219,  200,   11,   11, 0x05,
     250,   11,   11,   11, 0x05,
     272,  263,   11,   11, 0x05,
     288,   11,   11,   11, 0x05,
     326,  298,   11,   11, 0x05,
     351,   11,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
     362,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_XpdfWidget[] = {
    "XpdfWidget\0\0pageNum\0pageChange(int)\0"
    "midPageChange(int)\0preLoad()\0postLoad()\0"
    "e\0keyPress(QKeyEvent*)\0mousePress(QMouseEvent*)\0"
    "mouseRelease(QMouseEvent*)\0"
    "mouseMove(QMouseEvent*)\0"
    "mouseWheel(QWheelEvent*)\0linkType,dest,page\0"
    "linkClick(QString,QString,int)\0"
    "selectDone()\0finished\0paintDone(bool)\0"
    "resized()\0nextPage,firstPage,lastPage\0"
    "printStatus(int,int,int)\0tileDone()\0"
    "tick()\0"
};

void XpdfWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        XpdfWidget *_t = static_cast<XpdfWidget *>(_o);
        switch (_id) {
        case 0: _t->pageChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->midPageChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->preLoad(); break;
        case 3: _t->postLoad(); break;
        case 4: _t->keyPress((*reinterpret_cast< QKeyEvent*(*)>(_a[1]))); break;
        case 5: _t->mousePress((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 6: _t->mouseRelease((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 7: _t->mouseMove((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 8: _t->mouseWheel((*reinterpret_cast< QWheelEvent*(*)>(_a[1]))); break;
        case 9: _t->linkClick((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 10: _t->selectDone(); break;
        case 11: _t->paintDone((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 12: _t->resized(); break;
        case 13: _t->printStatus((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 14: _t->tileDone(); break;
        case 15: _t->tick(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData XpdfWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject XpdfWidget::staticMetaObject = {
    { &QAbstractScrollArea::staticMetaObject, qt_meta_stringdata_XpdfWidget,
      qt_meta_data_XpdfWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &XpdfWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *XpdfWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *XpdfWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_XpdfWidget))
        return static_cast<void*>(const_cast< XpdfWidget*>(this));
    return QAbstractScrollArea::qt_metacast(_clname);
}

int XpdfWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractScrollArea::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    }
    return _id;
}

// SIGNAL 0
void XpdfWidget::pageChange(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void XpdfWidget::midPageChange(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void XpdfWidget::preLoad()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void XpdfWidget::postLoad()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void XpdfWidget::keyPress(QKeyEvent * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void XpdfWidget::mousePress(QMouseEvent * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void XpdfWidget::mouseRelease(QMouseEvent * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void XpdfWidget::mouseMove(QMouseEvent * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void XpdfWidget::mouseWheel(QWheelEvent * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void XpdfWidget::linkClick(const QString & _t1, const QString & _t2, int _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void XpdfWidget::selectDone()
{
    QMetaObject::activate(this, &staticMetaObject, 10, 0);
}

// SIGNAL 11
void XpdfWidget::paintDone(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void XpdfWidget::resized()
{
    QMetaObject::activate(this, &staticMetaObject, 12, 0);
}

// SIGNAL 13
void XpdfWidget::printStatus(int _t1, int _t2, int _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}

// SIGNAL 14
void XpdfWidget::tileDone()
{
    QMetaObject::activate(this, &staticMetaObject, 14, 0);
}
QT_END_MOC_NAMESPACE
