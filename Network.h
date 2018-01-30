#ifndef NETWORK_H
#define NETWORK_H

#include <QObject>
#include "IPv4Address.h"

class Network : public QObject
{
    Q_OBJECT

  public:
    explicit Network(IPv4Address address, int maskLength, QObject *parent = nullptr);

    virtual ~Network();

    bool contains(IPv4Address address);
    IPv4Address getAddress();
    IPv4Address getBroadcastAddress();
    IPv4Address getFirstUsableAddress();
    IPv4Address getLastUsableAddress();
    long getMask();
    QString getMaskString();
    int getMaskLength();
    QVector<Network> getSubnets(); // produce two half-sized subnets
    long getTotalHosts(); // excluding network and broadcast
    bool isPublic();

  private:
    quint32 m_mask;

  signals:

  public slots:
};

#endif // NETWORK_H
