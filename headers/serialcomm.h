#ifndef SERIALCOMM_H
#define SERIALCOMM_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDir>
#include <QDebug>

class SerialComm : public QObject
{
    Q_OBJECT

public:
    explicit SerialComm(QObject *parent = nullptr);

    bool autoConnect();
    bool openPort(const QString &portName);
    void closePort();
    void sendData(const QString &data);
    bool isOpen() const;

    QByteArray readAllBytes();
    QSerialPort* getSerial() const { return serial; }

    QSerialPort *serial;
    QByteArray buffer;


signals:
    void dataReceived(const QString &data);

private slots:
    void readData();
};

#endif
