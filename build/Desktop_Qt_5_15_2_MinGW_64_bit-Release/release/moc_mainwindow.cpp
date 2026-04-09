/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[24];
    char stringdata0[318];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 14), // "tableActivated"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 5), // "table"
QT_MOC_LITERAL(4, 33, 7), // "refresh"
QT_MOC_LITERAL(5, 41, 12), // "showMetaData"
QT_MOC_LITERAL(6, 54, 21), // "on_tree_itemActivated"
QT_MOC_LITERAL(7, 76, 16), // "QTreeWidgetItem*"
QT_MOC_LITERAL(8, 93, 4), // "item"
QT_MOC_LITERAL(9, 98, 6), // "column"
QT_MOC_LITERAL(10, 105, 26), // "on_tree_currentItemChanged"
QT_MOC_LITERAL(11, 132, 7), // "current"
QT_MOC_LITERAL(12, 140, 8), // "previous"
QT_MOC_LITERAL(13, 149, 16), // "on_login_connect"
QT_MOC_LITERAL(14, 166, 9), // "tab_close"
QT_MOC_LITERAL(15, 176, 5), // "index"
QT_MOC_LITERAL(16, 182, 28), // "on_pushButton_addTab_clicked"
QT_MOC_LITERAL(17, 211, 9), // "add_table"
QT_MOC_LITERAL(18, 221, 9), // "tableName"
QT_MOC_LITERAL(19, 231, 14), // "connectionName"
QT_MOC_LITERAL(20, 246, 17), // "on_delete_clicked"
QT_MOC_LITERAL(21, 264, 17), // "on_update_clicked"
QT_MOC_LITERAL(22, 282, 17), // "on_insert_clicked"
QT_MOC_LITERAL(23, 300, 17) // "on_filter_clicked"

    },
    "MainWindow\0tableActivated\0\0table\0"
    "refresh\0showMetaData\0on_tree_itemActivated\0"
    "QTreeWidgetItem*\0item\0column\0"
    "on_tree_currentItemChanged\0current\0"
    "previous\0on_login_connect\0tab_close\0"
    "index\0on_pushButton_addTab_clicked\0"
    "add_table\0tableName\0connectionName\0"
    "on_delete_clicked\0on_update_clicked\0"
    "on_insert_clicked\0on_filter_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   79,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   82,    2, 0x0a /* Public */,
       5,    0,   83,    2, 0x0a /* Public */,
       6,    2,   84,    2, 0x0a /* Public */,
      10,    2,   89,    2, 0x0a /* Public */,
      13,    0,   94,    2, 0x08 /* Private */,
      14,    1,   95,    2, 0x08 /* Private */,
      16,    0,   98,    2, 0x08 /* Private */,
      17,    2,   99,    2, 0x08 /* Private */,
      20,    0,  104,    2, 0x08 /* Private */,
      21,    0,  105,    2, 0x08 /* Private */,
      22,    0,  106,    2, 0x08 /* Private */,
      23,    0,  107,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7, QMetaType::Int,    8,    9,
    QMetaType::Void, 0x80000000 | 7, 0x80000000 | 7,   11,   12,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   15,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   18,   19,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->tableActivated((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->refresh(); break;
        case 2: _t->showMetaData(); break;
        case 3: _t->on_tree_itemActivated((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: _t->on_tree_currentItemChanged((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< QTreeWidgetItem*(*)>(_a[2]))); break;
        case 5: _t->on_login_connect(); break;
        case 6: _t->tab_close((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->on_pushButton_addTab_clicked(); break;
        case 8: _t->add_table((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 9: _t->on_delete_clicked(); break;
        case 10: _t->on_update_clicked(); break;
        case 11: _t->on_insert_clicked(); break;
        case 12: _t->on_filter_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MainWindow::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::tableActivated)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::tableActivated(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
