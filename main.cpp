#include <QCoreApplication>
#include "IPv4Address.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    IPv4Address *test = new IPv4Address("123456");

    delete test;
    return a.exec();
}
