
#include "mainwindow.h"
#include "qlabel.h"
#include "qlineedit.h"
#include "ui_mainwindow.h"
#include <set>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->tabWidget->setTabsClosable(true);

    m_highlightDelegate = new HighlightDelegate(this);
    QDockWidget *dock = new QDockWidget("Errors", this);
    QPlainTextEdit *errorOutput = new QPlainTextEdit();
    errorOutput->setReadOnly(true);
    dock->setWidget(errorOutput);



    addDockWidget(Qt::BottomDockWidgetArea, dock);

    dock->setMinimumHeight(100);


    ui->treeWidget->setObjectName(QLatin1String("tree"));
    ui->treeWidget->setHeaderLabels(QStringList(tr("database")));
    ui->treeWidget->header()->setSectionResizeMode(QHeaderView::Stretch);
    refreshAction = new QAction(tr("Refresh"), ui->treeWidget);
    metaDataAction = new QAction(tr("Show Schema"), ui->treeWidget);
    loginAction = new QAction(tr("Connect database"), ui->treeWidget);
    disconnectAction = new QAction(tr("Disconnect database"), ui->treeWidget);
    connect(disconnectAction,&QAction::triggered, this, &MainWindow::disconnect_db);
    connect(refreshAction, &QAction::triggered, this, &MainWindow::refresh);
    connect(metaDataAction, &QAction::triggered, this, &MainWindow::showMetaData);
    connect(loginAction, &QAction::triggered, this, &MainWindow::on_login_connect);
    ui->treeWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->treeWidget, &QTreeWidget::customContextMenuRequested,
            this, &MainWindow::onCustomContextMenu);
    connect(this, &MainWindow::tableQueryActivated,
            this, [this](const QString &tableName){
                add_query_table(tableName, activeDb);
            });

    connect(ui->pushButton_deleteRow, &QPushButton::clicked,this,&MainWindow::on_delete_clicked);
    connect(ui->tabWidget, &QTabWidget::tabCloseRequested, this, &MainWindow::tab_close);
    connect(ui->pushButton_login, &QPushButton::clicked,this,&MainWindow::on_login_connect);
    connect(ui->treeWidget, &QTreeWidget::itemDoubleClicked,this, &MainWindow::on_tree_itemActivated);
    connect(ui->pushButton_updateRow,&QPushButton::clicked,this,&MainWindow::on_update_clicked);
    connect(ui->pushButton_insertRow,&QPushButton::clicked,this,&MainWindow::on_insert_clicked );
    connect(ui->pushButton_sendAction,&QPushButton::clicked,this,&MainWindow::on_filter_clicked );
    QTimer::singleShot(0, this, &MainWindow::on_login_connect);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onCustomContextMenu(const QPoint &pos)
{
    QTreeWidgetItem *item = ui->treeWidget->itemAt(pos);


    ui->treeWidget->setCurrentItem(item);

    QMenu menu(this);
    if (!item)
    {
        menu.addAction(loginAction);
        menu.exec(ui->treeWidget->viewport()->mapToGlobal(pos));
        return;
    }
    int type = item->data(0, Qt::UserRole).toInt();

    switch (type)
    {
    case DatabaseItem:
        menu.addAction(loginAction);
        menu.addAction(disconnectAction);
        break;

    case TableItem:
    {
        menu.addAction(refreshAction);
        menu.addAction(metaDataAction);

        menu.addSeparator();

        QAction *dropAction = menu.addAction("Drop table");
        connect(dropAction, &QAction::triggered, this, [this, item]() {
            dropTable(item);
        });
        break;
    }
    default:
        menu.addAction(refreshAction);
        break;
    }

    menu.exec(ui->treeWidget->viewport()->mapToGlobal(pos));
}

void MainWindow::add_query_table(const QString &tableName, const QString &connectionName)
{
    if (QueryTab* existingTab = findQueryTab(tableName, connectionName)) {
        int index = ui->tabWidget->indexOf(existingTab->pageWjd);
        if (index != -1)
            ui->tabWidget->setCurrentIndex(index);
        return;
    }

    QWidget *pageWidget = new QWidget();           // Вкладка
    QVBoxLayout *vLayout = new QVBoxLayout(pageWidget);

    QTableView *table = new QTableView(pageWidget);  // Родитель: pageWidget
    vLayout->addWidget(table);

    QPushButton *nextBtn = new QPushButton("Next", pageWidget); // Тоже родитель pageWidget
    QPushButton *prevBtn = new QPushButton("Prev", pageWidget);

    QHBoxLayout *btnLayout = new QHBoxLayout();
    btnLayout->addStretch();
    btnLayout->addWidget(prevBtn);
    btnLayout->addWidget(nextBtn);
    btnLayout->addStretch();

    vLayout->addLayout(btnLayout);

    ui->tabWidget->addTab(pageWidget, tableName);

    QSqlDatabase database = QSqlDatabase::database(connectionName);

    if (!database.isValid()) {
        qDebug() << "База с таким connectionName не существует!";
        return;
    }

    if (!database.isOpen()) {
        qDebug() << "База не открыта, пробуем открыть...";
        if (!database.open()) {
            qDebug() << "Не удалось открыть базу:" << database.lastError().text();
            return;
        }
    }
    QSqlRecord pk = database.primaryIndex(tableName);
    QStringList pkFields;
    for (int i = 0; i < pk.count(); ++i)
        pkFields << pk.fieldName(i);
    QString querystr;
    QString primarykey = pkFields.join(", ");
    QSqlQueryModel *model = new QSqlQueryModel(this);
    if (primarykey.isEmpty()) {
        querystr = QString("SELECT TOP 1000 * FROM %1").arg(tableName);
    } else {
        querystr = QString("SELECT * FROM %1 ORDER BY %2 OFFSET 0 ROWS FETCH NEXT 1000 ROWS ONLY").arg(tableName, primarykey);
    }


    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    model->setQuery(querystr, database);
    if (model->lastError().isValid())
    {
        qDebug() << "Query failed:" << model->lastError().text();
        model->clear();
        return;
    }
    table->setModel(model);
    queryTabs.append({pageWidget,table,model,tableName,connectionName});

    ui->tabWidget->
    connect(nextBtn, &QPushButton::clicked, this, [this, tableName, connectionName, primarykey]() {
        QueryTab *tab = findQueryTab(tableName, connectionName);
        tab->page++;
        setPage(*tab, primarykey);
    });

    connect(prevBtn, &QPushButton::clicked, this, [this, tableName, connectionName, primarykey]() {
        QueryTab *tab = findQueryTab(tableName, connectionName);
        if (tab->page > 0)
            tab->page--;
        setPage(*tab, primarykey);
    });
    int index = ui->tabWidget->addTab(pageWidget, tableName);
    ui->tabWidget->setCurrentIndex(index);

 }
