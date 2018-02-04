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
  IPv4AddressTest *ipv4addressTest = new IPv4AddressTest();
  NetworkTest *networkTest = new NetworkTest();

  QTest::qExec(ipv4addressTest, argc, argv);
  QTest::qExec(networkTest, argc, argv);

  delete ipv4addressTest;
  delete networkTest;

  a.QCoreApplication::exit();

  return 0;
}
