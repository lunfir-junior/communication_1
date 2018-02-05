#include "NetworkTest.h"

NetworkTest::NetworkTest(QObject *parent) : QObject(parent)
{
  address_this = new IPv4Address("192.168.0.0");
  net_this = new Network(address_this, 24);
  subnets_this = net_this->getSubnets();
}

NetworkTest::~NetworkTest()
{
  uint len = subnets_this.length();

  for ( uint i = 0; i < len; i++ ) {
    delete subnets_this[i];
  }

  delete address_this;
  delete net_this;
}

void NetworkTest::contains()
{
  IPv4Address *otherF = new IPv4Address("10.0.23.4");
  IPv4Address *otherT = new IPv4Address("192.168.0.25");

  QCOMPARE(net_this->contains(otherF),       bool(false));
  QCOMPARE(net_this->contains(otherT),       bool(true));

  delete otherF;
  delete otherT;
}

void NetworkTest::toString()
{
  QCOMPARE(net_this->toString(),      QString("192.168.0.0/24"));
}

void NetworkTest::getAddress()
{
  QCOMPARE(net_this->getAddress()->toString(),    QString("192.168.0.0"));
}

void NetworkTest::getBroadcastAddress()
{
  QCOMPARE(net_this->getBroadcastAddress()->toString(),     QString("192.168.0.255"));
}

void NetworkTest::getFirstUsableAddress()
{
  QCOMPARE(net_this->getFirstUsableAddress()->toString(),     QString("192.168.0.1"));
}

void NetworkTest::getLastUsableAddress()
{
  QCOMPARE(net_this->getLastUsableAddress()->toString(),    QString("192.168.0.254"));
}

void NetworkTest::getMask()
{
  QCOMPARE(net_this->getMask(),       quint32(4294967040));
}

void NetworkTest::getMaskString()
{
  QCOMPARE(net_this->getMaskString(),        QString("255.255.255.0"));
}

void NetworkTest::getMaskLength()
{
  QCOMPARE(net_this->getMaskLength(),      int(24));
}

void NetworkTest::isPublic()
{
  QCOMPARE(net_this->isPublic(),    bool(false));
}

void NetworkTest::getTotalHosts()
{
  QCOMPARE(net_this->getTotalHosts(),     long(254));
}

void NetworkTest::getSubnets()
{
  QCOMPARE(subnets_this[0]->toString(),                           QString("192.168.0.0/25"));
  QCOMPARE(subnets_this[0]->getAddress()->toString(),             QString("192.168.0.0"));
  QCOMPARE(subnets_this[0]->getFirstUsableAddress()->toString(),   QString("192.168.0.1"));
  QCOMPARE(subnets_this[0]->getLastUsableAddress()->toString(),    QString("192.168.0.126"));
  QCOMPARE(subnets_this[0]->getMaskLength(),                      int(25));
}