void MainWindow::setPage(QueryTab &tab, const QString primarykey)
{
    QSqlDatabase database = QSqlDatabase::database(tab.conn_name);
    QString querystr;
    if (primarykey.isEmpty()) {
        querystr = QString("SELECT TOP 1000 * FROM %1").arg(tab.table_name);
    } else {
        querystr = QString("SELECT * FROM %1 ORDER BY %2 OFFSET %3 ROWS FETCH NEXT 1000 ROWS ONLY").arg(tab.table_name, primarykey).arg(tab.page * 1000);
    }
    tab.table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tab.model->setQuery(querystr, database);
    if (tab.model->lastError().isValid())
        qDebug() << "Query failed:" << tab.model->lastError().text();
    tab.table->setModel(tab.model);
}
void MainWindow::dropTable(QTreeWidgetItem *item)
{

}
void MainWindow::renameTable(QTreeWidgetItem *item)
{

}
void MainWindow::showTriggers(QTreeWidgetItem *item)
{

}
void MainWindow::showFunctions(QTreeWidgetItem *item)
{

}

void MainWindow::on_login_connect()
{
    Dialog_auth *dlg = new Dialog_auth(this);
    dlg->setWindowModality(Qt::WindowModal);
    dlg->setWindowFlag(Qt::WindowStaysOnTopHint);

    connect(dlg, &Dialog_auth::credentialsEntered, this, [=](const QString &u, const QString &p,const QString &db ){
        username = u;
        password = p;
        namedb = db;
        qDebug() << "User:" << username << "Password:" << password << "Database" << namedb;
        int res = connect_to_database();
        qDebug() << "res connecting db " << res;
    });
    dlg->setAttribute(Qt::WA_DeleteOnClose);
    dlg->exec();

}

int MainWindow::connect_to_database()
{
    static int counter_conn = 0;
    ++counter_conn;
    QString conn_name = QString("Connection_%1").arg(counter_conn);
    QString connection = QString("Driver={ODBC Driver 17 for SQL Server};Server=127.0.0.1;Database=%1;UID=%2;PWD=%3;")
        .arg(namedb,username,password);

    qDebug() << QSqlDatabase::drivers();
    QSqlDatabase db =  QSqlDatabase::addDatabase("QODBC3", conn_name);
    qDebug() << conn_name;
    db.setDatabaseName(connection);
    if(db.open())
    {
        refresh();
        return 0;
    }
    else
    {
        qDebug() << "Connection failed:" << db.lastError().text();
        return 1;
    }

}

int MainWindow::disconnect_db()
{
    QTreeWidgetItem *item = ui->treeWidget->currentItem();
    if (!item)
        return -1;

    QTreeWidgetItem *root = item;
    while (root->parent())
        root = root->parent();

    QString connectionName = root->data(0, RoleConnectionName).toString();
    if (connectionName.isEmpty())
        return -1;

    for (int i = queryTabs.count() - 1; i >= 0; --i) {
        if (queryTabs[i].conn_name == connectionName) {
            ui->tabWidget->removeTab(ui->tabWidget->indexOf(queryTabs[i].pageWjd));
            queryTabs[i].table->setModel(nullptr);
            delete queryTabs[i].model;
            delete queryTabs[i].table;
            delete queryTabs[i].pageWjd;
            queryTabs.removeAt(i);
        }
    }

    {
        QSqlDatabase db = QSqlDatabase::database(connectionName);
        db.close();
    }

    QSqlDatabase::removeDatabase(connectionName);

    refresh();
    return 1;
}
void MainWindow::tab_close(int index)
{
    if (QMessageBox::question(this, "Закрыть",
                              "Закрыть вкладку?") == QMessageBox::Yes)
    {
        QWidget *widget = ui->tabWidget->widget(index);
        auto it2 = std::remove_if(queryTabs.begin(), queryTabs.end(),
                                 [widget](const QueryTab &tab){ return tab.pageWjd == widget; });
        if (it2 != queryTabs.end()) {
            queryTabs.erase(it2, queryTabs.end());
        }
        ui->tabWidget->removeTab(index);
        delete widget;
    }

}

void MainWindow::on_pushButton_addTab_clicked()
{
    ui->tabWidget->addTab(new QTextEdit(), "Текст");
}

QueryTab* MainWindow::findQueryTab(const QString &tableName, const QString &connName)
{
    for (auto &tab : queryTabs) {
        if (tab.table_name == tableName && tab.conn_name == connName) {
            return &tab;
        }
    }
    return nullptr;
}

static QString qDBCaption(const QSqlDatabase &db)
{
    QString nm = db.driverName();
    nm.append(QLatin1Char(':'));
    if (!db.userName().isEmpty())
        nm.append(db.userName()).append(QLatin1Char('@'));
    nm.append(db.databaseName());
    return nm;
}

