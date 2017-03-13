#include <QCoreApplication>
#include "locator.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    ParamsRaw *param = new ParamsRaw("../../config.json");
    Locator loc(param);
    cout << "speed = " << loc.speed << endl;
    cout << "locator_angle = " << loc.locator_angle << endl;

    return a.exec();
}
