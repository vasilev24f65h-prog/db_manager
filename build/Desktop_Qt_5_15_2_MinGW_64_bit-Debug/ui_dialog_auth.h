/********************************************************************************
** Form generated from reading UI file 'dialog_auth.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_AUTH_H
#define UI_DIALOG_AUTH_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_Dialog_auth
{
public:
    QGridLayout *gridLayout_2;
    QDialogButtonBox *buttonBox_login;
    QGridLayout *gridLayout_inputArea;
    QSpacerItem *verticalSpacer;
    QLineEdit *lineEdit_pass;
    QLabel *label_name;
    QLabel *label_pass;
    QSpacerItem *verticalSpacer_2;
    QLineEdit *lineEdit_db;
    QLineEdit *lineEdit_name;
    QLabel *label;
    QSpacerItem *verticalSpacer_3;

    void setupUi(QDialog *Dialog_auth)
    {
        if (Dialog_auth->objectName().isEmpty())
            Dialog_auth->setObjectName(QString::fromUtf8("Dialog_auth"));
        Dialog_auth->resize(400, 300);
        gridLayout_2 = new QGridLayout(Dialog_auth);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        buttonBox_login = new QDialogButtonBox(Dialog_auth);
        buttonBox_login->setObjectName(QString::fromUtf8("buttonBox_login"));
        buttonBox_login->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        buttonBox_login->setCenterButtons(true);

        gridLayout_2->addWidget(buttonBox_login, 1, 0, 1, 1);

        gridLayout_inputArea = new QGridLayout();
        gridLayout_inputArea->setObjectName(QString::fromUtf8("gridLayout_inputArea"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_inputArea->addItem(verticalSpacer, 8, 1, 1, 1);

        lineEdit_pass = new QLineEdit(Dialog_auth);
        lineEdit_pass->setObjectName(QString::fromUtf8("lineEdit_pass"));
        lineEdit_pass->setMaximumSize(QSize(200, 50));

        gridLayout_inputArea->addWidget(lineEdit_pass, 7, 1, 1, 1);

        label_name = new QLabel(Dialog_auth);
        label_name->setObjectName(QString::fromUtf8("label_name"));

        gridLayout_inputArea->addWidget(label_name, 3, 1, 1, 1);

        label_pass = new QLabel(Dialog_auth);
        label_pass->setObjectName(QString::fromUtf8("label_pass"));

        gridLayout_inputArea->addWidget(label_pass, 5, 1, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_inputArea->addItem(verticalSpacer_2, 0, 1, 1, 1);

        lineEdit_db = new QLineEdit(Dialog_auth);
        lineEdit_db->setObjectName(QString::fromUtf8("lineEdit_db"));
        lineEdit_db->setMaximumSize(QSize(200, 50));

        gridLayout_inputArea->addWidget(lineEdit_db, 2, 1, 1, 1);

        lineEdit_name = new QLineEdit(Dialog_auth);
        lineEdit_name->setObjectName(QString::fromUtf8("lineEdit_name"));
        lineEdit_name->setMaximumSize(QSize(200, 50));

        gridLayout_inputArea->addWidget(lineEdit_name, 4, 1, 1, 1);

        label = new QLabel(Dialog_auth);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_inputArea->addWidget(label, 1, 1, 1, 1);


        gridLayout_2->addLayout(gridLayout_inputArea, 0, 0, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_3, 2, 0, 1, 1);


        retranslateUi(Dialog_auth);

        QMetaObject::connectSlotsByName(Dialog_auth);
    } // setupUi

    void retranslateUi(QDialog *Dialog_auth)
    {
        Dialog_auth->setWindowTitle(QCoreApplication::translate("Dialog_auth", "Dialog", nullptr));
        label_name->setText(QCoreApplication::translate("Dialog_auth", "\320\230\320\274\321\217 \320\277\320\276\320\273\321\214\320\267\320\276\320\262\320\260\321\202\320\265\320\273\321\217", nullptr));
        label_pass->setText(QCoreApplication::translate("Dialog_auth", "\320\237\320\260\321\200\320\276\320\273\321\214", nullptr));
        lineEdit_db->setText(QCoreApplication::translate("Dialog_auth", "Goods", nullptr));
        label->setText(QCoreApplication::translate("Dialog_auth", "\320\221\320\260\320\267\320\260 \320\264\320\260\320\275\320\275\321\213\321\205", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog_auth: public Ui_Dialog_auth {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_AUTH_H
