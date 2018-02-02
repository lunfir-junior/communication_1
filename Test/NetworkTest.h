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
    Network *m_net;
    IPv4Address *m_address;

  signals:

  public slots:
    void contains();
    void getAddress();
    void getBroadcastAddress();
    void getFirstUsableAddress();
    void getLastUsableAddress();
    void getMask();
    void getMaskString();
    void getMaskLength();
    void isPublic();
};

#endif // NETWORKTEST_H
