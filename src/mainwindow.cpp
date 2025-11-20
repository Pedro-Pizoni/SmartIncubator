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

    // Sempre que chegar uma linha pronta da serial
    connect(serialcomm, &SerialComm::dataReceived,
            this, &MainWindow::updateDisplay);

    // Autoconexão ao iniciar
    QTimer::singleShot(0, this, &MainWindow::autoConnectSerial);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::autoConnectSerial() // auto conect
{
    QString portName;

    QDir devDir("/dev");
    QStringList ports = devDir.entryList(
        {"ttyUSB*", "ttyACM*"},
        QDir::System | QDir::Readable
        );

    if (!ports.isEmpty())
        portName = "/dev/" + ports.first();

    if (portName.isEmpty()) {
        ui->connectionStatusLabel->setText("❌ Nenhum Arduino encontrado");
        return;
    }

    if (serialcomm->openPort(portName)) {
        ui->connectionStatusLabel->setText("🟡 Porta aberta. Aguardando dados...");
        qDebug() << "📡 Porta aberta em:" << portName;
    } else {
        ui->connectionStatusLabel->setText("❌ Falha ao abrir porta");
    }
}
void MainWindow::updateDisplay(const QString &data)
{
    if (!data.startsWith("TEMP:"))
        return;

    QStringList parts = data.split(';');
    if (parts.size() != 2)
        return;

    bool ok1, ok2;
    double temp = parts[0].mid(5).toDouble(&ok1);
    double hum  = parts[1].mid(4).toDouble(&ok2);

    if (!ok1 || !ok2)
        return;
    ui->tempLabel->setText(QString("🌡️ Temperatura: %1 °C").arg(temp, 0, 'f', 1)); // atualiza a interface
    ui->humLabel->setText(QString("💧 Umidade: %1 %").arg(hum, 0, 'f', 1));

    dataStorage->saveData(QString("Temp: %1 | Hum: %2").arg(temp).arg(hum));
    if (!firstReadingReceived)
    {
        firstReadingReceived = true;

        incubatorController =
            new IncubatorController(serialcomm->getSerial(), this);

        ui->connectionStatusLabel->setText("🟢 Arduino em operação!");
        qDebug() << "🔥 Primeiro pacote recebido. Controlador iniciado!";
    }
    if (incubatorController)
        incubatorController->processData(data);
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

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Erro", "Não foi possível salvar o arquivo.");
        return;
    }

    QTextStream out(&file);
    QStringList registros = dataStorage->readAllData();

    if (registros.isEmpty()) {
        out << "Nenhum dado registrado ainda.\n";
    } else {
        for (const QString &linha : registros)
            out << linha << "\n";
    }

    file.close();

    QMessageBox::information(this,
                             "Histórico salvo",
                             "O histórico foi salvo com sucesso!");
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
