#ifndef DATASTORAGE_H
#define DATASTORAGE_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QFile>
#include <QTextStream>
#include <QDebug>

class DataStorage : public QObject
{
    Q_OBJECT

public:
    explicit DataStorage(QObject *parent = nullptr);

    void saveData(const QString &data);
    QStringList readAllData();
    void clearData();



private:
    QString filePath;
};

#endif
