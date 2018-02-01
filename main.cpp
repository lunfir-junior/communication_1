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
//  qDebug() << test->toString();

  Network *net = new Network(test, 24);
  qDebug() << net->getAddress()->toString();         // 192.168.0.0
//  qDebug() << net->getBroadcastAddress()->toString();// 192.168.0.255

//  delete nt;
//  delete test;

//  QTest::qExec(new IPv4AddressTest, argc, argv);

  return a.exec();
}
