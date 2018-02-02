#include <QCoreApplication>
#include <QDebug>
#include <QtTest>

#include "IPv4Address.h"
#include "Network.h"

//#include "Test/IPv4AddressTest.h"

int main(int argc, char *argv[])
{
  QCoreApplication a(argc, argv);

  IPv4Address *test = new IPv4Address("192.168.0.0");
  Network *net = new Network(test, 24);

  qDebug() << net->getAddress().toString();         // 192.168.0.0
  qDebug() << net->getBroadcastAddress().toString();// 192.168.0.255

  qDebug() << net->contains(new IPv4Address("10.0.23.4"));    // false
  qDebug() << net->contains(new IPv4Address("192.168.0.25")); // true

  qDebug() << net->getFirstUsableAddress().toString(); // 192.168.0.1
  qDebug() << net->getLastUsableAddress().toString();  // 192.168.0.254

  qDebug() << net->isPublic();                                // false
  //  delete net;
//  delete test;

//  QTest::qExec(new IPv4AddressTest, argc, argv);

  return a.exec();
}
