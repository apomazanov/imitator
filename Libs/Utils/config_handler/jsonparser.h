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

#ifndef DEFAULTPATH
#define DEFAULTPATH  "../../../config.json"
#endif // DEFAULTPATH

class JsonParser : public QObject
{
    Q_OBJECT
public:
    explicit JsonParser(QString configFilePath = DEFAULTPATH);

    /**************************************************************************
     * QMaps для параметров из JSON
     **************************************************************************/
    // Для простых параметров
    QMap<QString, QString> paramsSimple;
    // Для составных параметров
    QMap<QString, QList<QMap<QString, QString>>> paramsComplex;
    // Для TABLE_SIGNAL
    QMap<QString, QList<QString>> paramTableSignal;

private:
    QFile jsonConfig;
};

#endif // JSONPARSER_H
