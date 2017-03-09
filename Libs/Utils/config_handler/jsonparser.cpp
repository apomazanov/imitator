#include "jsonparser.h"

JsonParser::JsonParser(QObject *parent) : QObject(parent)
{
    jsonConfig.setFileName(configPath);
    if (!jsonConfig.open(QFile::ReadOnly))
    {
        cout << jsonConfig.errorString().toStdString() << endl;
        return;
    }

    QJsonDocument document = QJsonDocument::fromJson(jsonConfig.readAll());
    QJsonObject root = document.object();
    for (int i = 0; i < root.keys().count(); i++)
    {
        QString rootKey = root.keys().at(i);
        QString str = rootKey;
        if (root.value(rootKey).isString())
        {
            str += " = string";
            paramSimpleString[rootKey] = root.value(rootKey).toString();
        }
        if (root.value(rootKey).isArray())
        {
            str += " = array";

            if (rootKey.compare("TARGETS") && rootKey.compare("TABLE_SIGNAL"))
            {
                // List of QMaps
                QJsonArray jsonArray1 = root.value(rootKey).toArray();
                QList<QMap<QString, double>> listOfMaps;

                for (int j = 0; j < jsonArray1.count(); j++)
                {
                    // QMaps
                    QJsonObject jObj = jsonArray1[j].toObject();
                    QMap<QString, double> simpleMap;
                    for (int k = 0; k < jObj.keys().count(); k++)
                    {
                        QString tempKey = jObj.keys().at(k);
                        simpleMap[tempKey] = jObj.value(tempKey).toDouble();
                    }
                    listOfMaps.append(simpleMap);
                }
                paramSimpleArray[rootKey] = listOfMaps;
            }
        }
        if (root.value(rootKey).isDouble())
        {
            str += " = double";
            paramSimpleDouble[rootKey] = root.value(rootKey).toDouble();
        }
        cout << str.toStdString() << endl;
    }
    cout << "\n";
}
