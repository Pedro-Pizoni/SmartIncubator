#ifndef INCUBATORCONTROLLER_H
#define INCUBATORCONTROLLER_H

#include <QObject>
#include <QSerialPort>
#include <QString>
#include <QDebug>

class IncubatorController : public QObject
{
    Q_OBJECT

public:
    explicit IncubatorController(QSerialPort *port, QObject *parent = nullptr);

    void processData(const QString &data);
    void setTargetTemperature(double target);

private:
    QSerialPort *serialPort;
    double targetTemperature;
};

#endif
