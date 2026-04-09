/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionSave;
    QAction *actionSave_as;
    QAction *actionOpen;
    QAction *actionSettibgs_db;
    QAction *actionQuery;
    QWidget *centralwidget;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QTreeWidget *treeWidget;
    QPushButton *pushButton_login;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer;
    QPushButton *pushButton_insertRow;
    QPushButton *pushButton_updateRow;
    QPushButton *pushButton_deleteRow;
    QPushButton *pushButton;
    QSpacerItem *verticalSpacer_2;
    QTabWidget *tabWidget;
    QPushButton *pushButton_addTab;
    QHBoxLayout *horizontalLayout;
    QComboBox *comboBox_action;
    QLineEdit *lineEdit_action;
    QPushButton *pushButton_sendAction;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuSettings;
    QMenu *menuAbout;
    QMenu *menuCreate_query;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1176, 681);
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        actionSave_as = new QAction(MainWindow);
        actionSave_as->setObjectName(QString::fromUtf8("actionSave_as"));
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        actionSettibgs_db = new QAction(MainWindow);
        actionSettibgs_db->setObjectName(QString::fromUtf8("actionSettibgs_db"));
        actionQuery = new QAction(MainWindow);
        actionQuery->setObjectName(QString::fromUtf8("actionQuery"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout_2 = new QGridLayout(centralwidget);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        treeWidget = new QTreeWidget(centralwidget);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName(QString::fromUtf8("treeWidget"));

        gridLayout->addWidget(treeWidget, 5, 0, 1, 1);

        pushButton_login = new QPushButton(centralwidget);
        pushButton_login->setObjectName(QString::fromUtf8("pushButton_login"));

        gridLayout->addWidget(pushButton_login, 0, 1, 1, 1);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        pushButton_insertRow = new QPushButton(centralwidget);
        pushButton_insertRow->setObjectName(QString::fromUtf8("pushButton_insertRow"));

        verticalLayout_2->addWidget(pushButton_insertRow);

        pushButton_updateRow = new QPushButton(centralwidget);
        pushButton_updateRow->setObjectName(QString::fromUtf8("pushButton_updateRow"));

        verticalLayout_2->addWidget(pushButton_updateRow);

        pushButton_deleteRow = new QPushButton(centralwidget);
        pushButton_deleteRow->setObjectName(QString::fromUtf8("pushButton_deleteRow"));

        verticalLayout_2->addWidget(pushButton_deleteRow);

        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        verticalLayout_2->addWidget(pushButton);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);


        gridLayout->addLayout(verticalLayout_2, 5, 2, 1, 1);

        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));

        gridLayout->addWidget(tabWidget, 5, 1, 1, 1);

        pushButton_addTab = new QPushButton(centralwidget);
        pushButton_addTab->setObjectName(QString::fromUtf8("pushButton_addTab"));

        gridLayout->addWidget(pushButton_addTab, 0, 2, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        comboBox_action = new QComboBox(centralwidget);
        comboBox_action->addItem(QString());
        comboBox_action->addItem(QString());
        comboBox_action->addItem(QString());
        comboBox_action->addItem(QString());
        comboBox_action->setObjectName(QString::fromUtf8("comboBox_action"));

        horizontalLayout->addWidget(comboBox_action);

        lineEdit_action = new QLineEdit(centralwidget);
        lineEdit_action->setObjectName(QString::fromUtf8("lineEdit_action"));

        horizontalLayout->addWidget(lineEdit_action);

        pushButton_sendAction = new QPushButton(centralwidget);
        pushButton_sendAction->setObjectName(QString::fromUtf8("pushButton_sendAction"));

        horizontalLayout->addWidget(pushButton_sendAction);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1176, 22));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuSettings = new QMenu(menubar);
        menuSettings->setObjectName(QString::fromUtf8("menuSettings"));
        menuAbout = new QMenu(menubar);
        menuAbout->setObjectName(QString::fromUtf8("menuAbout"));
        menuCreate_query = new QMenu(menubar);
        menuCreate_query->setObjectName(QString::fromUtf8("menuCreate_query"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuSettings->menuAction());
        menubar->addAction(menuAbout->menuAction());
        menubar->addAction(menuCreate_query->menuAction());
        menuFile->addAction(actionSave);
        menuFile->addAction(actionSave_as);
        menuFile->addAction(actionOpen);
        menuSettings->addAction(actionSettibgs_db);
        menuCreate_query->addAction(actionQuery);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionSave->setText(QCoreApplication::translate("MainWindow", "Save", nullptr));
        actionSave_as->setText(QCoreApplication::translate("MainWindow", "Save as", nullptr));
        actionOpen->setText(QCoreApplication::translate("MainWindow", "Open", nullptr));
        actionSettibgs_db->setText(QCoreApplication::translate("MainWindow", "Settibgs db", nullptr));
        actionQuery->setText(QCoreApplication::translate("MainWindow", "Query", nullptr));
        pushButton_login->setText(QCoreApplication::translate("MainWindow", "Login", nullptr));
        pushButton_insertRow->setText(QCoreApplication::translate("MainWindow", "Insert", nullptr));
        pushButton_updateRow->setText(QCoreApplication::translate("MainWindow", "Update", nullptr));
        pushButton_deleteRow->setText(QCoreApplication::translate("MainWindow", "Delete", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));
        pushButton_addTab->setText(QCoreApplication::translate("MainWindow", "Add tab", nullptr));
        comboBox_action->setItemText(0, QCoreApplication::translate("MainWindow", "Search", nullptr));
        comboBox_action->setItemText(1, QCoreApplication::translate("MainWindow", "Filter", nullptr));
        comboBox_action->setItemText(2, QCoreApplication::translate("MainWindow", "Update", nullptr));
        comboBox_action->setItemText(3, QCoreApplication::translate("MainWindow", "Delete", nullptr));

        pushButton_sendAction->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
        menuSettings->setTitle(QCoreApplication::translate("MainWindow", "Settings", nullptr));
        menuAbout->setTitle(QCoreApplication::translate("MainWindow", "About", nullptr));
        menuCreate_query->setTitle(QCoreApplication::translate("MainWindow", "Create query", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
