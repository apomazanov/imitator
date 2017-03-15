#include <QCoreApplication>
#include "paramsraw.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    ParamsRaw p();

//    QString res = p.getParam("TARGETS", 1, "rsc_sigma");
//    cout << res.toStdString() << endl;

//    int t = p.getArraySize("TARGETS");
//    cout << t << endl;

//    QMap<QString, QString> temp = p.getItemFromArray("TARGETS", 1);
//    foreach (QString key, temp.keys()) {
//        cout << key.toStdString() << ":" << temp.value(key).toStdString() << endl;
//    }


    return a.exec();
}