void MainWindow::refresh()
{
    ui->treeWidget->clear();
    QStringList connectionNames = QSqlDatabase::connectionNames();

    bool gotActiveDb = false;
    for (int i = 0; i < connectionNames.count(); ++i) {
        QTreeWidgetItem *root = new QTreeWidgetItem(ui->treeWidget);
        QString connName = connectionNames.at(i);
        QTreeWidgetItem *dbNode = new QTreeWidgetItem(root);
        dbNode->setText(0, "Database");
        dbNode->setData(0, RoleType, DatabaseItem);
        QSqlDatabase db = QSqlDatabase::database(connName, false);
        root->setText(0, qDBCaption(db));
        root->setData(0, RoleConnectionName, connName);
        if (connectionNames.at(i) == activeDb) {
            gotActiveDb = true;
            setActive(root);
        }
        if (db.isOpen()) {
            QTreeWidgetItem *tablesNode = new QTreeWidgetItem(dbNode);
            tablesNode->setText(0, "Tables");
            tablesNode->setData(0, RoleType, TablesGroupItem);

            QTreeWidgetItem *viewsNode = new QTreeWidgetItem(dbNode);
            viewsNode->setText(0, "Views");
            viewsNode->setData(0, RoleType, ViewItem);

            QTreeWidgetItem *tableRootNode;
            QTreeWidgetItem *procNode = new QTreeWidgetItem(dbNode);
            procNode->setText(0, "Procedures");
            procNode->setData(0, RoleType, ProcItem);
            QTreeWidgetItem *indexNode;
            QTreeWidgetItem *funcNode = new QTreeWidgetItem(dbNode);
            funcNode->setText(0, "Function");
            funcNode->setData(0, RoleType, FuncItem);
            QTreeWidgetItem *primaryKeyNode;
            QTreeWidgetItem *foreignKeyNode;
            QTreeWidgetItem *triggersNode;
            QStringList tables;

            QString sql = "SELECT name FROM sys.tables WHERE is_ms_shipped = 0;";
            QSqlQuery query(db);
            if (!query.exec(sql)) {
                qDebug() << "Tables query failed:" << query.lastError().text();
            }
            while (query.next())
            {
                tables.append(query.value(0).toString());
            }
            for (const QString &tableName : std::as_const(tables)) {
                tableRootNode = new QTreeWidgetItem(tablesNode);
                QTreeWidgetItem *table = new QTreeWidgetItem(tableRootNode);
                tableRootNode->setText(0, tableName);
                tableRootNode->setData(0, RoleType, TablesGroupItem);
                table->setText(0, tableName);
                table->setData(0, RoleType, TableItem);

                indexNode = new QTreeWidgetItem(tableRootNode);
                indexNode->setText(0, "Indexces");
                indexNode->setData(0, RoleType, TablesGroupItem);

                primaryKeyNode = new QTreeWidgetItem(tableRootNode);
                primaryKeyNode->setText(0, "Primary key");
                primaryKeyNode->setData(0, RoleType, TablesGroupItem);

                foreignKeyNode = new QTreeWidgetItem(tableRootNode);
                foreignKeyNode->setText(0, "Foreign key");
                foreignKeyNode->setData(0, RoleType, TablesGroupItem);

                triggersNode = new QTreeWidgetItem(tableRootNode);
                triggersNode->setText(0, "Triggers");
                triggersNode->setData(0, RoleType, TablesGroupItem);

                sql = QString("SELECT name FROM sys.indexes WHERE object_id = OBJECT_ID('%1')").arg(tableName);
                if (!query.exec(sql)) {
                    qDebug() << "Indexes query failed:" << query.lastError().text();
                }
                while (query.next())
                {
                    QTreeWidgetItem *index = new QTreeWidgetItem(indexNode);
                    index->setText(0, query.value(0).toString());
                    index->setData(0, RoleType, TableItem);
                }
                QSqlIndex pk = db.primaryIndex(tableName);
                if(!pk.name().isEmpty())
                {
                    QTreeWidgetItem *primarykey = new QTreeWidgetItem(primaryKeyNode);
                    primarykey->setText(0,pk.name());
                    primarykey->setData(0, RoleType, TableItem);
                }

                sql = QString("SELECT name FROM sys.triggers WHERE parent_id = OBJECT_ID('%1')").arg(tableName);
                if (!query.exec(sql)) {
                    qDebug() << "Triggers query failed:" << query.lastError().text();
                    //return;
                }
                while (query.next())
                {
                    QTreeWidgetItem *triggers = new QTreeWidgetItem(triggersNode);
                    triggers->setText(0, query.value(0).toString());
                    triggers->setData(0, RoleType, TableItem);
                }

                sql = QString("SELECT * FROM sys.foreign_keys WHERE parent_object_id = OBJECT_ID('%1')").arg(tableName);
                if (!query.exec(sql)) {
                    qDebug() << "Foreign key query failed:" << query.lastError().text();
                    //return;
                }
                while (query.next())
                {
                    QTreeWidgetItem *foreignkey = new QTreeWidgetItem(foreignKeyNode);
                    foreignkey->setText(0, query.value(0).toString());
                    foreignkey->setData(0, RoleType, TableItem);
                }

            }

            sql = "SELECT name FROM sys.procedures";

            if (!query.exec(sql)) {
                qDebug() << "Procedures query failed:" << query.lastError().text();
                return;
            }

            while (query.next())
            {
                QTreeWidgetItem *proc = new QTreeWidgetItem(procNode);
                proc->setText(0, query.value(0).toString());
                proc->setData(0, RoleType, ProcItem);
            }
            sql = "SELECT name FROM sys.objects WHERE type IN ('FN', 'TF', 'IF')";

            if (!query.exec(sql)) {
                qDebug() << "Functions query failed:" << query.lastError().text();
                //return;
            }

            while (query.next())
            {
                QTreeWidgetItem *func = new QTreeWidgetItem(funcNode);
                func->setText(0, query.value(0).toString());
                func->setData(0, RoleType, FuncItem);
            }

            QStringList views;
            sql = "SELECT name FROM sys.views WHERE is_ms_shipped = 0;";
            if (!query.exec(sql)) {
                qDebug() << "Views query failed:" << query.lastError().text();
            }
            while (query.next())
            {
                views.append(query.value(0).toString());
            }
            for (const QString &viewsName : std::as_const(views)) {
                QTreeWidgetItem *views = new QTreeWidgetItem(viewsNode);
                views->setText(0, viewsName);
                views->setData(0, RoleType, ViewItem);
            }
        }
    }
    if (!gotActiveDb) {
        activeDb = connectionNames.value(0);
        setActive(ui->treeWidget->topLevelItem(0));
    }

    ui->treeWidget->doItemsLayout(); // HACK
}

