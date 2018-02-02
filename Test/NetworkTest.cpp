#include "NetworkTest.h"

NetworkTest::NetworkTest(QObject *parent) : QObject(parent)
{
  m_address = new IPv4Address("192.168.0.0");
  m_net = new Network(m_address, 24);
}

NetworkTest::~NetworkTest()
{
  delete m_address;
  delete m_net;
}

void NetworkTest::contains()
{
  IPv4Address *otherF = new IPv4Address("10.0.23.4");
  IPv4Address *otherT = new IPv4Address("192.168.0.25");

  QCOMPARE(m_net->contains(otherF),       bool(false));
  QCOMPARE(m_net->contains(otherT),       bool(true));

  delete otherF;
  delete otherT;

}

void NetworkTest::getAddress()
{
  QCOMPARE(m_net->getAddress().toString(),    QString("192.168.0.0"));
}

void NetworkTest::getBroadcastAddress()
{
  QCOMPARE(m_net->getBroadcastAddress().toString(),     QString("192.168.0.255"));
}

void NetworkTest::getFirstUsableAddress()
{
  QCOMPARE(m_net->getFirstUsableAddress().toString(),     QString("192.168.0.1"));
}

void NetworkTest::getLastUsableAddress()
{
  QCOMPARE(m_net->getLastUsableAddress().toString(),    QString("192.168.0.254"));
}

void NetworkTest::getMask()
{
  QCOMPARE(m_net->getMask(),       quint32(4294967040));
}

void NetworkTest::getMaskString()
{
  QCOMPARE(m_net->getMaskString(),        QString("255.255.255.0"));
}

void NetworkTest::getMaskLength()
{
  QCOMPARE(m_net->getMaskLength(),      int(24));
}

void NetworkTest::isPublic()
{
  QCOMPARE(m_net->isPublic(),       bool(false));
}
