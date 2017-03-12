#include <QCoreApplication>
#include "locator.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Locator p;

    return a.exec();
}
