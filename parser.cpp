<<<<<<< HEAD
#include "logicupdate.h"

UpdateRequeted UpdateParse::parseCommand(QString &input)
{
    UpdateRequeted req;
    if (input.startsWith(':')) {
        QString temp = input.mid(1);
        req.command = temp.section(' ', 0, 0);
        input.replace(":"+req.command, "");
    }
    else
    {
        req.command = "def";
    }
    return req;
}
void UpdateParse::setupRowCol(QModelIndexList &indexes, std::set<int> &columns, QList<int> &rows )
{
    std::sort(indexes.begin(), indexes.end(), [](const QModelIndex &a, const QModelIndex &b) {
        if (a.row() == b.row())
            return a.column() < b.column();
        return a.row() < b.row();
    });

    qDebug() << "Selected count:" << indexes.size();

    for (const auto &index : std::as_const(indexes))
    {
        rows.append(index.row());
    }

    std::sort(rows.begin(), rows.end());

    for (const auto &index : std::as_const(indexes))
    {
        columns.insert(index.column());
    }
}
void UpdateParse::parseData(QString &upd_data, std::set<int> &columns, UpdateRequeted &req)
{
    std::vector<int> vec_count_val{};
    std::vector<int> vec_index_val{};
    std::vector<QString> vec_qstr{};
    if(columns.size()>1)
    {
        QString current;
        int bracketLevel = 0;

        for (QChar ch : std::as_const(upd_data))
        {
            if (ch == '(')
                ++bracketLevel;
            else if (ch == ')')
                --bracketLevel;

            if (ch == ',' && bracketLevel == 0)
            {
                req.multi_value.append(current.trimmed());
                current.clear();
            }
            else
            {
                current += ch;
            }
        }

        // добавить последний элемент
        if (!current.isEmpty())
            req.multi_value.append(current.trimmed());
        QVector<QVector<QString>> groups;
        QVector<int> counts;

        static const  QRegularExpression re("\\(?([^\\)]*)\\)?\\s*(?:\\*\\s*(\\d+))?");

        for (QString val : std::as_const(req.multi_value))
        {
            val = val.trimmed();

            QRegularExpressionMatch match = re.match(val);

            if (match.hasMatch())
            {
                QString inside = match.captured(1);
                QString countStr = match.captured(2);

                int count = countStr.isEmpty() ? 1 : countStr.toInt();

                QVector<QString> group;

                for (QString item : inside.split(',', Qt::SkipEmptyParts))
                {
                    group.push_back(item.trimmed());
                }

                groups.push_back(group);
                counts.push_back(count);
            }
        }
        QStringList result;

        for (int g = 0; g < groups.size(); ++g)
        {
            for (int i = 0; i < counts[g]; ++i)
            {
                for (QString& val : groups[g])
                {
                    result.push_back(val);
                }
            }
        }
        req.multi_value = result;
    }
    else {
        req.multi_value = upd_data.split(',');
        int pos = 0;

        static const QRegularExpression re("^\\(([^\\)]*)\\)\\s*\\*\\s*(\\d+)$"); // скобки + *N

        for (QString &val : req.multi_value) {
            val = val.trimmed();

            QRegularExpressionMatch match = re.match(val);
            if (match.hasMatch()) {
                // Разбираем значения внутри скобок
                val = match.captured(1);
                int count = match.captured(2).toInt();

                QString cleaned = val.trimmed();
                vec_qstr.push_back(cleaned);
                vec_count_val.push_back(count);
                vec_index_val.push_back(pos);

                ++pos;
            } else {
                // Одиночное значение или скобки без *N
                vec_qstr.push_back(val);
                vec_count_val.push_back(1);
                vec_index_val.push_back(pos);
                ++pos;
            }
        }

        // разворачиваем повторения
        for (int i = 0; i < vec_count_val.size(); ++i) {
            int count = vec_count_val[i];
            for (int j = 1; j < count; ++j) {
                int pos = vec_index_val[i];
                req.multi_value.insert(pos + 1, vec_qstr[i]);
            }
        }
    }
}
=======
#include "logicupdate.h"

