/****************************************************************************
** Meta object code from reading C++ file 'CWK2Widget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "CWK2Widget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CWK2Widget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CWK2Widget_t {
    QByteArrayData data[10];
    char stringdata[76];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CWK2Widget_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CWK2Widget_t qt_meta_stringdata_CWK2Widget = {
    {
QT_MOC_LITERAL(0, 0, 10),
QT_MOC_LITERAL(1, 11, 11),
QT_MOC_LITERAL(2, 23, 0),
QT_MOC_LITERAL(3, 24, 4),
QT_MOC_LITERAL(4, 29, 1),
QT_MOC_LITERAL(5, 31, 11),
QT_MOC_LITERAL(6, 43, 10),
QT_MOC_LITERAL(7, 54, 1),
QT_MOC_LITERAL(8, 56, 17),
QT_MOC_LITERAL(9, 74, 1)
    },
    "CWK2Widget\0updateAngle\0\0kick\0i\0"
    "changePower\0inputPower\0p\0changeShirtColour\0"
    "x"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CWK2Widget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x0a /* Public */,
       3,    1,   40,    2, 0x0a /* Public */,
       5,    0,   43,    2, 0x0a /* Public */,
       6,    1,   44,    2, 0x0a /* Public */,
       8,    1,   47,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double,    7,
    QMetaType::Void, QMetaType::Int,    9,

       0        // eod
};

void CWK2Widget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CWK2Widget *_t = static_cast<CWK2Widget *>(_o);
        switch (_id) {
        case 0: _t->updateAngle(); break;
        case 1: _t->kick((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->changePower(); break;
        case 3: _t->inputPower((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 4: _t->changeShirtColour((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject CWK2Widget::staticMetaObject = {
    { &QGLWidget::staticMetaObject, qt_meta_stringdata_CWK2Widget.data,
      qt_meta_data_CWK2Widget,  qt_static_metacall, 0, 0}
};


const QMetaObject *CWK2Widget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CWK2Widget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CWK2Widget.stringdata))
        return static_cast<void*>(const_cast< CWK2Widget*>(this));
    return QGLWidget::qt_metacast(_clname);
}

int CWK2Widget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGLWidget::qt_metacall(_c, _id, _a);
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
QT_END_MOC_NAMESPACE
