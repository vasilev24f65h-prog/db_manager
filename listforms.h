#ifndef LISTFORMS_H
#define LISTFORMS_H

#include <QSqlRecord>
#include <QWidget>

class listforms : public QWidget
{
    Q_OBJECT
public:
    listforms(const QSqlRecord &record,QWidget *parent = nullptr);
    QSqlRecord getRecord();
private:
    QSqlRecord m_record;
signals:
    void sizeChanged();
};

#endif // LISTFORMS_H
