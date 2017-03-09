#ifndef JSONPARSER_H
#define JSONPARSER_H

#include <QObject>
#include <iostream>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QMap>
#include <QList>
using namespace std;

class JsonParser : public QObject
{
    Q_OBJECT
public:
    explicit JsonParser(QObject *parent = 0);

    /**************************************************************************
     * QMaps для параметров из JSON
     **************************************************************************/
    // Для строковых параметров
    QMap<QString, QString> paramSimpleString;
    // Для простых параметров double
    QMap<QString, double> paramSimpleDouble;
    // Для "списков списков" пар параметр:значение
    QMap<QString, QList<QMap<QString, double>>> paramSimpleArray;
    // Для TARGETS
    QMap<QString, QList<QMap<QString, double>>> paramTargetsArray;
    // Для TABLE_SIGNAL
    QMap<QString, QList<double>> paramTableSignalArray;

private:
    QFile jsonConfig;
    QString configPath = QString("./../../../config.json");

};

#endif // JSONPARSER_H
