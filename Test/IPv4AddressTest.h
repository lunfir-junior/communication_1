#ifndef IPV4ADDRESSTEST_H
#define IPV4ADDRESSTEST_H

#include <QObject>
#include <QTest>

#include "IPv4Address.h"

class IPv4AddressTest : public QObject
{
    Q_OBJECT

  public:
    explicit IPv4AddressTest(QObject *parent = 0);
    ~IPv4AddressTest();

  private:
    IPv4Address *ip_this;

  signals:

  private slots:
    void lessThan();
    void greaterThan();
    void equals();

    void toString();
    void toLong();

  public slots:
};

#endif // IPV4ADDRESSTEST_H
