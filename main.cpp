#include <QCoreApplication>
#include <QDebug>
#include <QtTest>

#include "IPv4Address.h"
#include "Network.h"

#include "Test/IPv4AddressTest.h"

int main(int argc, char *argv[])
{
  QCoreApplication a(argc, argv);

  QTest::qExec(new IPv4AddressTest, argc, argv);

  return a.exec();
}