QSqlDatabase MainWindow::currentDatabase() const
{
    return QSqlDatabase::database(activeDb);
}

static void qSetBold(QTreeWidgetItem *item, bool bold)
{
    QFont font = item->font(0);
    font.setBold(bold);
    item->setFont(0, font);
}

void MainWindow::setActive(QTreeWidgetItem *item)
{
    for (int i = 0; i < ui->treeWidget->topLevelItemCount(); ++i) {
        if (ui->treeWidget->topLevelItem(i)->font(0).bold())
            qSetBold(ui->treeWidget->topLevelItem(i), false);
    }

    if (!item)
        return;

    qSetBold(item, true);
    activeDb = item->data(0, RoleConnectionName).toString();
}

void MainWindow::on_tree_itemActivated(QTreeWidgetItem *item, int /* column */)
{
    if (!item)
        return;

    QTreeWidgetItem *root = item;
    while (root->parent())
        root = root->parent();

    setActive(root);

    if (item->data(0, RoleType).toInt() == TableItem) {
        emit tableQueryActivated(item->text(0));
    }
    if (item->data(0, RoleType).toInt() == ViewItem) {
        emit tableQueryActivated(item->text(0));
    }
}



void MainWindow::on_tree_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *)
{
    metaDataAction->setEnabled(current && current->parent());
}


void MainWindow::showMetaData()
{
    QTreeWidgetItem *item = ui->treeWidget->currentItem();
    if (!item) return;
    if (item->data(0, RoleType).toInt() != TableItem)
        return;

    QTreeWidgetItem *root = item;
    while (root->parent())
        root = root->parent();

    setActive(root);

    if (item->data(0, RoleType).toInt() != TableItem)
        return;

    QString t = item->text(0);

    QSqlDatabase database = currentDatabase();

    QSqlQuery query(database);

    QString sql = QString(R"(
        SELECT
            c.COLUMN_NAME,
            c.DATA_TYPE,
            c.CHARACTER_MAXIMUM_LENGTH,
            c.NUMERIC_PRECISION,
            c.NUMERIC_SCALE,
            c.IS_NULLABLE,
            c.COLUMN_DEFAULT,
            COLUMNPROPERTY(object_id(c.TABLE_NAME), c.COLUMN_NAME, 'IsIdentity') AS IS_IDENTITY
        FROM INFORMATION_SCHEMA.COLUMNS c
        WHERE c.TABLE_NAME = '%1'
        ORDER BY c.ORDINAL_POSITION
    )").arg(t);

    if (!query.exec(sql)) {
        qDebug() << "Metadata query failed:" << query.lastError().text();
        return;
    }

    QTableView *view = new QTableView();
    QStandardItemModel *model = new QStandardItemModel(view);

    model->setColumnCount(8);

    model->setHeaderData(0, Qt::Horizontal, "Fieldname");
    model->setHeaderData(1, Qt::Horizontal, "Type");
    model->setHeaderData(2, Qt::Horizontal, "Length");
    model->setHeaderData(3, Qt::Horizontal, "Precision");
    model->setHeaderData(4, Qt::Horizontal, "Scale");
    model->setHeaderData(5, Qt::Horizontal, "Nullable");
    model->setHeaderData(6, Qt::Horizontal, "Default");
    model->setHeaderData(7, Qt::Horizontal, "Identity");

    int row = 0;
    while (query.next()) {
        model->insertRow(row);

        model->setData(model->index(row, 0), query.value(0)); // COLUMN_NAME
        model->setData(model->index(row, 1), query.value(1)); // DATA_TYPE
        model->setData(model->index(row, 2), query.value(2)); // LENGTH
        model->setData(model->index(row, 3), query.value(3)); // PRECISION
        model->setData(model->index(row, 4), query.value(4)); // SCALE
        model->setData(model->index(row, 5), query.value(5)); // NULLABLE
        model->setData(model->index(row, 6), query.value(6)); // DEFAULT
        model->setData(model->index(row, 7), query.value(7)); // IDENTITY

        row++;
    }

    view->setModel(model);
    view->setEditTriggers(QAbstractItemView::NoEditTriggers);
    for (int i = 0; i < ui->tabWidget->count(); ++i)
    {
        if (ui->tabWidget->tabText(i) == t + " (schema)")
        {
            ui->tabWidget->setCurrentIndex(i);
            return;
        }
    }
    ui->tabWidget->addTab(view, t + " (schema)");
}


