#include "dialog_auth.h"
#include "ui_dialog_auth.h"

Dialog_auth::Dialog_auth(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_auth)
{
    ui->setupUi(this);
    connect(ui->buttonBox_login, &QDialogButtonBox::accepted,this, &Dialog_auth::on_ButtonBox_accepted );
    connect(ui->buttonBox_login, &QDialogButtonBox::rejected,this, &Dialog_auth::reject );
}

Dialog_auth::~Dialog_auth()
{
    delete ui;
}

void Dialog_auth::on_ButtonBox_accepted()
{
    username = ui->lineEdit_name->text();
    password = ui->lineEdit_pass->text();
    namedb = ui->lineEdit_db->text();
    if (username.isEmpty() || password.isEmpty() || namedb.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите имя пользователя и пароль.");
        return;
    }
    emit credentialsEntered(username, password, namedb);
    accept();
}


