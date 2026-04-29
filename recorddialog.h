#ifndef RECORDDIALOG_H
#define RECORDDIALOG_H


#include "qabstractitemmodel.h"
#include "qgroupbox.h"
#include "qsqlrecord.h"
#include <QObject>
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QRadioButton>
#include <QDialogButtonBox>
#include <QFormLayout>
enum RadioButtonState
{
    Insert,
    Update,
    Delete,
    None = -1
};
struct QueryTab;
class RecordDialog : public QDialog
{
public:
    RecordDialog(const QSqlRecord &record,
                 QueryTab *tab, bool isView,
                 QWidget *parent = nullptr);
    void BuildForm();
    int getRadioState();
    QString join_placeholders();
    QString join_fieldNames();
    QString join_commit();
    int size_editors();
    QWidget* get_editors(int index);
    QVariant get_record_value(QString &name);
private:
    QVector<QWidget*> editors;
    QStringList fieldNames;
    QStringList placeholders;
    QStringList commit;
    QModelIndex index;
    int row;
    QSqlRecord m_record;
    QueryTab *m_tab;
    QVBoxLayout *mainLayout;
    QLabel *title;
    QScrollArea *scroll;
    QWidget *container;
    QVBoxLayout *containerLayout;
    QGroupBox *group;
    QRadioButton *insert;
    QRadioButton *update;
    QRadioButton *delete_btn;
    QFormLayout *form;
    QButtonGroup *groupBtn;
    QDialogButtonBox *btn;
    QHBoxLayout *radioLayout;
};

#endif // RECORDDIALOG_H
