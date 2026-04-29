
#ifndef DIALOG_AUTH_H
#define DIALOG_AUTH_H
#include "credpass.h"
#include <QDialog>
#include <QString>
#include <QMessageBox>
#include <QSettings>
namespace Ui {
class Dialog_auth;
}
enum AuthMode {
    WindowsAuth,
    SqlAuth
};

class Dialog_auth : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_auth(QWidget *parent = nullptr);
    ~Dialog_auth();
    void loadConnections();
    bool getAuthMetod();

private slots:
    void on_ButtonBox_accepted();
    void onConnectionChanged(const QString &name);
    void on_pushButton_add_connection_clicked();
    void deleteConnection(const QString &name);
    void updateConnection(const QString &name);
    void onUseWindowsAuth(int index);
signals:
    void credentialsEntered(const QString &username, const QString &password, const QString &namedb, const QString &host, const QString &connection);


private:
    Ui::Dialog_auth *ui;
    QString connection;
    QString username;
    QString password;
    QString namedb;
    QString host;
    bool use_win;
};

#endif // DIALOG_AUTH_H



