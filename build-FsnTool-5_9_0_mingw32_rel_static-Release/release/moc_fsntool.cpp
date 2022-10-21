/****************************************************************************
** Meta object code from reading C++ file 'fsntool.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../fsntool.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'fsntool.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_FsnTool_t {
    QByteArrayData data[21];
    char stringdata0[359];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FsnTool_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FsnTool_t qt_meta_stringdata_FsnTool = {
    {
QT_MOC_LITERAL(0, 0, 7), // "FsnTool"
QT_MOC_LITERAL(1, 8, 21), // "on_pushButton_clicked"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 36), // "on_listWidget_fsn_currentText..."
QT_MOC_LITERAL(4, 68, 7), // "fsnFile"
QT_MOC_LITERAL(5, 76, 23), // "on_pushButton_2_clicked"
QT_MOC_LITERAL(6, 100, 23), // "on_pushButton_4_clicked"
QT_MOC_LITERAL(7, 124, 23), // "on_pushButton_3_clicked"
QT_MOC_LITERAL(8, 148, 23), // "on_pushButton_5_clicked"
QT_MOC_LITERAL(9, 172, 23), // "on_pushButton_6_clicked"
QT_MOC_LITERAL(10, 196, 18), // "slot_doubleClicked"
QT_MOC_LITERAL(11, 215, 3), // "row"
QT_MOC_LITERAL(12, 219, 6), // "column"
QT_MOC_LITERAL(13, 226, 23), // "on_pushButton_7_clicked"
QT_MOC_LITERAL(14, 250, 23), // "on_pushButton_8_clicked"
QT_MOC_LITERAL(15, 274, 24), // "on_pushButton_10_clicked"
QT_MOC_LITERAL(16, 299, 24), // "on_pushButton_11_clicked"
QT_MOC_LITERAL(17, 324, 6), // "DelDir"
QT_MOC_LITERAL(18, 331, 4), // "path"
QT_MOC_LITERAL(19, 336, 14), // "readFsnVersion"
QT_MOC_LITERAL(20, 351, 7) // "fsnPath"

    },
    "FsnTool\0on_pushButton_clicked\0\0"
    "on_listWidget_fsn_currentTextChanged\0"
    "fsnFile\0on_pushButton_2_clicked\0"
    "on_pushButton_4_clicked\0on_pushButton_3_clicked\0"
    "on_pushButton_5_clicked\0on_pushButton_6_clicked\0"
    "slot_doubleClicked\0row\0column\0"
    "on_pushButton_7_clicked\0on_pushButton_8_clicked\0"
    "on_pushButton_10_clicked\0"
    "on_pushButton_11_clicked\0DelDir\0path\0"
    "readFsnVersion\0fsnPath"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FsnTool[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   84,    2, 0x08 /* Private */,
       3,    1,   85,    2, 0x08 /* Private */,
       5,    0,   88,    2, 0x08 /* Private */,
       6,    0,   89,    2, 0x08 /* Private */,
       7,    0,   90,    2, 0x08 /* Private */,
       8,    0,   91,    2, 0x08 /* Private */,
       9,    0,   92,    2, 0x08 /* Private */,
      10,    2,   93,    2, 0x08 /* Private */,
      13,    0,   98,    2, 0x08 /* Private */,
      14,    0,   99,    2, 0x08 /* Private */,
      15,    0,  100,    2, 0x08 /* Private */,
      16,    0,  101,    2, 0x08 /* Private */,
      17,    1,  102,    2, 0x0a /* Public */,
      19,    1,  105,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   11,   12,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool, QMetaType::QString,   18,
    QMetaType::Void, QMetaType::QString,   20,

       0        // eod
};

void FsnTool::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        FsnTool *_t = static_cast<FsnTool *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_pushButton_clicked(); break;
        case 1: _t->on_listWidget_fsn_currentTextChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->on_pushButton_2_clicked(); break;
        case 3: _t->on_pushButton_4_clicked(); break;
        case 4: _t->on_pushButton_3_clicked(); break;
        case 5: _t->on_pushButton_5_clicked(); break;
        case 6: _t->on_pushButton_6_clicked(); break;
        case 7: _t->slot_doubleClicked((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 8: _t->on_pushButton_7_clicked(); break;
        case 9: _t->on_pushButton_8_clicked(); break;
        case 10: _t->on_pushButton_10_clicked(); break;
        case 11: _t->on_pushButton_11_clicked(); break;
        case 12: { bool _r = _t->DelDir((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 13: _t->readFsnVersion((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject FsnTool::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_FsnTool.data,
      qt_meta_data_FsnTool,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *FsnTool::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FsnTool::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_FsnTool.stringdata0))
        return static_cast<void*>(const_cast< FsnTool*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int FsnTool::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