QueryTab * MainWindow::getCurrentQueryTab(QWidget *widget)
{
    for(auto &t : queryTabs)
    {
        if(t.pageWjd==widget)
        {
            return &t;
        }
    }
    return nullptr;
}
void MainWindow::on_delete_clicked()
{

    if (QMessageBox::question(this, "Удалить",
                              "Удалить запись(и)?") == QMessageBox::Yes)
    {
        QTableView *currentView = nullptr;
        QSqlQueryModel *queryModel = nullptr;
        int currentIndex = ui->tabWidget->currentIndex();
        QWidget *widget = ui->tabWidget->widget(currentIndex);

        QueryTab *tab =getCurrentQueryTab(widget);

        if(!tab)
        {
            QMessageBox::warning(this, "Ошибка", "Отсутсвует табличное представление.");
            return;
        }
        currentView =tab->table;
        queryModel = tab->model;
        QModelIndexList selectedIndexes = currentView->selectionModel()->selectedIndexes();

        if (selectedIndexes.isEmpty())
        {
            QMessageBox::warning(this, "Ошибка", "Нет выбранных строк.");
            return;
        }

        // уникальные строки
        QSet<int> rowsSet;
        for (const QModelIndex &idx : std::as_const(selectedIndexes))
            rowsSet.insert(idx.row());

        QSqlDatabase db = currentDatabase();
        QSqlRecord pk = db.primaryIndex(tab->table_name);
        if(pk.count()==0)
        {
            QMessageBox::warning(this, "Внимание", "Вы работаете с представлением или таблицой без первичного ключа. "
                                                   "Корректность операции не гарантируется.");
        }
        QStringList rowConditions;
        QList<QVariant> bindValues;

        for (int row : rowsSet)
        {
            QStringList oneRow;
            if(pk.count()!=0)
            {
                for (int i = 0; i < pk.count(); ++i)
                {
                    QString field = pk.fieldName(i);
                    int col = queryModel->record().indexOf(field);
                    QVariant value = queryModel->data(queryModel->index(row, col));

                    oneRow << QString("%1 = ?").arg(field);
                    bindValues << value;
                }

                rowConditions << "(" + oneRow.join(" AND ") + ")";
            }
            else {
                QSqlRecord rec = queryModel->record();

                for (int col = 0; col < rec.count(); ++col)
                {
                    QString field = rec.fieldName(col);
                    QVariant value = queryModel->data(queryModel->index(row, col));

                    if (value.isNull()) {
                        oneRow << QString("%1 IS NULL").arg(field);
                    } else {
                        oneRow << QString("%1 = ?").arg(field);
                        bindValues << value;
                    }
                }
                rowConditions << "(" + oneRow.join(" AND ") + ")";
            }

        }

        QString sql = QString("DELETE FROM %1 WHERE %2")
                          .arg(tab->table_name, rowConditions.join(" OR "));

        QSqlQuery query(db);
        query.prepare(sql);

        for (const QVariant &val : std::as_const(bindValues))
            query.addBindValue(val);

        db.transaction();

        if (!query.exec()) {
            db.rollback();
            QMessageBox::warning(this, "Ошибка", query.lastError().text());
            return;
        }

        db.commit();

        queryModel->setQuery(queryModel->query().lastQuery(), db);
        QMessageBox::information(this, "Удаление", "Строки удалены.");
    }


}

void MainWindow::on_update_clicked()
{
    QDialog dlg(this);

    QVBoxLayout *layout = new QVBoxLayout(&dlg);
    QString upd_data;
    QLineEdit *line = new QLineEdit(&dlg);
    layout->addWidget(line);
    QDialogButtonBox * btn = new QDialogButtonBox(Qt::Horizontal, &dlg);
    btn->addButton("OK", QDialogButtonBox::AcceptRole);
    btn->addButton("Cancel", QDialogButtonBox::RejectRole);
    layout->addWidget(btn);
    connect(btn,&QDialogButtonBox::accepted,&dlg,&QDialog::accept);
    connect(btn,&QDialogButtonBox::rejected,&dlg,&QDialog::reject);
    if (dlg.exec() == QDialog::Accepted) {
        upd_data = line->text();
    }
    else
        return;

    UpdateRequeted req;
    UpdateParse parser;
    req = parser.parseCommand(upd_data);

    QTableView *currentView = nullptr;
    QSqlQueryModel *currentModel = nullptr;
    QString currentTableName;
    QString currentConnName;

    int currentIndex = ui->tabWidget->currentIndex();
    QWidget *widget = ui->tabWidget->widget(currentIndex);

    QueryTab *tab =getCurrentQueryTab(widget);

    if(!tab)
    {
        QMessageBox::warning(this, "Ошибка", "Отсутсвует табличное представление.");
        return;
    }
    currentView =tab->table;
    currentModel = tab->model;
    currentTableName = tab->table_name;
    currentConnName = tab->conn_name;

    if (!currentView || !currentModel) {
        QMessageBox::warning(this, "Ошибка", "Отсутствует таблица или модель.");
        return;
    }

    currentView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    currentView->setSelectionBehavior(QAbstractItemView::SelectItems);

    QSqlDatabase db = QSqlDatabase::database(currentConnName);
    QSqlRecord pk = db.primaryIndex(tab->table_name);
    QSqlTableModel* tableModel = new QSqlTableModel(this, db);
    tableModel->setTable(currentTableName);
    tableModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    tableModel->select();
// Привязываем таблицу к view

    QModelIndexList indexes = currentView->selectionModel()->selectedIndexes();
    std::set<int> columns;
    QList<int> rows;

    if(pk.count()==0)
    {
        QMessageBox::warning(this, "Внимание", "Вы работаете с представлением или таблицой без первичного ключа. "
                                               "Корректность операции не гарантируется.");
    }
    if (indexes.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Нет выбранных ячеек.");
        return;
    }
    parser.setupRowCol(indexes,columns,rows);

    if(columns.size() != 1 && ((rows.size() % static_cast<int>(columns.size())) != 0 ) )
    {
        QMessageBox::warning(this, "Ошибка", "Разное число ячеек в строках");
        return;
    }
    parser.parseData(upd_data, columns, req);

    if (req.multi_value.size() < static_cast<int>(columns.size())) {
        QMessageBox::warning(this, "Ошибка", "Недостаточно значений для обновления.");
        return;
    }
    if(req.command == "def" && (req.multi_value.size() < static_cast<int>(rows.size())))
    {
        QMessageBox::warning(this, "Ошибка", "Недостаточно значений для обновления.");
        return;
    }
    if(req.command == "def" && (req.multi_value.size() > static_cast<int>(rows.size())))
    {
        QMessageBox::warning(this, "Ошибка", "Слишком много значений для обновления.");
        return;
    }


    QString error;
    if (UpdateExecutor::execute(db, tableModel, indexes, req, error, columns, rows)) {
        tableModel->submitAll(); // применяем изменения
        tableModel->select();    // обновляем view
        currentModel->setQuery(currentModel->query().lastQuery(), db);
        QMessageBox::information(this, "Success", "All changes saved");
    } else {
        QMessageBox::critical(this, "Error!", error);
        tableModel->revertAll(); // откатываем изменения при ошибке
        tableModel->select();
        currentModel->setQuery(currentModel->query().lastQuery(), db);
    }

}
//формировать sql запрос на вставку вручную, потом отсанется только поиск и фильтры переделать и в приципе все тогда будет готово
// потом останется ввод и вывод информации в виде форм сделать и удалить код связанный с tablemodel.
// далее надо будет сосредоточиться на админском функционале
void MainWindow::on_insert_clicked()
{
    QDialog dlg(this);

    QFormLayout *form = new QFormLayout(&dlg);

    QDialogButtonBox * btn = new QDialogButtonBox(Qt::Horizontal, &dlg);
    btn->addButton("OK", QDialogButtonBox::AcceptRole);
    btn->addButton("Cancel", QDialogButtonBox::RejectRole);
    connect(btn,&QDialogButtonBox::accepted,&dlg,&QDialog::accept);
    connect(btn,&QDialogButtonBox::rejected,&dlg,&QDialog::reject);
    form->addWidget(btn);
    QTableView *currentView = nullptr;
    QSqlQueryModel *currentModel = nullptr;
    QString currentTableName;
    QString currentConnName;
    QVector<QWidget*> editors;
    QStringList fieldNames;
    QStringList placeholders;
    int currentIndex = ui->tabWidget->currentIndex();
    QWidget *widget = ui->tabWidget->widget(currentIndex);

    QueryTab *tab =getCurrentQueryTab(widget);

    if(!tab)
    {
        QMessageBox::warning(this, "Ошибка", "Отсутсвует табличное представление.");
        return;
    }
    currentView =tab->table;
    currentModel = tab->model;
    currentTableName = tab->table_name;
    currentConnName = tab->conn_name;

    if (!currentView || !currentModel) {
        QMessageBox::warning(this, "Ошибка", "Отсутствует таблица или модель.");
        return;
    }

    currentView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    currentView->setSelectionBehavior(QAbstractItemView::SelectItems);

    QSqlRecord record = currentModel->record();

    QVector<int> fieldIndexes;

    for (int i = 0; i < record.count(); ++i)
    {
        QSqlField field = record.field(i);

        // пропускаем автоинкремент
        if (field.isAutoValue())
            continue;

        QString fieldName = field.name();
        fieldNames.append(fieldName);
        QLabel *label = new QLabel(fieldName, &dlg);
        QLineEdit *edit = new QLineEdit(&dlg);
        placeholders << QString(":v%1").arg(i);
        form->addRow(label, edit);

        editors.push_back(edit);
        fieldIndexes.push_back(i); // запоминаем реальный индекс поля
    }
    if (dlg.exec() == QDialog::Accepted)
    {   QSqlDatabase db = currentDatabase();
        QSqlRecord pk = db.primaryIndex(tab->table_name);
        if(pk.count()==0)
        {
            QMessageBox::warning(this, "Внимание", "Вы работаете с представлением или таблицой без первичного ключа. "
                                                   "Корректность операции не гарантируется.");
        }
        QString query = QString("INSERT INTO %1 (%2) VALUES (%3)").arg(currentTableName, fieldNames.join(" , "), placeholders.join(", "));
        QSqlQuery insert(query,db);
        insert.prepare(query);
        for (int i = 0; i < editors.size(); ++i)
        {

            QLineEdit *edit = qobject_cast<QLineEdit*>(editors[i]);
            if (edit->text().isEmpty())
                insert.bindValue(QString(":v%1").arg(i), QVariant());
            else
                insert.bindValue(QString(":v%1").arg(i), edit->text());
        }
        db.transaction();
        if(insert.exec())
        {
            db.commit();
            currentModel->setQuery(currentModel->query().lastQuery(), db);
            QMessageBox::information(this, "Success", "All changes saved");
        }
        else {
            db.rollback();
            QMessageBox::critical(this, "Error!", insert.lastError().text());

            currentModel->setQuery(currentModel->query().lastQuery(), db);
        }

    }
}