UpdateRequeted UpdateParse::parseCommand(QString &input)
{
    UpdateRequeted req;
    if (input.startsWith(':')) {
        QString temp = input.mid(1);
        req.command = temp.section(' ', 0, 0);
        input.replace(":"+req.command, "");
    }
    else
    {
        req.command = "def";
    }
    return req;
}
void UpdateParse::setupRowCol(QModelIndexList &indexes, std::set<int> &columns, QList<int> &rows )
{
    std::sort(indexes.begin(), indexes.end(), [](const QModelIndex &a, const QModelIndex &b) {
        if (a.row() == b.row())
            return a.column() < b.column();
        return a.row() < b.row();
    });

    qDebug() << "Selected count:" << indexes.size();

    for (const auto &index : std::as_const(indexes))
    {
        rows.append(index.row());
    }

    std::sort(rows.begin(), rows.end());

    for (const auto &index : std::as_const(indexes))
    {
        columns.insert(index.column());
    }
}
void UpdateParse::parseData(QString &upd_data, std::set<int> &columns, UpdateRequeted &req)
{
    std::vector<int> vec_count_val{};
    std::vector<int> vec_index_val{};
    std::vector<QString> vec_qstr{};
    if(columns.size()>1)
    {
        QString current;
        int bracketLevel = 0;

        for (QChar ch : std::as_const(upd_data))
        {
            if (ch == '(')
                ++bracketLevel;
            else if (ch == ')')
                --bracketLevel;

            if (ch == ',' && bracketLevel == 0)
            {
                req.multi_value.append(current.trimmed());
                current.clear();
            }
            else
            {
                current += ch;
            }
        }

        // добавить последний элемент
        if (!current.isEmpty())
            req.multi_value.append(current.trimmed());
        QVector<QVector<QString>> groups;
        QVector<int> counts;

        static const  QRegularExpression re("\\(?([^\\)]*)\\)?\\s*(?:\\*\\s*(\\d+))?");

        for (QString val : std::as_const(req.multi_value))
        {
            val = val.trimmed();

            QRegularExpressionMatch match = re.match(val);

            if (match.hasMatch())
            {
                QString inside = match.captured(1);
                QString countStr = match.captured(2);

                int count = countStr.isEmpty() ? 1 : countStr.toInt();

                QVector<QString> group;

                for (QString item : inside.split(',', Qt::SkipEmptyParts))
                {
                    group.push_back(item.trimmed());
                }

                groups.push_back(group);
                counts.push_back(count);
            }
        }
        QStringList result;

        for (int g = 0; g < groups.size(); ++g)
        {
            for (int i = 0; i < counts[g]; ++i)
            {
                for (QString& val : groups[g])
                {
                    result.push_back(val);
                }
            }
        }
        req.multi_value = result;
    }
    else {
        req.multi_value = upd_data.split(',');
        int pos = 0;

        static const QRegularExpression re("^\\(([^\\)]*)\\)\\s*\\*\\s*(\\d+)$"); // скобки + *N

        for (QString &val : req.multi_value) {
            val = val.trimmed();

            QRegularExpressionMatch match = re.match(val);
            if (match.hasMatch()) {
                // Разбираем значения внутри скобок
                val = match.captured(1);
                int count = match.captured(2).toInt();

                QString cleaned = val.trimmed();
                vec_qstr.push_back(cleaned);
                vec_count_val.push_back(count);
                vec_index_val.push_back(pos);

                ++pos;
            } else {
                // Одиночное значение или скобки без *N
                vec_qstr.push_back(val);
                vec_count_val.push_back(1);
                vec_index_val.push_back(pos);
                ++pos;
            }
        }

        // разворачиваем повторения
        for (int i = 0; i < vec_count_val.size(); ++i) {
            int count = vec_count_val[i];
            for (int j = 1; j < count; ++j) {
                int pos = vec_index_val[i];
                req.multi_value.insert(pos + 1, vec_qstr[i]);
            }
        }
    }
}
>>>>>>> origin/main
