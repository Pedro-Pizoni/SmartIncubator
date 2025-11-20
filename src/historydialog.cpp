#include "historydialog.h"
#include "ui_historydialog.h"
#include <QMessageBox>

HistoryDialog::HistoryDialog(DataStorage *storage, QWidget *parent)
    : QDialog(parent),
    ui(new Ui::HistoryDialog),
    dataStorage(storage)
{
    ui->setupUi(this);
    setWindowTitle("📜 Histórico de Dados");
    setModal(true);
    ui->historyTextEdit->setStyleSheet(
        "QTextEdit { background-color: #1E1E1E; color: #FFFFFF; font: 12pt 'Segoe UI'; }");

    loadHistory();

}

HistoryDialog::~HistoryDialog()
{
    delete ui;
}

void HistoryDialog::loadHistory()
{
    ui->historyTextEdit->clear();

    if (!dataStorage)
        return;

    QStringList allData = dataStorage->readAllData();
    for (const QString &line : allData) {
        ui->historyTextEdit->append(line);
    }
}

void HistoryDialog::on_clearButton_clicked()
{
    if (dataStorage) {
        dataStorage->clearData();
    }
    ui->historyTextEdit->clear();
    QMessageBox::information(this, "Histórico", "O histórico foi limpo com sucesso!");
}
void HistoryDialog::on_closeButton_clicked()
{
    accept();
}
