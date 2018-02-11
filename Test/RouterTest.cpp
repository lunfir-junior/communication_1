#include "RouterTest.h"

RouterTest::RouterTest(QObject *parent) : QObject(parent)
{
  QPointer<Route> route = new Route(new Network(new IPv4Address("0.0.0.0"), 0), new IPv4Address("192.168.0.1"), QString("en0"), 10);
  routes_this.append(route);

  route = new Route(new Network(new IPv4Address("192.168.0.0"), 24), nullptr, "en0", 10);
  routes_this.append(route);

  route = new Route(new Network(new IPv4Address("10.0.0.0"), 8), new IPv4Address("10.123.0.1"), QString("en1"), 10);
  routes_this.append(route);

  route = new Route(new Network(new IPv4Address("10.123.0.0"), 20), nullptr, QString("en1"), 10);
  routes_this.append(route);

  router_this = new Router(routes_this);
}

RouterTest::~RouterTest()
{
  delete router_this;
}

void RouterTest::getRouteForAddress()
{
  IPv4Address *address = new IPv4Address("192.168.0.176");
  Route *route = router_this->getRouteForAddress(address);
  Network *network = route->getNetwork();

  QCOMPARE(route->getMetric(), int(10));
  QCOMPARE(route->getInterfaceName(), QString("en0"));
  QCOMPARE(network->toString(), QString("192.168.0.0/24"));
  QCOMPARE(network->getAddress()->toString(), QString("192.168.0.0"));

  address = new IPv4Address("10.0.1.1");
  route = router_this->getRouteForAddress(address);
  network = route->getNetwork();

  QCOMPARE(route->getMetric(), int(10));
  QCOMPARE(route->getInterfaceName(), QString("en1"));
  QCOMPARE(network->toString(), QString("10.0.0.0/8"));

  delete address;
  delete route;
}
