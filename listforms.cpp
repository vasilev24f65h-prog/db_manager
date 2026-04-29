#include "listforms.h"
#include "qboxlayout.h"
#include "qdatetime.h"
#include "qdebug.h"
#include "qformlayout.h"
#include "qlabel.h"
#include "qpushbutton.h"
#include "qvariant.h"

listforms::listforms(const QSqlRecord &record, QWidget *parent)
    : QWidget(parent)
{
    qDebug() << "record.count =" << record.count();
    m_record = record;
    for (int i = 0; i < m_record.count(); ++i)
    {
        qDebug() << m_record.fieldName(i) << m_record.value(i);
    }

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(5);
    QString title = "Exemple title";

    QPushButton *header = new QPushButton("▶ " + title);
    header->setCheckable(true);
    header->setMinimumHeight(30);
    QWidget *details = new QWidget;
    QFormLayout *form = new QFormLayout(details);
    for (int i = 0; i < m_record.count(); ++i)
    {
        QString name = m_record.fieldName(i);
        QVariant value = m_record.value(i);
        form->addRow(name, new QLabel(value.toString()));
    }

    details->setVisible(false);

    connect(header, &QPushButton::toggled, [=](bool checked){
        details->setVisible(checked);
        header->setText((checked ? "▼ " : "▶ ") + title);
        adjustSize();
        emit sizeChanged();
    });

    mainLayout->addWidget(header);
    mainLayout->addWidget(details);
}

QSqlRecord listforms::getRecord()
{
    return m_record;
}
