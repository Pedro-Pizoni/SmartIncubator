#include "datastorage.h"

DataStorage::DataStorage(QObject *parent)
    : QObject(parent)
{
    filePath = "dados_incubadora.txt";
}

void DataStorage::saveData(const QString &data)
{
    QFile file(filePath);
    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        qWarning() << "Não foi possível abrir o arquivo para salvar os dados.";
        return;
    }

    QTextStream out(&file);
    out << data << "\n";
    file.close();
}

QStringList DataStorage::readAllData()
{
    QStringList lines;
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Não foi possível abrir o arquivo para leitura.";
        return lines;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (!line.isEmpty())
            lines.append(line);
    }

    file.close();
    return lines;
}

void DataStorage::clearData()
{
    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        file.close();
        qDebug() << "Histórico limpo com sucesso!";
    } else {
        qWarning() << "Falha ao limpar o histórico.";
    }
}
