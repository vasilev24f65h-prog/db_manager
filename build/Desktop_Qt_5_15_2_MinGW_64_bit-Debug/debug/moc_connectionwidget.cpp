/****************************************************************************
** Meta object code from reading C++ file 'connectionwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../connectionwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'connectionwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ConnectionWidget_t {
    QByteArrayData data[15];
    char stringdata0[183];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ConnectionWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ConnectionWidget_t qt_meta_stringdata_ConnectionWidget = {
    {
QT_MOC_LITERAL(0, 0, 16), // "ConnectionWidget"
QT_MOC_LITERAL(1, 17, 14), // "tableActivated"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 5), // "table"
QT_MOC_LITERAL(4, 39, 17), // "metaDataRequested"
QT_MOC_LITERAL(5, 57, 9), // "tableName"
QT_MOC_LITERAL(6, 67, 7), // "refresh"
QT_MOC_LITERAL(7, 75, 12), // "showMetaData"
QT_MOC_LITERAL(8, 88, 21), // "on_tree_itemActivated"
QT_MOC_LITERAL(9, 110, 16), // "QTreeWidgetItem*"
QT_MOC_LITERAL(10, 127, 4), // "item"
QT_MOC_LITERAL(11, 132, 6), // "column"
QT_MOC_LITERAL(12, 139, 26), // "on_tree_currentItemChanged"
QT_MOC_LITERAL(13, 166, 7), // "current"
QT_MOC_LITERAL(14, 174, 8) // "previous"

    },
    "ConnectionWidget\0tableActivated\0\0table\0"
    "metaDataRequested\0tableName\0refresh\0"
    "showMetaData\0on_tree_itemActivated\0"
    "QTreeWidgetItem*\0item\0column\0"
    "on_tree_currentItemChanged\0current\0"
    "previous"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ConnectionWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,
       4,    1,   47,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   50,    2, 0x0a /* Public */,
       7,    0,   51,    2, 0x0a /* Public */,
       8,    2,   52,    2, 0x0a /* Public */,
      12,    2,   57,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    5,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 9, QMetaType::Int,   10,   11,
    QMetaType::Void, 0x80000000 | 9, 0x80000000 | 9,   13,   14,

       0        // eod
};

void ConnectionWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ConnectionWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->tableActivated((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->metaDataRequested((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->refresh(); break;
        case 3: _t->showMetaData(); break;
        case 4: _t->on_tree_itemActivated((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 5: _t->on_tree_currentItemChanged((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< QTreeWidgetItem*(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ConnectionWidget::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ConnectionWidget::tableActivated)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ConnectionWidget::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ConnectionWidget::metaDataRequested)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ConnectionWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_ConnectionWidget.data,
    qt_meta_data_ConnectionWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ConnectionWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ConnectionWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ConnectionWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int ConnectionWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void ConnectionWidget::tableActivated(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ConnectionWidget::metaDataRequested(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
