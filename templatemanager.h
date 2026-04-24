#ifndef TEMPLATEMANAGER_H
#define TEMPLATEMANAGER_H
#include <QString>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

class TemplateManager
{
public:
    TemplateManager();
    void loadJSON(const QString &path);
    void writeJSON(const QString &path, QString &tablename, QString &filepath);
    QString get_template(const QString &path, const QString &tablename);

private:
    QHash<QString, QString> map;
};

#endif // TEMPLATEMANAGER_H
