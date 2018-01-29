#include "IPv4AddressTest.h"

IPv4AddressTest::IPv4AddressTest(QObject *parent) : QObject(parent)
{
  ip_this = new IPv4Address(2131504406);

}

IPv4AddressTest::~IPv4AddressTest()
{
  delete ip_this;
}

void IPv4AddressTest::lessThan()
{
  IPv4Address *ip_other = new IPv4Address("131.16.34.66");

  QCOMPARE(ip_this->lessThan(ip_other),      bool(true));

  delete ip_other;
}

void IPv4AddressTest::greaterThan()
{
  IPv4Address *ip_other = new IPv4Address("131.16.34.66");

  QCOMPARE(ip_this->greaterThan(ip_other),      bool(false));

  delete ip_other;
}

void IPv4AddressTest::equals()
{
  IPv4Address *ip_other_1 = new IPv4Address("127.12.45.22");
  IPv4Address *ip_other_2 = new IPv4Address(2131504406L);
  IPv4Address *ip_other_3 = new IPv4Address(0xF834AD02L);

  QCOMPARE(ip_this->equals(ip_other_1),      bool(true));
  QCOMPARE(ip_this->equals(ip_other_2),      bool(true));
  QCOMPARE(ip_this->equals(ip_other_3),      bool(false));

  delete ip_other_1;
  delete ip_other_2;
  delete ip_other_3;
}

void IPv4AddressTest::toString()
{
  QCOMPARE(ip_this->toString(),      QString("127.12.45.22"));
}

void IPv4AddressTest::toLong()
{
  QCOMPARE(ip_this->toLong(),      quint32(2131504406));
}
