#include "templatemanager.h"

TemplateManager::TemplateManager() {}

void TemplateManager::loadJSON(const QString &path)
{
    QFile file(path);

    if(!file.open(QIODevice::ReadOnly))
    {
        qWarning() << "Cannot open file";
        return;
    }

    QByteArray data = file.readAll();
    file.close();
    QJsonParseError err;
    QJsonDocument doc = QJsonDocument::fromJson(data, &err);
    if (err.error != QJsonParseError::NoError) {
        qWarning() << "JSON parse error:" << err.errorString();
        return;
    }
    if (!doc.isObject()) {
        qWarning() << "Root is not an object";
        return;
    }
    QJsonObject root = doc.object();
    if (!root.contains("templates") || !root["templates"].isArray()) {
        qWarning() << "No templates array!";
        return;
    }
    QJsonArray arr = root["templates"].toArray();

    for (const QJsonValue &val : std::as_const(arr)) {
        QJsonObject obj = val.toObject();

        QString table = obj["table"].toString();
        QString file  = obj["filepath"].toString();
        map.insert(table,file);
        qDebug() << table << file;
    }
}

void TemplateManager::writeJSON(const QString &path, QString &tablename, QString &filepath)
{
    QJsonArray arr;

    QJsonObject u;
    u["table"] = tablename;
    u["file"] = filepath;

    arr.append(u);
    map.insert(tablename,filepath);
    QJsonObject root;
    root["templates"] = arr;

    QJsonDocument doc(root);

    QFile file(path);
    file.open(QIODevice::WriteOnly);
    file.write(doc.toJson());
    file.close();
}

QString TemplateManager::get_template(const QString &path, const QString &tablename)
{
    QFile file(path);

    if(!file.open(QIODevice::ReadOnly))
    {
        qWarning() << "Cannot open file";
        return "";
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonObject root = doc.object();
    QJsonArray arr = root["templates"].toArray();

    for (const QJsonValue &val : std::as_const(arr)) {
        QJsonObject obj = val.toObject();

        QString table = obj["table"].toString();
        QString file  = obj["filepath"].toString();
        if(table == tablename)
            return file;

        qDebug() << table << file;
    }
    return "";
}
