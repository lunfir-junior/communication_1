#include <QCoreApplication>
#include <QDebug>
#include <QtTest>

//#include "IPv4Address.h"
//#include "Network.h"
#include <Router.h>

#include "Test/IPv4AddressTest.h"
#include "Test/NetworkTest.h"
#include "Test/RouterTest.h"

int main(int argc, char *argv[])
{
  QCoreApplication a(argc, argv);

  IPv4AddressTest *ipv4addressTest = new IPv4AddressTest();
  NetworkTest *networkTest = new NetworkTest();
  RouterTest *routerTest = new RouterTest();

  QTest::qExec(ipv4addressTest, argc, argv);
  QTest::qExec(networkTest, argc, argv);
  QTest::qExec(routerTest, argc, argv);

  delete ipv4addressTest;
  delete networkTest;
  delete routerTest;

  a.QCoreApplication::exit();

  return 0;
}
