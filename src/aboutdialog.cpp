#include "aboutdialog.h"
#include "ui_aboutdialog.h"
#include <QDesktopServices>
#include <QUrl>

AboutDialog::AboutDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::AboutDialog)
{
    ui->setupUi(this);
    setWindowTitle("ℹ️ Sobre o Smart Incubator");
    ui->label->setText(
        "<h2>🌡️ Smart Incubator</h2>"
        "<p>Projeto desenvolvido por <b>Pedro Pizoni</b><br>"
        "Engenharia da Computação — 2025</p>"
        "<p>Controle inteligente de temperatura e umidade com Arduino e Qt.</p>"
        );
    connect(ui->githubButton_2, &QPushButton::clicked, this, []() {
        QDesktopServices::openUrl(QUrl("https://github.com/Pedro-Pizoni"));
    });

    connect(ui->youtubeButton, &QPushButton::clicked, this, []() {
        QDesktopServices::openUrl(QUrl("https://youtu.be/Xd1P1qslgvQ"));
    });
    connect(ui->closeButton, &QPushButton::clicked, this, &QDialog::accept);
}

AboutDialog::~AboutDialog()
{
    delete ui;
}
