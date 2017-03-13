#include "paramsraw.h"

ParamsRaw::ParamsRaw(QObject *parent, QString configFilePath) : QObject(parent)
{
    parser = new JsonParser(0, configFilePath);
}

QList<QString> ParamsRaw::getParam(QString paramName, QString confirm)
{
    if ((!paramName.compare("TABLE_SIGNAL")) && (!paramName.compare(confirm)))
    {
        return parser->paramTableSignal.value(paramName);
    }
    else
    {
        QList<QString> empty;
        empty.append("-1");
        return empty;
    }
}

QString ParamsRaw::getParam(QString kitName, int pos, QString paramName)
{
    foreach (QString rootKey, parser->paramsComplex.keys()) {
        if (!rootKey.compare(kitName)){
            if (parser->paramsComplex.value(kitName).count() < (pos + 1))
                // Неверно указан номер элемента в комплекте
                return "-2";
            else
            {
                foreach (QString key, parser->paramsComplex.value(kitName)[pos].keys()) {
                    if (!key.compare(paramName))
                        return parser->paramsComplex.value(kitName)[pos].value(key);
                }
                // Нет нужного параметра в элементе комплекта
                return "-3";
            }
        }
    }
    // kitName error
    return "-1";
}

int ParamsRaw::getArraySize(QString kitName)
{
    foreach (QString rootKey, parser->paramsComplex.keys()) {
        if (!rootKey.compare(kitName))
            return parser->paramsComplex.value(kitName).count();
    }
    return -1;
}

QMap<QString, QString> ParamsRaw::getItemFromArray(QString kitName, int pos)
{
    QMap<QString, QString> empty;
    empty["-1"] = "-1";
    foreach (QString rootkey, parser->paramsComplex.keys()) {
        if (!rootkey.compare(kitName)){
            if (parser->paramsComplex.value(kitName).count() < (pos + 1))
                return empty;
            else
                return parser->paramsComplex.value(kitName)[pos];
        }
    }
    return empty;
}

QString ParamsRaw::getParam(QString paramName)
{
    foreach (QString key, parser->paramsSimple.keys()) {
        if (!key.compare(paramName))
            return parser->paramsSimple.value(key);
    }

    return "-1";
}