QString MainWindow::buildSearchCondition(QSqlQueryModel *model, QString &searchText, QList<Placeholders> &placeholders)
{
    QStringList conditions;
    QSqlRecord record = model->record();
    int index  = 0;
    static bool ok;
    ok = searchText.toInt();
    searchText.replace("'", "''");
    searchText.replace("%", "\\%");
    searchText.replace("_", "\\_");

    for (int i = 0; i < record.count(); ++i) {
        QString fieldName = record.fieldName(i);
        QSqlField field = record.field(i);
        QVariant::Type fieldType = field.type();

        if (fieldType == QVariant::ByteArray || field.isAutoValue())
            continue;

        QString placeholder = QString(":val%1").arg(index++);


        if (fieldType == QVariant::String) {
            conditions.append(QString("CONTAINS(%1 , %2) OR %1 LIKE %3 ESCAPE '\\'")
                                  .arg(fieldName, placeholder+"full", placeholder));
            placeholders.append({placeholder, false});
        }
        else if ((fieldType == QVariant::Int || fieldType == QVariant::LongLong || fieldType == QVariant::Double) && ok) {
            conditions.append(QString("%1 = %2 ")
                                  .arg(fieldName, placeholder));
            placeholders.append({placeholder, true});
        }

    }

    if (conditions.isEmpty())
        return "";

    return conditions.join(" OR ");
}

