#ifndef NETWORKTEST_H
#define NETWORKTEST_H

#include <QObject>
#include <QTest>

#include <IPv4Address.h>
#include <Network.h>

class NetworkTest : public QObject
{
    Q_OBJECT
  public:
    explicit NetworkTest(QObject *parent = nullptr);
    ~NetworkTest();

  private:
    Network *net_this;
    IPv4Address *address_this;
    QVector<Network*> subnets_this;

  signals:

  private slots:
    void contains();
    void toString();
    void getAddress();
    void getBroadcastAddress();
    void getFirstUsableAddress();
    void getLastUsableAddress();
    void getMask();
    void getMaskString();
    void getMaskLength();
    void isPublic();
    void getTotalHosts();
    void getSubnets();
};

#endif // NETWORKTEST_H
