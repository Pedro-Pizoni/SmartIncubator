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

bool DataStorage::exportData(const QString &fileName)
{
    QFile file(fileName);

    // Tenta criar/sobrescrever o arquivo escolhido
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return false; // Deu erro
    }

    QTextStream out(&file);

    // Reutiliza sua própria função de ler tudo!
    QStringList registros = readAllData();

    if (registros.isEmpty()) {
        out << "Nenhum dado registrado ainda.\n";
    } else {
        for (const QString &linha : registros)
            out << linha << "\n";
    }

    file.close();
    return true; // Sucesso
}
