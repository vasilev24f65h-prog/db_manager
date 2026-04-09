
#ifndef HIGHLIGHTDELEGATE_H
#define HIGHLIGHTDELEGATE_H
#include <QString>
#include <QStyledItemDelegate>
class HighlightDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit HighlightDelegate(QObject *parent = nullptr);

    void setSearchText(const QString &text);

protected:
    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const override;

private:
    QString m_searchText;
};

#endif // HIGHLIGHTDELEGATE_H

