#include "serialcomm.h"
#include <QThread>

SerialComm::SerialComm(QObject *parent)
    : QObject(parent)
{
    serial = new QSerialPort(this);
    connect(serial, &QSerialPort::readyRead, this, &SerialComm::readData);
}

bool SerialComm::autoConnect()
{
#ifdef Q_OS_WIN
    QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : ports) {
        if (openPort(info.portName()))
            return true;
    }
#else
    QDir devDir("/dev");
    QStringList ports = devDir.entryList(QStringList() << "ttyUSB*" << "ttyACM*",
                                         QDir::System | QDir::Readable);

    for (const QString &port : ports) {
        if (openPort("/dev/" + port))
            return true;
    }
#endif
    return false;
}

bool SerialComm::openPort(const QString &portName)
{
    serial->setPortName(portName);
    serial->setBaudRate(QSerialPort::Baud9600);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);

    if (serial->open(QIODevice::ReadWrite)) {
        qDebug() << "Porta aberta:" << portName;
        return true;
    }

    qDebug() << "Falha ao abrir porta:" << portName;
    return false;
}

void SerialComm::closePort()
{
    if (serial->isOpen()) {
        serial->close();
        qDebug() << "Porta serial fechada.";
    }
}

void SerialComm::sendData(const QString &data)
{
    if (!serial->isOpen()) {
        qDebug() << "Porta fechada, não é possível enviar.";
        return;
    }

    serial->write(data.toUtf8());
    serial->flush();
}

bool SerialComm::isOpen() const
{
    return serial->isOpen();
}


void SerialComm::readData()
{
    buffer.append(serial->readAll());

    // se não tem \n ainda, espera
    if (!buffer.contains('\n'))
        return;

    QList<QByteArray> linhas = buffer.split('\n');
    buffer = linhas.takeLast();

    for (const QByteArray &linha : linhas)
        emit dataReceived(QString::fromUtf8(linha).trimmed());
}

