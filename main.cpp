#include <QCoreApplication>
#include <QDebug>
#include <QtTest>

#include "IPv4Address.h"
#include "Network.h"

#include "Test/IPv4AddressTest.h"
#include "Test/NetworkTest.h"

int main(int argc, char *argv[])
{
  QCoreApplication a(argc, argv);

//  IPv4Address *test = new IPv4Address("192.168.0.0");
//  Network *net = new Network(test, 24);

  QTest::qExec(new IPv4AddressTest, argc, argv);
  QTest::qExec(new NetworkTest, argc, argv);

  a.QCoreApplication::exit();

  return 0;
}
