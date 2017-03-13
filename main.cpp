#include <QCoreApplication>
#include "lord.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Lord w;

    return a.exec();
}