void MainWindow::on_filter_clicked()
{
    QString condition = ui->lineEdit_action->text();
    QString action = ui->comboBox_action->currentText();

    QTableView *currentView = nullptr;
    QSqlQueryModel *currentModel = nullptr;
    QString currentTableName;
    QString currentConnName;

    int currentIndex = ui->tabWidget->currentIndex();
    QWidget *widget = ui->tabWidget->widget(currentIndex);

    QueryTab *tab =getCurrentQueryTab(widget);

    if(!tab)
    {
        QMessageBox::warning(this, "Ошибка", "Отсутсвует табличное представление.");
        return;
    }
    currentView =tab->table;
    currentModel = tab->model;
    currentTableName = tab->table_name;
    currentConnName = tab->conn_name;

    if (!currentView || !currentModel) {
        QMessageBox::warning(this, "Ошибка", "Отсутствует таблица или модель.");
        return;
    }
    QSqlDatabase db = currentDatabase();
    currentView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    currentView->setSelectionBehavior(QAbstractItemView::SelectItems);
    QSqlRecord pk = db.primaryIndex(currentTableName);
    QStringList pkFields;
    for (int i = 0; i < pk.count(); ++i)
        pkFields << pk.fieldName(i);
    QString primarykey = pkFields.join(", ");
    if(action == "Filter")
    {
        if(condition.isEmpty())
        {
            return;
        }
        static const QRegularExpression re(R"(^\s*([\w_]+)\s*(=|!=|<>|>=|<=|>|<|like)\s*(.+)\s*$)",
                              QRegularExpression::CaseInsensitiveOption);
        static const QRegularExpression logicRe(R"(\s+(AND|OR)\s+)", QRegularExpression::CaseInsensitiveOption);
        QStringList parts = condition.split(logicRe, Qt::SkipEmptyParts);
        QRegularExpressionMatchIterator it = logicRe.globalMatch(condition);
        QList<Condition> conditions;
        QString where;
        QRegularExpressionMatch match = re.match(condition.trimmed());
        QStringList logicOps;
        QStringList partsVal;
        QSqlRecord rec = db.record(currentTableName);
        QSet<QString> allowedOps = {"=", "<", ">", "<=", ">=", "LIKE"};
        QSet<QString> allowedColumns;
        for (int i = 0; i < rec.count(); ++i) {
            allowedColumns.insert(rec.fieldName(i));
        }
        while (it.hasNext())
        {
            QRegularExpressionMatch match = it.next();
            logicOps << match.captured(1).toUpper();
        }
        preparedParts(parts,conditions,partsVal,re,allowedOps,allowedColumns, ":val");
        if (!conditions.isEmpty())
        {
            where = partsVal[0];
            for (int i = 1; i < conditions.size(); ++i)
            {
                QString op = logicOps.value(i-1);
                where += " " + op + " " + partsVal[i];
            }
        }
        QString sql = QString("SELECT * FROM %1 WHERE %2").arg(currentTableName, where);
        QSqlQuery query(db);
        query.prepare(sql);
        for (int i = 0; i < conditions.size(); ++i)
        {
            QString val = conditions[i].value;
            if (conditions[i].op == "LIKE")
                val = "%" + val + "%";

            query.bindValue(":val" + QString::number(i), val);
        }

        query.exec();
        m_highlightDelegate->setSearchText("");
        currentModel->setQuery(query);
        currentView->update();
    }
    else if(action == "Search")
    {

        if (condition.isEmpty()) {
            m_highlightDelegate->setSearchText("");
            return;
        } else {
            QList<Placeholders> placeholders;
            QString filterCondition = buildSearchCondition(tab->model, condition, placeholders);
            if (!filterCondition.isEmpty()) {
                QString querystr = QString("SELECT * FROM %1 WHERE %2").arg(currentTableName,filterCondition);
                qDebug() << "Executing SQL:" << querystr;
                QSqlQuery query(db);
                query.prepare(querystr);
                for (const Placeholders &ph : std::as_const(placeholders)) {
                    if(ph.isNumeric)
                    {
                        query.bindValue(ph.ph, condition);
                    }
                    else
                    {
                        query.bindValue(ph.ph+"full","\"" + condition + "*\"");
                        query.bindValue(ph.ph, "%" + condition + "%");
                    }

                }
                if (!query.exec()) {
                    qDebug() << query.lastError();
                }
                qDebug() << query.lastQuery();
                currentModel->setQuery(query);
                m_highlightDelegate->setSearchText(condition);
                currentView->setItemDelegate(m_highlightDelegate);
                currentView->viewport()->update();

                qDebug() << "Search applied:" << filterCondition;
                qDebug() << "Rows found:" << currentModel->rowCount();
            } else {
                QMessageBox::warning(this, "Ошибка", "Нет полей для поиска.");
            }
    }
    }
    else if(action == "Update")
    {
        if(condition.isEmpty())
        {
            return;
        }
        static const QRegularExpression re(R"(^\s*([\w_]+)\s*(=)\s*(.+)\s*$)",
                                           QRegularExpression::CaseInsensitiveOption);
        static const QRegularExpression logicRe("\\s*,\\s*");
        static const QRegularExpression whereRe("\\bWHERE\\b\\s+(.*)", QRegularExpression::CaseInsensitiveOption);
        static const QRegularExpression andRe(R"(\s+(AND)\s+)", QRegularExpression::CaseInsensitiveOption);
        QRegularExpressionMatch matchWhere = whereRe.match(condition.trimmed());
        QStringList full = condition.split(logicRe, Qt::SkipEmptyParts);
        QString whereCond = matchWhere.captured(0);
        QString where = matchWhere.captured(1);
        full.back().remove(whereCond);
        QStringList whereParts = where.split(andRe,Qt::SkipEmptyParts);
        QString value;
        QString whereVal;
        QStringList parts = full;

        whereCond.clear();
        where.clear();
        full.clear();

        QRegularExpressionMatchIterator it = logicRe.globalMatch(condition);
        QList<Condition> conditions;
        QList<Condition> conditionsWhere;
        QStringList partsVal;

        QSqlRecord rec = db.record(currentTableName);
        QSet<QString> allowedOps = {"=", "<", ">", "<=", ">=", "LIKE"};
        QSet<QString> allowedColumns;
        for (int i = 0; i < rec.count(); ++i) {
            allowedColumns.insert(rec.fieldName(i));
        }
        preparedParts(parts,conditions,partsVal,re,allowedOps,allowedColumns, ":val");
        if (!conditions.isEmpty())
        {
            value = partsVal[0];
            for (int i = 1; i < conditions.size(); ++i)
            {
                value += " , " + partsVal[i];
            }
        }
        partsVal.clear();
        preparedParts(whereParts,conditionsWhere,partsVal,re,allowedOps,allowedColumns, ":where");
        if (!conditionsWhere.isEmpty())
        {
            whereVal = partsVal[0];
            for (int i = 1; i < conditionsWhere.size(); ++i)
            {
                whereVal += " AND " + partsVal[i];
            }
        }
        QString sql = QString("UPDATE %1 SET %2 WHERE %3").arg(currentTableName, value,whereVal);
        QSqlQuery query(db);
        query.prepare(sql);
        for (int i = 0; i < conditions.size(); ++i)
        {
            QString val = conditions[i].value;

            query.bindValue(":val" + QString::number(i), val);

        }
        for (int i = 0; i < conditionsWhere.size(); ++i)
        {
            QString val = conditionsWhere[i].value;

            query.bindValue(":where" + QString::number(i), val);

        }
        db.transaction();
        if(query.exec())
        {
            int rowsAffected = query.numRowsAffected();
            QMessageBox::information(this, "Успех",
                                     QString("Обновлено строк: %1").arg(rowsAffected));

            currentModel->setQuery(query);
            db.commit();
            setPage(*tab, primarykey);
            m_highlightDelegate->setSearchText(conditionsWhere[0].value);
            currentView->setItemDelegate(m_highlightDelegate);
        }
        else {
            QMessageBox::warning(this, "Ошибка",
                                 "Не удалось обновить: " + query.lastError().text());
            db.rollback();
            setPage(*tab, primarykey);
        }

    }
    else if(action == "Delete")
    {
        static const QRegularExpression re(R"(^\s*([\w_]+)\s*(=)\s*(.+)\s*$)",
                                           QRegularExpression::CaseInsensitiveOption);
        static const QRegularExpression whereRe("\\bWHERE\\b\\s+(.*)", QRegularExpression::CaseInsensitiveOption);
        static const QRegularExpression andRe(R"(\s+(AND|OR)\s+)", QRegularExpression::CaseInsensitiveOption);

        QRegularExpressionMatch matchWhere = whereRe.match(condition.trimmed());
        QString where = matchWhere.captured(1);
        QStringList whereParts = where.split(andRe,Qt::SkipEmptyParts);
        QString value;
        QStringList logicOps;
        where.clear();

        QRegularExpressionMatchIterator it = andRe.globalMatch(condition);
        QList<Condition> conditionsWhere;
        QStringList partsVal;

        QSqlRecord rec = db.record(currentTableName);
        QSet<QString> allowedOps = {"=", "<", ">", "<=", ">=", "LIKE"};
        QSet<QString> allowedColumns;
        for (int i = 0; i < rec.count(); ++i) {
            allowedColumns.insert(rec.fieldName(i));
        }
        while (it.hasNext())
        {
            QRegularExpressionMatch match = it.next();
            logicOps << match.captured(1).toUpper();
        }
        preparedParts(whereParts,conditionsWhere,partsVal,re,allowedOps,allowedColumns, ":where");
        if (!conditionsWhere.isEmpty())
        {
            value = partsVal[0];
            for (int i = 1; i < conditionsWhere.size(); ++i)
            {
                QString op = logicOps.value(i-1);
                value += " " + op + " " + partsVal[i];
            }
        }

        QString queryStr = QString("DELETE FROM %1 WHERE %2 ")
                               .arg(currentTableName, value);
        QSqlQuery query(db);
        query.prepare(queryStr);
        for (int i = 0; i < conditionsWhere.size(); ++i)
        {
            QString val = conditionsWhere[i].value;

            query.bindValue(":where" + QString::number(i), val);

        }
        db.transaction();
        if (query.exec()) {
            int rowsAffected = query.numRowsAffected();
            QMessageBox::information(this, "Успех",
                                     QString("Удалено строк: %1").arg(rowsAffected));
            currentModel->setQuery(query);
            db.commit();
            setPage(*tab, primarykey);
        } else {
            QMessageBox::warning(this, "Ошибка",
                                 "Не удалось удалить строку: " + query.lastError().text());
            db.rollback();
            setPage(*tab, primarykey);

    }
    }

}

