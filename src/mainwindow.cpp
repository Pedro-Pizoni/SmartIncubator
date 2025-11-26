#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "historydialog.h"
#include "aboutdialog.h"
#include "incubatorcontroller.h"

#include <QDir>
#include <QTimer>
#include <QSerialPortInfo>
#include <QMessageBox>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    serialcomm(new SerialComm(this)),
    dataStorage(new DataStorage(this)),
    incubatorController(nullptr),
    firstReadingReceived(false)
{
    ui->setupUi(this);
    setWindowTitle("Smart Incubator 🐣");

    ui->connectionStatusLabel->setText("🔴 Aguardando Arduino...");

    // Conexão Sinal/Slot para receber dados
    connect(serialcomm, &SerialComm::dataReceived,
            this, &MainWindow::updateDisplay);

    // Agendar autoconexão para depois da interface carregar
    QTimer::singleShot(0, this, &MainWindow::autoConnectSerial);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::autoConnectSerial()
{
    bool sucesso = serialcomm->autoConnect();
    if (sucesso) {
        ui->connectionStatusLabel->setText("🟡 Porta aberta. Aguardando dados...");
        qDebug() << "📡 Conexão automática realizada com sucesso!";
    } else {
        ui->connectionStatusLabel->setText("❌ Nenhuma porta encontrada");
        qDebug() << "❌ Falha na conexão automática.";
    }
}

void MainWindow::updateDisplay(const QString &data)
{
    // 1. Filtro de Segurança
    if (!data.startsWith("TEMP:"))
        return;

    QStringList parts = data.split(';');
    if (parts.size() != 2)
        return;

    bool ok1, ok2;
    // Extrai os números ignorando "TEMP:" (5 chars) e "HUM:" (4 chars)
    double temp = parts[0].mid(5).toDouble(&ok1);
    double hum  = parts[1].mid(4).toDouble(&ok2);

    if (!ok1 || !ok2)
        return;
    ui->tempLabel->setText(QString("🌡️ Temperatura: %1 °C").arg(temp, 0, 'f', 1));
    ui->humLabel->setText(QString("💧 Umidade: %1 %").arg(hum, 0, 'f', 1));
    dataStorage->saveData(QString("Temp: %1 | Hum: %2").arg(temp).arg(hum));
    if (!firstReadingReceived)
    {
        firstReadingReceived = true;
        // Cria o controlador apenas agora que temos conexão confirmada
        incubatorController = new IncubatorController(serialcomm->getSerial(), this);

        ui->connectionStatusLabel->setText("🟢 Arduino em operação!");
        qDebug() << "🔥 Primeiro pacote recebido. Controlador iniciado!";
    }
    if (incubatorController)
        incubatorController->processData(temp);
}

void MainWindow::on_historyButton_clicked()
{
    HistoryDialog dialog(dataStorage, this);
    dialog.exec();
}

void MainWindow::on_aboutButton_clicked()
{
    AboutDialog dialog(this);
    dialog.exec();
}

void MainWindow::on_saveButton_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(
        this,
        "Salvar histórico",
        QDir::homePath() + "/historico_incubadora.txt",
        "Arquivos de texto (*.txt)"
        );

    if (fileName.isEmpty())
        return;

    if (dataStorage->exportData(fileName)) {
        QMessageBox::information(this,
                                 "Histórico salvo",
                                 "O histórico foi salvo com sucesso!");
    } else {
        QMessageBox::warning(this,
                             "Erro",
                             "Não foi possível salvar o arquivo.");
    }
}

void MainWindow::on_applyTempButton_clicked()
{
    targetTemperature = ui->targetTempSpinBox->value();

    if (incubatorController)
        incubatorController->setTargetTemperature(targetTemperature);

    QMessageBox::information(
        this,
        "Temperatura alvo",
        QString("Nova temperatura alvo: %1 °C").arg(targetTemperature)
        );
}
