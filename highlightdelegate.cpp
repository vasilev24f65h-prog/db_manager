<<<<<<< HEAD
#include "highlightdelegate.h"
#include "qapplication.h"
#include "qdebug.h"
#include <QPainter>

HighlightDelegate::HighlightDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
    , m_searchText("")  // Инициализируем пустой строкой
{
}

void HighlightDelegate::setSearchText(const QString &text)
{
    m_searchText = text;
}

void HighlightDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                              const QModelIndex &index) const
{
    // Сохраняем состояние painter
    painter->save();

    // Получаем данные ячейки
    QString cellText = index.data(Qt::DisplayRole).toString();
    bool isSelected = option.state & QStyle::State_Selected;
    bool hasFocus = option.state & QStyle::State_HasFocus;
    bool hasSearchMatch = !m_searchText.isEmpty() &&
                          cellText.contains(m_searchText, Qt::CaseInsensitive);
    // Настройка фона
    QStyleOptionViewItem opt = option;
    if (isSelected) {
        // Ячейка выделена - используем стандартный цвет выделения
        painter->fillRect(opt.rect, opt.palette.brush(QPalette::Highlight));
    }
    else if (hasSearchMatch) {
        // Ячейка не выделена, но содержит искомый текст
        painter->fillRect(opt.rect, QColor(50, 200, 50)); // Зеленый фон

        // Рисуем рамку для выделения
        painter->setPen(QPen(QColor(80, 200, 80), 1));
        painter->drawRect(opt.rect.adjusted(0, 0, -1, -1));
    }
    else {
        // Обычная ячейка - рисуем стандартный фон
        painter->fillRect(opt.rect, opt.palette.brush(QPalette::Base));
    }

    // Рисуем текст
    if (!cellText.isEmpty()) {
        QRect textRect = opt.rect.adjusted(4, 2, -4, -2); // Отступы для текста

        // Устанавливаем цвет текста
        if (!m_searchText.isEmpty() && cellText.contains(m_searchText, Qt::CaseInsensitive)) {
            painter->setPen(Qt::black);
        } else {
            painter->setPen(opt.palette.color(QPalette::Text));
        }

        // Выравнивание текста
        painter->drawText(textRect, opt.displayAlignment, cellText);
    }
    // Восстанавливаем состояние painter
    painter->restore();
}
=======
#include "highlightdelegate.h"
#include "qapplication.h"
#include "qdebug.h"
#include <QPainter>

HighlightDelegate::HighlightDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
    , m_searchText("")  // Инициализируем пустой строкой
{
}

void HighlightDelegate::setSearchText(const QString &text)
{
    m_searchText = text;
}

void HighlightDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                              const QModelIndex &index) const
{
    // Сохраняем состояние painter
    painter->save();

    // Получаем данные ячейки
    QString cellText = index.data(Qt::DisplayRole).toString();
    bool isSelected = option.state & QStyle::State_Selected;
    bool hasFocus = option.state & QStyle::State_HasFocus;
    bool hasSearchMatch = !m_searchText.isEmpty() &&
                          cellText.contains(m_searchText, Qt::CaseInsensitive);
    // Настройка фона
    QStyleOptionViewItem opt = option;
    if (isSelected) {
        // Ячейка выделена - используем стандартный цвет выделения
        painter->fillRect(opt.rect, opt.palette.brush(QPalette::Highlight));
    }
    else if (hasSearchMatch) {
        // Ячейка не выделена, но содержит искомый текст
        painter->fillRect(opt.rect, QColor(50, 200, 50)); // Зеленый фон

        // Рисуем рамку для выделения
        painter->setPen(QPen(QColor(80, 200, 80), 1));
        painter->drawRect(opt.rect.adjusted(0, 0, -1, -1));
    }
    else {
        // Обычная ячейка - рисуем стандартный фон
        painter->fillRect(opt.rect, opt.palette.brush(QPalette::Base));
    }

    // Рисуем текст
    if (!cellText.isEmpty()) {
        QRect textRect = opt.rect.adjusted(4, 2, -4, -2); // Отступы для текста

        // Устанавливаем цвет текста
        if (!m_searchText.isEmpty() && cellText.contains(m_searchText, Qt::CaseInsensitive)) {
            painter->setPen(Qt::black);
        } else {
            painter->setPen(opt.palette.color(QPalette::Text));
        }

        // Выравнивание текста
        painter->drawText(textRect, opt.displayAlignment, cellText);
    }
    // Восстанавливаем состояние painter
    painter->restore();
}
>>>>>>> origin/main