void MainWindow::preparedParts(const QStringList &parts, QList<Condition> &conditions, QStringList &partsVal, const QRegularExpression re,
                               const QSet<QString> &allowedOps, const QSet<QString> allowedColumns, const QString &binding)
{
    int i = 0;
    for (const QString &part : std::as_const(parts))
    {
        QRegularExpressionMatch match = re.match(part.trimmed());

        if (!match.hasMatch())
            continue;

        Condition c;
        c.column = match.captured(1);
        c.op = match.captured(2).toUpper();
        c.value = match.captured(3).trimmed();
        if (!allowedColumns.contains(c.column)) {
            return;
        }
        if (!allowedOps.contains(c.op)) {
            return;
        }
        conditions << c;

        QString cond;
        cond = QString("%1 %2 "+binding+"%3").arg(c.column, c.op).arg(i);
        partsVal << cond;
        i++;
    }
}

void MainWindow::on_pushButton_clear_clicked()
{
    int currentIndex = ui->tabWidget->currentIndex();
    QWidget *widget = ui->tabWidget->widget(currentIndex);
    QueryTab *tab =getCurrentQueryTab(widget);

    if(!tab)
    {
        QMessageBox::warning(this, "Ошибка", "Отсутсвует табличное представление.");
        return;
    }
    QTableView *currentView =tab->table;
    QSqlQueryModel* currentModel = tab->model;
    QString currentTableName = tab->table_name;

    if (!currentView || !currentModel) {
        QMessageBox::warning(this, "Ошибка", "Отсутствует таблица или модель.");
        return;
    }
    QSqlDatabase db = currentDatabase();
    QSqlRecord pk = db.primaryIndex(currentTableName);
    QStringList pkFields;
    for (int i = 0; i < pk.count(); ++i)
        pkFields << pk.fieldName(i);
    QString primarykey = pkFields.join(", ");
    setPage(*tab, primarykey);
    ui->lineEdit_action->clear();
    m_highlightDelegate->setSearchText("");

}

// ту ду, че еще надо сделать
//Соответсвенно работа с функциями, индексами, процедурами, ввод/вывод данных в виде форм, импорт в один из форматов, писалка sql запросов,
//метрики производительности, например нагрузка на сервер и т.д., планировщик запросов и его вывод, обработку ошибок, расширить работу с таблицами, реализовать простой интерфейс для работы
//с ролями
