/****************************************************************************
** Meta object code from reading C++ file 'centerframe.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../lab02/centerframe.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'centerframe.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CenterFrame_t {
    QByteArrayData data[19];
    char stringdata0[248];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CenterFrame_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CenterFrame_t qt_meta_stringdata_CenterFrame = {
    {
QT_MOC_LITERAL(0, 0, 11), // "CenterFrame"
QT_MOC_LITERAL(1, 12, 11), // "setPenStyle"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 8), // "penStyle"
QT_MOC_LITERAL(4, 34, 11), // "setPenWidth"
QT_MOC_LITERAL(5, 46, 5), // "width"
QT_MOC_LITERAL(6, 52, 11), // "setPenColor"
QT_MOC_LITERAL(7, 64, 5), // "color"
QT_MOC_LITERAL(8, 70, 10), // "clearPaint"
QT_MOC_LITERAL(9, 81, 10), // "selectFile"
QT_MOC_LITERAL(10, 92, 17), // "on_btnRectClicked"
QT_MOC_LITERAL(11, 110, 20), // "on_btnEllipseClicked"
QT_MOC_LITERAL(12, 131, 17), // "on_btnLineClicked"
QT_MOC_LITERAL(13, 149, 21), // "on_btnTriangleClicked"
QT_MOC_LITERAL(14, 171, 17), // "on_btnTextClicked"
QT_MOC_LITERAL(15, 189, 16), // "on_edtTextEdited"
QT_MOC_LITERAL(16, 206, 4), // "text"
QT_MOC_LITERAL(17, 211, 15), // "on_btnImageShow"
QT_MOC_LITERAL(18, 227, 20) // "on_btnDiamondClicked"

    },
    "CenterFrame\0setPenStyle\0\0penStyle\0"
    "setPenWidth\0width\0setPenColor\0color\0"
    "clearPaint\0selectFile\0on_btnRectClicked\0"
    "on_btnEllipseClicked\0on_btnLineClicked\0"
    "on_btnTriangleClicked\0on_btnTextClicked\0"
    "on_edtTextEdited\0text\0on_btnImageShow\0"
    "on_btnDiamondClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CenterFrame[] = {

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
       1,    1,   84,    2, 0x0a /* Public */,
       4,    1,   87,    2, 0x0a /* Public */,
       4,    0,   90,    2, 0x2a /* Public | MethodCloned */,
       6,    1,   91,    2, 0x0a /* Public */,
       8,    0,   94,    2, 0x0a /* Public */,
       9,    0,   95,    2, 0x0a /* Public */,
      10,    0,   96,    2, 0x09 /* Protected */,
      11,    0,   97,    2, 0x09 /* Protected */,
      12,    0,   98,    2, 0x09 /* Protected */,
      13,    0,   99,    2, 0x09 /* Protected */,
      14,    0,  100,    2, 0x09 /* Protected */,
      15,    1,  101,    2, 0x09 /* Protected */,
      17,    0,  104,    2, 0x09 /* Protected */,
      18,    0,  105,    2, 0x09 /* Protected */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QColor,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void CenterFrame::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CenterFrame *_t = static_cast<CenterFrame *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setPenStyle((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->setPenWidth((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->setPenWidth(); break;
        case 3: _t->setPenColor((*reinterpret_cast< QColor(*)>(_a[1]))); break;
        case 4: _t->clearPaint(); break;
        case 5: _t->selectFile(); break;
        case 6: _t->on_btnRectClicked(); break;
        case 7: _t->on_btnEllipseClicked(); break;
        case 8: _t->on_btnLineClicked(); break;
        case 9: _t->on_btnTriangleClicked(); break;
        case 10: _t->on_btnTextClicked(); break;
        case 11: _t->on_edtTextEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 12: _t->on_btnImageShow(); break;
        case 13: _t->on_btnDiamondClicked(); break;
        default: ;
        }
    }
}

const QMetaObject CenterFrame::staticMetaObject = {
    { &QFrame::staticMetaObject, qt_meta_stringdata_CenterFrame.data,
      qt_meta_data_CenterFrame,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *CenterFrame::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CenterFrame::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CenterFrame.stringdata0))
        return static_cast<void*>(this);
    return QFrame::qt_metacast(_clname);
}

int CenterFrame::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFrame::qt_metacall(_c, _id, _a);
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
