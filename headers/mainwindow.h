#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "serialcomm.h"
#include "datastorage.h"
#include "incubatorcontroller.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void updateDisplay(const QString &data);
    void on_historyButton_clicked();
    void on_aboutButton_clicked();
    void on_saveButton_clicked();
    void on_applyTempButton_clicked();
    void autoConnectSerial();

private:
    Ui::MainWindow *ui;

    SerialComm *serialcomm;
    DataStorage *dataStorage;
    IncubatorController *incubatorController;

    double targetTemperature = 37.5;
    bool firstReadingReceived = false;
};

#endif
