#include "recorddialog.h"
#include "mainwindow.h"

RecordDialog::RecordDialog(const QSqlRecord &record, QueryTab *tab, bool isView, QWidget *parent) : QDialog(parent)
{

    setWindowTitle("Карточка записи");
    resize(500, 400);

    mainLayout = new QVBoxLayout(this);

    title = new QLabel("Карточка записи");
    title->setStyleSheet("font-size: 18px; font-weight: bold;");
    title->setAlignment(Qt::AlignCenter);

    mainLayout->addWidget(title);

    scroll = new QScrollArea;
    scroll->setWidgetResizable(true);

    container = new QWidget(this);
    containerLayout = new QVBoxLayout(container);

    group = new QGroupBox("Основная информация");
    insert = new QRadioButton("Вставка");
    update = new QRadioButton("Обновление");
    delete_btn = new QRadioButton("Удаление");
    form = new QFormLayout(group);
    groupBtn = new QButtonGroup(this);
    groupBtn->addButton(insert,Insert);
    groupBtn->addButton(update, Update);
    groupBtn->addButton(delete_btn, Delete);
    radioLayout = new QHBoxLayout;

    radioLayout->addWidget(insert);
    radioLayout->addWidget(update);
    radioLayout->addWidget(delete_btn);

    btn = new QDialogButtonBox(QDialogButtonBox::Save | QDialogButtonBox::Cancel);

    QObject::connect(btn, &QDialogButtonBox::accepted, this, &QDialog::accept);
    QObject::connect(btn, &QDialogButtonBox::rejected, this, &QDialog::reject);
    scroll->setWidget(container);
    containerLayout->addWidget(group);
    containerLayout->addLayout(radioLayout);
    containerLayout->addWidget(btn);
    mainLayout->addWidget(scroll);
    index = tab->table->currentIndex();
    row = index.row();
    m_record = record;
    m_tab = tab;
    qDebug() << "ROW =" << index.row();
    BuildForm();
}

void RecordDialog::BuildForm()
{
    for (int i = 0; i < m_record.count(); ++i)
    {
        QSqlField field = m_record.field(i);
        QString fieldName = field.name();

        QLabel *label = new QLabel(fieldName);
        label->setStyleSheet("font-weight: bold;");

        QWidget *editor = nullptr;
        QVariant value = m_record.value(i);
        if (field.type() == QVariant::Date) {
            QDateEdit *dateEdit = new QDateEdit;
            dateEdit->setCalendarPopup(true);
            if (value.isValid())
                dateEdit->setDate(value.toDate());
            editor = dateEdit;
        }
        else if (field.type() == QVariant::Int) {
            QSpinBox *spin = new QSpinBox;
            spin->setRange(INT_MIN, INT_MAX);
            if (value.isValid())
                spin->setValue(value.toInt());

            editor = spin;
        }
        else if (field.type() == QVariant::Double) {
            QDoubleSpinBox *dspin = new QDoubleSpinBox;
            dspin->setRange(-1e12, 1e12);
            if (value.isValid())
                dspin->setValue(value.toDouble());
            editor = dspin;
        }
        else if (field.type() == QVariant::Bool) {
            QCheckBox *cbox = new QCheckBox;
            if(value.isValid())
                cbox->setChecked(value.toBool());
            editor = cbox;
        }
        else {
            QLineEdit *lineEdit = new QLineEdit;

            if (value.isValid())
                lineEdit->setText(value.toString());

            lineEdit->setPlaceholderText("Введите " + field.name());

            editor = lineEdit;

        }

        editors.push_back(editor);
        fieldNames << fieldName;
        placeholders << QString(":v%1").arg(i);
        commit << fieldName + " = " + placeholders[i];
        form->addRow(label, editor);
    }
}
int RecordDialog::getRadioState()
{
    return groupBtn->checkedId();
}

QString RecordDialog::join_placeholders()
{
    return placeholders.join(", ");
}
QString RecordDialog::join_fieldNames()
{
    return fieldNames.join(", ");
}
QString RecordDialog::join_commit()
{
    return commit.join(", ");
}
int RecordDialog::size_editors()
{
    return editors.size();
}
QWidget* RecordDialog::get_editors(int index)
{
    return editors[index];
}
QVariant RecordDialog::get_record_value(QString &name)
{
    return m_record.value(name);
}
