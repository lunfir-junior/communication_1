#ifndef ROUTE_H
#define ROUTE_H

#include <QObject>
#include <QDebug>
#include <Network.h>
#include <IPv4Address.h>

class Route : public QObject
{
    Q_OBJECT
  public:
    explicit Route(Network *network,
                   IPv4Address *gateway,
                   QString interfaceName,
                   int metric,
                   QObject *parent = nullptr);

    explicit Route(const Route &other);

    virtual ~Route();

    IPv4Address *getGateway() const;
    QString getInterfaceName() const;
    int getMetric() const;
    Network *getNetwork() const;
    QString toString() const;

    Route& operator=(Route *other);
    bool operator==(const Route &other);
    bool operator!=(const Route &other);

  private:
    Network *m_network;
    IPv4Address *m_gateway;
    QString m_interfaceName;
    int m_metric;

  signals:

  public slots:
};

#endif // ROUTE_H
