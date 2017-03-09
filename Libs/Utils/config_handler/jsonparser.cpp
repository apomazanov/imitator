#include "jsonparser.h"

JsonParser::JsonParser(QObject *parent, QString configFilePath) : QObject(parent)
{
    jsonConfig.setFileName(configFilePath);
    if (!jsonConfig.open(QFile::ReadOnly))
    {
        cout << jsonConfig.errorString().toStdString() << endl;
        return;
    }

    QJsonDocument document = QJsonDocument::fromJson(jsonConfig.readAll());
    jsonConfig.close();
    QJsonObject root = document.object();
    for (int i = 0; i < root.keys().count(); i++)
    {
        QString rootKey = root.keys().at(i);
        QString str = rootKey;
        if (root.value(rootKey).isString())
        {
            str += " = string";
            paramsSimple[rootKey] = root.value(rootKey).toString();
        }
        if (root.value(rootKey).isDouble())
        {
            str += " = double";
            paramsSimple[rootKey] = QString::number(root.value(rootKey).toDouble());
        }
        if (root.value(rootKey).isArray())
        {
            str += " = array";

            if (rootKey.compare("TABLE_SIGNAL"))
            {
                // List of QMaps
                QJsonArray jsonArray = root.value(rootKey).toArray();
                QList<QMap<QString, QString>> listOfMaps;

                for (int j = 0; j < jsonArray.count(); j++)
                {
                    // QMaps
                    QJsonObject jObj = jsonArray[j].toObject();
                    QMap<QString, QString> simpleMap;
                    for (int k = 0; k < jObj.keys().count(); k++)
                    {
                        QString tempKey = jObj.keys().at(k);


                        // TARGETS or not
                        if (jObj[tempKey].isObject())
                        {
                            QJsonObject tObj = jObj[tempKey].toObject();
                            for (int z = 0; z < tObj.keys().count(); z++)
                            {
                                QString oldName = tObj.keys().at(z);
                                QString newName = tempKey + "_" + oldName;
                                simpleMap[newName] = QString::number(tObj.value(oldName).toDouble());
                            }
                        }
                        else
                            simpleMap[tempKey] = QString::number(jObj.value(tempKey).toDouble());
                    }
                    listOfMaps.append(simpleMap);
                }
                paramsComplex[rootKey] = listOfMaps;
            }
            else
            {
                // TABLE_SIGNAL
                // List of strings
                QJsonArray jsonArray = root.value(rootKey).toArray();
                QList<QString> listOfStrings;

                for (int j = 0; j < jsonArray.count(); j++)
                    listOfStrings.append(QString::number(jsonArray[j].toDouble()));

                paramTableSignal[rootKey] = listOfStrings;
            }
        }
//        cout << str.toStdString() << endl;
    }
    cout << "\n";
}
