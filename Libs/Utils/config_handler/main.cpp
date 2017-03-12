#include <QCoreApplication>
#include "paramsraw.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    ParamsRaw p(0, "./../../../config.json");

//    QString res = p.getParam("TARGETS", 1, "rsc_sigma");
//    cout << res.toStdString() << endl;
    int t = p.getArraySize("DNA_TABLE_AZ");
    cout << t << endl;

    return a.exec();
}
