/********************************************************************************
** Form generated from reading UI file 'browserwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BROWSERWIDGET_H
#define UI_BROWSERWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "connectionwidget.h"

QT_BEGIN_NAMESPACE

class Ui_Browser
{
public:
    QAction *insertRowAction;
    QAction *deleteRowAction;
    QAction *fieldStrategyAction;
    QAction *rowStrategyAction;
    QAction *manualStrategyAction;
    QAction *submitAction;
    QAction *revertAction;
    QAction *selectAction;
    QVBoxLayout *vboxLayout;
    QSplitter *splitter_2;
    ConnectionWidget *connectionWidget;
    QTableView *table;
    QGroupBox *groupBox;
    QVBoxLayout *vboxLayout1;
    QTextEdit *sqlEdit;
    QHBoxLayout *hboxLayout;
    QSpacerItem *spacerItem;
    QPushButton *clearButton;
    QPushButton *submitButton;

    void setupUi(QWidget *Browser)
    {
        if (Browser->objectName().isEmpty())
            Browser->setObjectName(QString::fromUtf8("Browser"));
        Browser->resize(765, 515);
        insertRowAction = new QAction(Browser);
        insertRowAction->setObjectName(QString::fromUtf8("insertRowAction"));
        insertRowAction->setEnabled(false);
        deleteRowAction = new QAction(Browser);
        deleteRowAction->setObjectName(QString::fromUtf8("deleteRowAction"));
        deleteRowAction->setEnabled(false);
        fieldStrategyAction = new QAction(Browser);
        fieldStrategyAction->setObjectName(QString::fromUtf8("fieldStrategyAction"));
        fieldStrategyAction->setCheckable(true);
        rowStrategyAction = new QAction(Browser);
        rowStrategyAction->setObjectName(QString::fromUtf8("rowStrategyAction"));
        rowStrategyAction->setCheckable(true);
        manualStrategyAction = new QAction(Browser);
        manualStrategyAction->setObjectName(QString::fromUtf8("manualStrategyAction"));
        manualStrategyAction->setCheckable(true);
        submitAction = new QAction(Browser);
        submitAction->setObjectName(QString::fromUtf8("submitAction"));
        revertAction = new QAction(Browser);
        revertAction->setObjectName(QString::fromUtf8("revertAction"));
        selectAction = new QAction(Browser);
        selectAction->setObjectName(QString::fromUtf8("selectAction"));
        vboxLayout = new QVBoxLayout(Browser);
#ifndef Q_OS_MAC
        vboxLayout->setSpacing(6);
#endif
        vboxLayout->setContentsMargins(8, 8, 8, 8);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        splitter_2 = new QSplitter(Browser);
        splitter_2->setObjectName(QString::fromUtf8("splitter_2"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(splitter_2->sizePolicy().hasHeightForWidth());
        splitter_2->setSizePolicy(sizePolicy);
        splitter_2->setOrientation(Qt::Horizontal);
        connectionWidget = new ConnectionWidget(splitter_2);
        connectionWidget->setObjectName(QString::fromUtf8("connectionWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Ignored, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(1);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(connectionWidget->sizePolicy().hasHeightForWidth());
        connectionWidget->setSizePolicy(sizePolicy1);
        splitter_2->addWidget(connectionWidget);
        table = new QTableView(splitter_2);
        table->setObjectName(QString::fromUtf8("table"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(2);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(table->sizePolicy().hasHeightForWidth());
        table->setSizePolicy(sizePolicy2);
        table->setContextMenuPolicy(Qt::ActionsContextMenu);
        table->setSelectionBehavior(QAbstractItemView::SelectRows);
        splitter_2->addWidget(table);

        vboxLayout->addWidget(splitter_2);

        groupBox = new QGroupBox(Browser);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy3);
        groupBox->setMaximumSize(QSize(16777215, 180));
        vboxLayout1 = new QVBoxLayout(groupBox);
#ifndef Q_OS_MAC
        vboxLayout1->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        vboxLayout1->setContentsMargins(9, 9, 9, 9);
#endif
        vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
        sqlEdit = new QTextEdit(groupBox);
        sqlEdit->setObjectName(QString::fromUtf8("sqlEdit"));
        QSizePolicy sizePolicy4(QSizePolicy::Expanding, QSizePolicy::MinimumExpanding);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(sqlEdit->sizePolicy().hasHeightForWidth());
        sqlEdit->setSizePolicy(sizePolicy4);
        sqlEdit->setMinimumSize(QSize(0, 18));
        sqlEdit->setBaseSize(QSize(0, 120));

        vboxLayout1->addWidget(sqlEdit);

        hboxLayout = new QHBoxLayout();
#ifndef Q_OS_MAC
        hboxLayout->setSpacing(6);
#endif
        hboxLayout->setContentsMargins(1, 1, 1, 1);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        spacerItem = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem);

        clearButton = new QPushButton(groupBox);
        clearButton->setObjectName(QString::fromUtf8("clearButton"));

        hboxLayout->addWidget(clearButton);

        submitButton = new QPushButton(groupBox);
        submitButton->setObjectName(QString::fromUtf8("submitButton"));

        hboxLayout->addWidget(submitButton);


        vboxLayout1->addLayout(hboxLayout);


        vboxLayout->addWidget(groupBox);

        QWidget::setTabOrder(sqlEdit, clearButton);
        QWidget::setTabOrder(clearButton, submitButton);
        QWidget::setTabOrder(submitButton, connectionWidget);
        QWidget::setTabOrder(connectionWidget, table);

        retranslateUi(Browser);

        QMetaObject::connectSlotsByName(Browser);
    } // setupUi

    void retranslateUi(QWidget *Browser)
    {
        Browser->setWindowTitle(QCoreApplication::translate("Browser", "Qt SQL Browser", nullptr));
        insertRowAction->setText(QCoreApplication::translate("Browser", "&Insert Row", nullptr));
#if QT_CONFIG(statustip)
        insertRowAction->setStatusTip(QCoreApplication::translate("Browser", "Inserts a new Row", nullptr));
#endif // QT_CONFIG(statustip)
        deleteRowAction->setText(QCoreApplication::translate("Browser", "&Delete Row", nullptr));
#if QT_CONFIG(statustip)
        deleteRowAction->setStatusTip(QCoreApplication::translate("Browser", "Deletes the current Row", nullptr));
#endif // QT_CONFIG(statustip)
        fieldStrategyAction->setText(QCoreApplication::translate("Browser", "Submit on &Field Change", nullptr));
#if QT_CONFIG(tooltip)
        fieldStrategyAction->setToolTip(QCoreApplication::translate("Browser", "Commit on Field Change", nullptr));
#endif // QT_CONFIG(tooltip)
        rowStrategyAction->setText(QCoreApplication::translate("Browser", "Submit on &Row Change", nullptr));
#if QT_CONFIG(tooltip)
        rowStrategyAction->setToolTip(QCoreApplication::translate("Browser", "Commit on Row Change", nullptr));
#endif // QT_CONFIG(tooltip)
        manualStrategyAction->setText(QCoreApplication::translate("Browser", "Submit &Manually", nullptr));
#if QT_CONFIG(tooltip)
        manualStrategyAction->setToolTip(QCoreApplication::translate("Browser", "Commit Manually", nullptr));
#endif // QT_CONFIG(tooltip)
        submitAction->setText(QCoreApplication::translate("Browser", "&Submit All", nullptr));
#if QT_CONFIG(tooltip)
        submitAction->setToolTip(QCoreApplication::translate("Browser", "Submit Changes", nullptr));
#endif // QT_CONFIG(tooltip)
        revertAction->setText(QCoreApplication::translate("Browser", "&Revert All", nullptr));
#if QT_CONFIG(tooltip)
        revertAction->setToolTip(QCoreApplication::translate("Browser", "Revert", nullptr));
#endif // QT_CONFIG(tooltip)
        selectAction->setText(QCoreApplication::translate("Browser", "S&elect", nullptr));
#if QT_CONFIG(tooltip)
        selectAction->setToolTip(QCoreApplication::translate("Browser", "Refresh Data from Database", nullptr));
#endif // QT_CONFIG(tooltip)
        groupBox->setTitle(QCoreApplication::translate("Browser", "SQL Query", nullptr));
        clearButton->setText(QCoreApplication::translate("Browser", "&Clear", nullptr));
        submitButton->setText(QCoreApplication::translate("Browser", "&Submit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Browser: public Ui_Browser {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BROWSERWIDGET_H
