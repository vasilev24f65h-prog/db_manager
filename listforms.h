#ifndef LISTFORMS_H
#define LISTFORMS_H

#include <QSqlRecord>
#include <QWidget>

class listforms : public QWidget
{
    Q_OBJECT
public:
    listforms(const QSqlRecord &record,QWidget *parent = nullptr);

signals:
    void sizeChanged();
};

#endif // LISTFORMS_H
