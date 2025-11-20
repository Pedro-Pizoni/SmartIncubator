#ifndef HISTORYDIALOG_H
#define HISTORYDIALOG_H

#include <QDialog>
#include <QStringList>
#include <QTextEdit>
#include "datastorage.h"

QT_BEGIN_NAMESPACE
namespace Ui { class HistoryDialog; }
QT_END_NAMESPACE

class HistoryDialog : public QDialog
{
    Q_OBJECT

public:
    explicit HistoryDialog(DataStorage *storage, QWidget *parent = nullptr);
    ~HistoryDialog();

private slots:
    void on_clearButton_clicked();
    void on_closeButton_clicked();
private:
    Ui::HistoryDialog *ui;
    DataStorage *dataStorage;
    void loadHistory();
};

#endif
