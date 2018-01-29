#include <QCoreApplication>
#include <QDebug>
#include <QtTest>

#include "IPv4Address.h"
#include "Network.h"

#include "Test/IPv4AddressTest.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    IPv4AddressTest *ipv4Test = new IPv4AddressTest();

     QTest::qExec(ipv4Test, argc, argv);

     delete ipv4Test;
    return a.exec();
}
