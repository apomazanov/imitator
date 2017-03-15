#include <QCoreApplication>
#include "receiverbase.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    ReceiverBase b;
    return a.exec();
}
