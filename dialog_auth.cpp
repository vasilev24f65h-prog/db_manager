
#include "dialog_auth.h"
#include "ui_dialog_auth.h"

Dialog_auth::Dialog_auth(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_auth)
{
    ui->setupUi(this);
    loadConnections();
    connect(ui->buttonBox_login, &QDialogButtonBox::accepted,this, &Dialog_auth::on_ButtonBox_accepted );
    connect(ui->buttonBox_login, &QDialogButtonBox::rejected,this, &Dialog_auth::reject );
    connect(ui->comboBox_connection_name, &QComboBox::currentTextChanged,
            this, &Dialog_auth::onConnectionChanged);
    connect(ui->pushButton_delete_connection, &QPushButton::clicked,
            this, [this]()
            {
                QString name = ui->comboBox_connection_name->currentText();

                if (name.isEmpty())
                    return;

                QMessageBox::StandardButton res =
                    QMessageBox::question(this, "Удаление",
                                          "Удалить подключение " + name + "?");

                if (res == QMessageBox::Yes)
                    deleteConnection(name);
                if (ui->comboBox_connection_name->count() > 0)
                    onConnectionChanged(ui->comboBox_connection_name->currentText());
            });
}

Dialog_auth::~Dialog_auth()
{
    delete ui;
}
void Dialog_auth::loadConnections()
{
    QSettings settings("Exempl", "DBApp");

    settings.beginGroup("connections");
    QStringList connections = settings.childGroups();
    settings.endGroup();

    ui->comboBox_connection_name->clear();
    ui->comboBox_connection_name->addItems(connections);
}

void Dialog_auth::onConnectionChanged(const QString &name)
{
    QSettings settings("Exempl", "DBApp");

    QString key = "connections/" + name;

    ui->lineEdit_host->setText(settings.value(key + "/server").toString());
    ui->lineEdit_db->setText(settings.value(key + "/database").toString());
    ui->lineEdit_username->setText(settings.value(key + "/user").toString());

}
void Dialog_auth::on_ButtonBox_accepted()
{
    connection = ui->comboBox_connection_name->currentText();
    username = ui->lineEdit_username->text();
    password = ui->lineEdit_pass->text();
    namedb = ui->lineEdit_db->text();
    host = ui->lineEdit_host->text();

    if (username.isEmpty() || password.isEmpty() ||
        namedb.isEmpty() || host.isEmpty() || connection.isEmpty())
    {
        QMessageBox::warning(this, "Ошибка", "Заполните все поля.");
        return;
    }

    emit credentialsEntered(username, password, namedb, host, connection);
    accept();
}



void Dialog_auth::on_pushButton_add_connection_clicked()
{
    QDialog dlg(this);
    QVBoxLayout *layout = new QVBoxLayout(&dlg);

    QLineEdit *edit_conn = new QLineEdit(&dlg);
    layout->addWidget(edit_conn);

    QDialogButtonBox *btn = new QDialogButtonBox(Qt::Horizontal, &dlg);
    btn->addButton("OK", QDialogButtonBox::AcceptRole);
    btn->addButton("Cancel", QDialogButtonBox::RejectRole);

    layout->addWidget(btn);

    connect(btn, &QDialogButtonBox::accepted, &dlg, &QDialog::accept);
    connect(btn, &QDialogButtonBox::rejected, &dlg, &QDialog::reject);

    if (dlg.exec() != QDialog::Accepted)
        return;

    connection = edit_conn->text();

    QSettings settings("Exempl", "DBApp");

    QString key = "connections/" + connection;

    settings.setValue(key + "/server", ui->lineEdit_host->text());
    settings.setValue(key + "/database", ui->lineEdit_db->text());
    settings.setValue(key + "/user", ui->lineEdit_username->text());

    loadConnections();
}

void Dialog_auth::deleteConnection(const QString &name)
{
    QSettings settings("Exempl", "DBApp");

    settings.beginGroup("connections");
    settings.remove(name);
    settings.endGroup();

    loadConnections();
}
