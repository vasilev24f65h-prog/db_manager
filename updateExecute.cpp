<<<<<<< HEAD
#include "logicupdate.h"

bool UpdateExecutor::execute(QSqlDatabase db,
                             QSqlTableModel* model,
                             const QModelIndexList& indexes,
                             const UpdateRequeted& req,
                             QString& error, const std::set<int> &columns, const QList<int> &rows)
{
    auto strategy = UpdateStrategyFactory::create(req.command);

    db.transaction();

    strategy->apply(model, indexes, req.multi_value, columns, rows);

    if (model->submitAll()) {
        db.commit();
        return true;
    } else {
        db.rollback();
        error = model->lastError().text();
        return false;
    }
}
std::unique_ptr<UpdateStrategy> UpdateStrategyFactory::create(const QString& command)
{
    if (command == "cycle")
        return std::make_unique<Cycle>();
    if (command == "fst")
        return std::make_unique<FirstFill>(); // временно
    if (command == "lst")
        return std::make_unique<LastFill>();
    if (command == "def")
        return std::make_unique<Defoult>();

    return std::make_unique<Defoult>();
}
=======
#include "logicupdate.h"

bool UpdateExecutor::execute(QSqlDatabase db,
                             QSqlTableModel* model,
                             const QModelIndexList& indexes,
                             const UpdateRequeted& req,
                             QString& error, const std::set<int> &columns, const QList<int> &rows)
{
    auto strategy = UpdateStrategyFactory::create(req.command);

    db.transaction();

    strategy->apply(model, indexes, req.multi_value, columns, rows);

    if (model->submitAll()) {
        db.commit();
        return true;
    } else {
        db.rollback();
        error = model->lastError().text();
        return false;
    }
}
std::unique_ptr<UpdateStrategy> UpdateStrategyFactory::create(const QString& command)
{
    if (command == "cycle")
        return std::make_unique<Cycle>();
    if (command == "fst")
        return std::make_unique<FirstFill>(); // временно
    if (command == "lst")
        return std::make_unique<LastFill>();
    if (command == "def")
        return std::make_unique<Defoult>();

    return std::make_unique<Defoult>();
}
>>>>>>> origin/main
