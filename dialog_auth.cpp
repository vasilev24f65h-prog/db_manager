
#include "dialog_auth.h"
#include "qdebug.h"
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
    connect(ui->pushButton_update_clicked, &QPushButton::clicked,
            this, [this]()
            {
                QString name = ui->comboBox_connection_name->currentText();

                if (name.isEmpty())
                    return;

                QMessageBox::StandardButton res =
                    QMessageBox::question(this, "Обновление",
                                          "Обновить подключение " + name + "?");

                if (res == QMessageBox::Yes)
                    updateConnection(name);
                if (ui->comboBox_connection_name->count() > 0)
                    onConnectionChanged(ui->comboBox_connection_name->currentText());
            });
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
    ui->comboBox_connection_name->blockSignals(true);
    QString current = ui->comboBox_connection_name->currentText();
    ui->comboBox_connection_name->clear();
    ui->comboBox_connection_name->addItems(connections);
    int index = ui->comboBox_connection_name->findText(current);
    if (index >= 0)
        ui->comboBox_connection_name->setCurrentIndex(index);
    else if (!connections.isEmpty())
        ui->comboBox_connection_name->setCurrentIndex(0);

    ui->comboBox_connection_name->blockSignals(false);

    if (!ui->comboBox_connection_name->currentText().isEmpty())
        onConnectionChanged(ui->comboBox_connection_name->currentText());
}

void Dialog_auth::onConnectionChanged(const QString &name)
{
    QSettings settings("Exempl", "DBApp");

    QString key = "connections/" + name;
    ui->lineEdit_host->clear();
    ui->lineEdit_db->clear();
    ui->lineEdit_username->clear();
    ui->lineEdit_pass->clear();
    ui->checkBox_pass->setChecked(false);
    ui->lineEdit_host->setText(settings.value(key + "/server").toString());
    ui->lineEdit_db->setText(settings.value(key + "/database").toString());
    ui->lineEdit_username->setText(settings.value(key + "/user").toString());
    std::wstring passkey = settings.value(key + "/credkey").toString().toStdWString();
    std::wstring pass;
    if(readCredential(passkey, pass))
    {
        qDebug() << "Read pass from wcm";
        ui->checkBox_pass->setChecked(true);
        ui->lineEdit_pass->setText(QString::fromStdWString(pass));
    }
    else
        qDebug() << "Dont read pass";

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
    int index = ui->comboBox_connection_name->findText(connection);
    if(index>=0)
    {
        qDebug() << "This connection name is exists";
        return;
    }
    QSettings settings("Exempl", "DBApp");

    QString key = "connections/" + connection;

    settings.setValue(key + "/server", ui->lineEdit_host->text());
    settings.setValue(key + "/database", ui->lineEdit_db->text());
    settings.setValue(key + "/user", ui->lineEdit_username->text());
    QString key_pass_qt = key + " for " + ui->lineEdit_username->text();
    std::wstring key_pass = key_pass_qt.toStdWString();
    if(ui->checkBox_pass->isChecked())
    {
        if(writeCredential(key_pass,ui->lineEdit_pass->text().toStdWString()))
        {
            qDebug() << "Write pass to wcm";
            settings.setValue(key + "/credkey", QString::fromStdWString(key_pass));
        }
        else
        {
            qDebug() << "Dont write to pass in wcm";
        }
    }

    loadConnections();
}

void Dialog_auth::deleteConnection(const QString &name)
{
    QSettings settings("Exempl", "DBApp");
    std::wstring key_pass = settings.value("connections/" + name + "/credkey").toString().toStdWString();
    if(!key_pass.empty())
    {
        deleteCredential(key_pass);
        qDebug() << "Delete pass";
    }
    settings.beginGroup("connections");
    settings.remove(name);
    settings.endGroup();

    loadConnections();
}

void Dialog_auth::updateConnection(const QString &name)
{
    QSettings settings("Exempl", "DBApp");

    QString key = "connections/" + name;

    settings.setValue(key + "/server", ui->lineEdit_host->text());
    settings.setValue(key + "/database", ui->lineEdit_db->text());
    settings.setValue(key + "/user", ui->lineEdit_username->text());

    if(ui->checkBox_pass->isChecked())
    {
        QString key_pass_qt = key + " for " + ui->lineEdit_username->text();
        std::wstring key_pass = key_pass_qt.toStdWString();
        if(writeCredential(key_pass,ui->lineEdit_pass->text().toStdWString()))
        {
            qDebug() << "Write pass to wcm";
            settings.setValue(key + "/credkey", QString::fromStdWString(key_pass));
        }
        else
        {
            qDebug() << "Dont write to pass in wcm";
        }
    }
    else
    {
        std::wstring key_pass = settings.value(key + "/credkey").toString().toStdWString();
        if(!key_pass.empty())
        {
            deleteCredential(key_pass);
            settings.remove(key + "/credkey");
            qDebug() << "Delete pass";
        }
    }

    loadConnections();
}
