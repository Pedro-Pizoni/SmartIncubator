#include "incubatorcontroller.h"
#include <QtMath>

IncubatorController::IncubatorController(QSerialPort *port, QObject *parent)
    : QObject(parent), serialPort(port), targetTemperature(37.5)
{
}

void IncubatorController::processData(double tempAtual)
{
    if (!serialPort || !serialPort->isOpen())
        return;

    double erro = targetTemperature - tempAtual;
    double brilhoCalc = 0;

    static bool lampOn = false;
    double histerese = 0.3;

    if (erro > histerese) {
        lampOn = true;
    } else if (erro < -histerese) {
        lampOn = false;
    }

    if (!lampOn) {
        brilhoCalc = 0;
    } else {
        double erroPos = qMax(0.0, erro);
        double k = 0.12;

        brilhoCalc = 255.0 * (1.0 - exp(-k * erroPos));

        if (brilhoCalc < 0) brilhoCalc = 0;
        if (brilhoCalc > 255) brilhoCalc = 255;
    }

    int brilhoFinal = static_cast<int>(brilhoCalc);

    QString comando = QString("DIM:%1\n").arg(brilhoFinal);
    serialPort->write(comando.toUtf8());
    serialPort->flush();

    // Debug log for monitoring the control loop behavior (temperature, error, lamp state, PWM).
    // Useful during calibration, testing, and troubleshooting.
    // Keep commented in production to avoid console clutter. Uncomment when detailed runtime
    // diagnostics are needed.
    // qDebug() << "TEMP:" << tempAtual
    //          << "| ERRO:" << erro
    //          << "| LampOn:" << lampOn
    //          << "| Brilho:" << brilhoFinal;
}

void IncubatorController::setTargetTemperature(double target)
{
    targetTemperature = target;
}
