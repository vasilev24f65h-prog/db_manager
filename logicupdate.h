
#ifndef LOGICUPDATE_H
#define LOGICUPDATE_H
#include "qdebug.h"
#include "qregularexpression.h"
#include "qsqlerror.h"
#include "qsqltablemodel.h"
#include <QString>
#include <QStringList>
#include <set>
#include <memory>
struct UpdateRequeted
{
    QString command;
    QStringList multi_value;
};

class UpdateParse
{
public:
    static UpdateRequeted parseCommand(QString &input);
    static void setupRowCol(QModelIndexList &indexes, std::set<int> &columns, QList<int> &rows );
    static void parseData(QString &upd_data, std::set<int> &columns, UpdateRequeted &req);

};

class UpdateStrategy
{
public:
    virtual ~UpdateStrategy() = default;

    virtual void apply(QSqlTableModel* model,
                            const QModelIndexList& indexes,
                            const QStringList& values, const std::set<int> &columns, const QList<int> &rows) = 0;

};

class Cycle : public UpdateStrategy
{
public:
    void apply(QSqlTableModel* model,
               const QModelIndexList& indexes,
               const QStringList& multi_value, const std::set<int> &columns, const QList<int> &rows) override;

};

class Defoult : public UpdateStrategy
{
    void apply(QSqlTableModel* model,
               const QModelIndexList& indexes,
               const QStringList& multi_value, const std::set<int> &columns, const QList<int> &rows) override;

};

class FirstFill : public UpdateStrategy
{
    void apply(QSqlTableModel* model,
               const QModelIndexList& indexes,
               const QStringList& multi_value, const std::set<int> &columns, const QList<int> &rows) override;

};

class LastFill : public UpdateStrategy
{
    void apply(QSqlTableModel* model,
               const QModelIndexList& indexes,
               const QStringList& multi_value, const std::set<int> &columns, const QList<int> &rows) override;

};

class UpdateStrategyFactory {
public:
    static std::unique_ptr<UpdateStrategy> create(const QString& command);

};


class UpdateExecutor {
public:
    static bool execute(QSqlDatabase db,
                        QSqlTableModel* model,
                        const QModelIndexList& indexes,
                        const UpdateRequeted& req,
                        QString& error, const std::set<int> &columns, const QList<int> &rows);

};
class logicUpdate
{
public:
    logicUpdate();
};

#endif // LOGICUPDATE_H
