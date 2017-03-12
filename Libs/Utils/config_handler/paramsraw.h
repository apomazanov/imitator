#ifndef PARAMSRAW_H
#define PARAMSRAW_H

#include <QObject>
#include "jsonparser.h"

class ParamsRaw : public QObject
{
    Q_OBJECT
public:
    explicit ParamsRaw(QObject *parent = 0, QString configFilePath = DEFAULTPATH);

    // Для TABLE_SIGNAL
    QList<QString> getParam(QString paramName, QString confirm);
    // Для составных параметров
    QString getParam(QString kitName, int pos, QString paramName);
    int getArraySize(QString kitName);
    // Для простых параметров
    QString getParam(QString paramName);

private:
    JsonParser *parser;
};

#endif // PARAMSRAW_H
