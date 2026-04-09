#ifndef DIALOG_AUTH_H
#define DIALOG_AUTH_H

#include <QDialog>
#include <QString>
#include <QMessageBox>

namespace Ui {
class Dialog_auth;
}

class Dialog_auth : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_auth(QWidget *parent = nullptr);
    ~Dialog_auth();


private slots:
    void on_ButtonBox_accepted();

signals:
    void credentialsEntered(const QString &username, const QString &password, const QString &namedb);

private:
    Ui::Dialog_auth *ui;
    QString username;
    QString password;
    QString namedb;


};

#endif // DIALOG_AUTH_H
