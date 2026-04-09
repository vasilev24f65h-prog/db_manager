<<<<<<< HEAD
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlError>
#include <QTextEdit>
#include <QTreeWidget>
#include <QAction>
#include <QDockWidget>
#include <QPlainTextEdit>
#include <QSqlTableModel>
#include <QTableView>
#include <QSqlField>
#include <QStandardItemModel>
#include <QSqlRecord>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QTimer>
#include <vector>
#include <sstream>
#include <QSqlQuery>
#include <QSqlDriver>
#include <QSqlIndex>
#include "dialog_auth.h"
#include "highlightdelegate.h"
#include "logicupdate.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE
struct Condition {
    QString column;
    QString op;
    QString value;
};
struct TableTab
{
    QTableView *table;
    QSqlTableModel * model;
    QString table_name;
    QString conn_name;
};
struct QueryTab
{
    QWidget *pageWjd;
    QTableView *table;
    QSqlQueryModel * model;
    QString table_name;
    QString conn_name;
    unsigned int page = 0;
};
enum {
    RoleType = Qt::UserRole,
    RoleConnectionName = Qt::UserRole + 1
};
enum class FillMode {
    FirstFill,   // заполнять сначала
    EndFill,     // заполнять с конца
    Repeat,      // по кругу
    Defoult    // недостающее = первое значение
};
enum ItemType {
    DatabaseItem = 1,
    TablesGroupItem,
    TableItem,
    ViewsGroupItem,
    ViewItem,
    FuncItem,
    ProcItem
};
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    int connect_to_database();
    TableTab* findTab(const QString &tableName, const QString &connName);
    QueryTab* findQueryTab(const QString &tableName, const QString &connName);
    int disconnect_db();
    QString buildSearchCondition(QSqlQueryModel *model, const QString &searchText);
    TableTab *getCurrentTableTab(QWidget *widget);
    QueryTab *getCurrentQueryTab(QWidget *widget);


signals:
    void tableActivated(const QString &table);
    void tableQueryActivated(const QString &table);


public slots:
    void refresh();
    void showMetaData();
    void on_tree_itemActivated(QTreeWidgetItem *item, int column);
    void on_tree_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);

private slots:
    void on_login_connect();
    void tab_close(int index);
    void on_pushButton_addTab_clicked();
    void add_table(const QString &tableName, const QString &connectionName);
    void add_query_table(const QString &tableName, const QString &connectionName);
    void on_delete_clicked();
    void on_update_clicked();
    void on_insert_clicked();
    void on_filter_clicked();
    void onCustomContextMenu(const QPoint &pos);
    void setPage(QueryTab &tab, const QString primarykey);

    void on_pushButton_clear_clicked();

protected:


private:
    Ui::MainWindow *ui;
    QString username, password, namedb;
    QAction *metaDataAction;
    QAction *refreshAction;
    QAction *loginAction;
    QAction *disconnectAction;

    HighlightDelegate *m_highlightDelegate;
    QSqlDatabase currentDatabase() const;
    void setActive(QTreeWidgetItem *);
    QString activeDb;
    QVector<TableTab> tableTabs;
    QVector<QueryTab> queryTabs;
    void dropTable(QTreeWidgetItem *item);
    void renameTable(QTreeWidgetItem *item);
    void showTriggers(QTreeWidgetItem *item);
    void showFunctions(QTreeWidgetItem *item);
    void showTable(QTreeWidgetItem *item);


};
#endif // MAINWINDOW_H
=======
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlError>
#include <QTextEdit>
#include <QTreeWidget>
#include <QAction>
#include <QDockWidget>
#include <QPlainTextEdit>
#include <QSqlTableModel>
#include <QTableView>
#include <QSqlField>
#include <QStandardItemModel>
#include <QSqlRecord>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QTimer>
#include <vector>
#include <sstream>
#include <QSqlQuery>
#include <QSqlDriver>
#include <QSqlIndex>
#include "dialog_auth.h"
#include "highlightdelegate.h"
#include "logicupdate.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE
struct TableTab
{
    QTableView *table;
    QSqlTableModel * model;
    QString table_name;
    QString conn_name;
};
struct QueryTab
{
    QWidget *pageWjd;
    QTableView *table;
    QSqlQueryModel * model;
    QString table_name;
    QString conn_name;
    unsigned int page = 0;
};
enum {
    RoleType = Qt::UserRole,
    RoleConnectionName = Qt::UserRole + 1
};
enum class FillMode {
    FirstFill,   // заполнять сначала
    EndFill,     // заполнять с конца
    Repeat,      // по кругу
    Defoult    // недостающее = первое значение
};
enum ItemType {
    DatabaseItem = 1,
    TablesGroupItem,
    TableItem,
    ViewsGroupItem,
    ViewItem,
    FuncItem,
    ProcItem
};
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    int connect_to_database();
    TableTab* findTab(const QString &tableName, const QString &connName);
    QueryTab* findQueryTab(const QString &tableName, const QString &connName);
    int disconnect_db();
    QString buildSearchCondition(QSqlQueryModel *model, const QString &searchText);
    TableTab *getCurrentTableTab(QWidget *widget);
    QueryTab *getCurrentQueryTab(QWidget *widget);


signals:
    void tableActivated(const QString &table);
    void tableQueryActivated(const QString &table);


public slots:
    void refresh();
    void showMetaData();
    void on_tree_itemActivated(QTreeWidgetItem *item, int column);
    void on_tree_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);

private slots:
    void on_login_connect();
    void tab_close(int index);
    void on_pushButton_addTab_clicked();
    void add_table(const QString &tableName, const QString &connectionName);
    void add_query_table(const QString &tableName, const QString &connectionName);
    void on_delete_clicked();
    void on_update_clicked();
    void on_insert_clicked();
    void on_filter_clicked();
    void onCustomContextMenu(const QPoint &pos);
    void setPage(QueryTab &tab, const QString primarykey);

protected:


private:
    Ui::MainWindow *ui;
    QString username, password, namedb;
    QAction *metaDataAction;
    QAction *refreshAction;
    QAction *loginAction;
    QAction *disconnectAction;

    HighlightDelegate *m_highlightDelegate;
    QSqlDatabase currentDatabase() const;
    void setActive(QTreeWidgetItem *);
    QString activeDb;
    QVector<TableTab> tableTabs;
    QVector<QueryTab> queryTabs;
    void dropTable(QTreeWidgetItem *item);
    void renameTable(QTreeWidgetItem *item);
    void showTriggers(QTreeWidgetItem *item);
    void showFunctions(QTreeWidgetItem *item);
    void showTable(QTreeWidgetItem *item);


};
#endif // MAINWINDOW_H
>>>>>>> origin/main
