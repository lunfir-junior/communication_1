#include <QCoreApplication>
#include <QDebug>
#include <QtTest>

//#include "IPv4Address.h"
//#include "Network.h"
#include <Router.h>

#include "Test/IPv4AddressTest.h"
#include "Test/NetworkTest.h"

int main(int argc, char *argv[])
{
  QCoreApplication a(argc, argv);

  IPv4Address *test = new IPv4Address("192.168.0.0");
  Network *net = new Network(test, 32);
  IPv4AddressTest *ipv4addressTest = new IPv4AddressTest();
  NetworkTest *networkTest = new NetworkTest();

  QList<Route*> routes/* = new QList()*/;

//  routes.append();
  routes.append(new Route(new Network(new IPv4Address("192.168.0.0"), 24), nullptr, QString("en0"), 20));
  routes.append(new Route(new Network(new IPv4Address("10.0.0.0"), 8), new IPv4Address("10.123.0.1"), QString("en1"), 10));

//  Route *testRoute = new Route(new Network(new IPv4Address("0.0.0.0"), 0), new IPv4Address("192.168.0.1"), QString("en0"), 10);

//  qDebug() << testRoute->getGateway()->toString();
//  qDebug() << testRoute->getNetwork()->getAddress()->toString();

  Router *router = new Router(routes);
  router->addRoute(new Route(new Network(new IPv4Address("10.123.0.0"), 20), nullptr, QString("en1"), 5));
  router->addRoute(new Route(new Network(new IPv4Address("192.255.0.0"), 16), nullptr, QString("en0"), 2));
  qDebug().noquote() << router->toString();

  Route *route = router->getRouteForAddress(new IPv4Address("192.255.0.176"));

  qDebug() << route->getMetric(); //10
  qDebug() << route->getInterfaceName(); // en0
  Network *testNet = route->getNetwork();
  qDebug() << testNet->toString();        // 192.168.0.0/24
  qDebug() << testNet->getAddress()->toString(); // 192.168.0.0

//  route = router->getRouteForAddress(new IPv4Address("10.0.1.1"));
//  qDebug() << route->getMetric();                  // 10
//  qDebug() << route->getInterfaceName();           // en1
//  testNet = route->getNetwork();
//  qDebug() << testNet->toString();                     // 10.0.0.0/8

//  IPv4Address *test_1 = new IPv4Address("192.168.0.0");
//    Network *net_1 = new Network(test_1, 32);
//  qDebug() << (*net == *net_1);

//  qDebug() << "total hosts: " << net->getTotalHosts();
//  qDebug() << "is public: " << net->isPublic();

//  qDebug() << net->getAddress()->toString();
//  qDebug() << net->getFirstUsableAddress()->toString();
//  qDebug() << net->getLastUsableAddress()->toString();
//  qDebug() << net->getBroadcastAddress()->toString();

  QTest::qExec(ipv4addressTest, argc, argv);
  QTest::qExec(networkTest, argc, argv);

  delete ipv4addressTest;
  delete networkTest;

  delete net;
  delete test;

  a.QCoreApplication::exit();

  return 0;
}
