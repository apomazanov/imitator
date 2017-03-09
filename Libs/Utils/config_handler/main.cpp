#include <QCoreApplication>
#include "jsonparser.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    JsonParser parser;

    return a.exec();
}
