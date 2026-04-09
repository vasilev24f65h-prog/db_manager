#include "logicupdate.h"

logicUpdate::logicUpdate() {}

void LastFill::apply(QSqlTableModel* model,
           const QModelIndexList& indexes,
           const QStringList& multi_value, const std::set<int> &columns, const QList<int> &rows)
{
    if(columns.size()==1)
    {
        for (int r = (rows.size()-1), i = 0, cnt = rows.size(); (r >= 0)&&(i < multi_value.size()); --r)
        {
            QString value;

            if (cnt >= multi_value.size())
            {
                --cnt;
                value = multi_value[i];
            }
            else
            {
                ++i;
                value = multi_value[i]; // fallback
            }
            for (auto index = indexes.rbegin();index !=indexes.rend();++index)
            {
                if (index->row() == rows[r])
                {
                    model->setData(*index, value);
                    break;
                }
            }
        }
    }
    else
    {
        int cols = columns.size();
        int col = 0;
        int totalRows = rows.size();
        int totalValues = multi_value.size();
        int totalRows_ = totalRows / cols;
        int lstRows = totalRows_ - (totalValues/cols);
        int idx = 0;
        for (auto index = indexes.rbegin();index !=indexes.rend();++index)
        {
            if(idx<totalValues)
            {
                model->setData(*index, multi_value[idx]);
                ++idx;
                ++col;
            }
            if(cols == col)
            {
                if(lstRows != 0)
                {
                    --lstRows;
                    idx = 0;
                }
                col = 0;
            }
        }
    }

}

void FirstFill::apply(QSqlTableModel* model,
           const QModelIndexList& indexes,
           const QStringList& multi_value, const std::set<int> &columns, const QList<int> &rows)
{
    if(columns.size()==1)
    {
        int fillRow = (rows.size()+1)-  multi_value.size();
        for (int r = 0, i = 0; r < rows.size(); ++r)
        {
            QString value;

            if (r < fillRow)
                value = multi_value[0];
            else
            {
                if(i < multi_value.size()-1)
                {
                    ++i;
                }
                value = multi_value[i]; // fallback
            }
            for (const auto &index : std::as_const(indexes))
            {
                if (index.row() == rows[r])
                {
                    model->setData(index, value);
                    break;
                }
            }
        }
    }
    else
    {
        int cols = columns.size();
        int col = 0;
        int totalRows = rows.size();
        int totalValues = multi_value.size();
        int totalRows_ = totalRows / cols;
        int lstRows = totalRows_ - (totalValues/cols);
        int idx = 0;
        for (auto index = indexes.begin();index !=indexes.end();++index)
        {
            if(idx<totalValues)
            {
                model->setData(*index, multi_value[idx]);
                ++idx;
                ++col;
            }
            if(cols == col)
            {
                if(lstRows != 0)
                {
                    --lstRows;
                    idx = 0;
                }
                col = 0;
            }
        }
    }
}

void Defoult::apply(QSqlTableModel* model,
           const QModelIndexList& indexes,
           const QStringList& multi_value, const std::set<int> &columns, const QList<int> &rows)
{
    if(columns.size()==1)
    {
        for (int r = 0; r < rows.size(); ++r)
        {
            model->setData(indexes[r], multi_value[r]);
        }
    }
    else
    {
        for (int i = 0; i < indexes.size() && i < multi_value.size(); ++i)
        {
            model->setData(indexes[i], multi_value[i]);
        }
    }
}

void Cycle::apply(QSqlTableModel* model,
           const QModelIndexList& indexes,
           const QStringList& multi_value, const std::set<int> &columns, const QList<int> &rows)
{
    for (int i = 0; i < indexes.size(); ++i)
    {
        QString value = multi_value[i % multi_value.size()];
        model->setData(indexes[i], value);
    }
}

