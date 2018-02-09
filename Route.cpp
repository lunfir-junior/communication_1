#include "Route.h"

Route::Route(Network *network, IPv4Address *gateway, QString interfaceName, int metric, QObject *parent)
  : QObject(parent)
{
  Q_UNUSED(parent);

  m_network = network;
  m_gateway = gateway;
  m_interfaceName = interfaceName;
  m_metric = metric;
}

Route::Route(const Route &other)
  : QObject(other.parent()),
    m_network(other.getNetwork()),
    m_gateway(other.getGateway()),
    m_interfaceName(other.getInterfaceName()),
    m_metric(other.getMetric())
{

}

Route::~Route()
{
  delete m_network;
  delete m_gateway;
}

IPv4Address* Route::getGateway() const
{
  return m_gateway;
}

QString Route::getInterfaceName() const
{
  return m_interfaceName;
}

int Route::getMetric() const
{
  return m_metric;
}

Network* Route::getNetwork() const
{
  return m_network;
}

QString Route::toString() const
{
  QString res;

  res.append("net: ");
  res.append(m_network->toString());

  if ( m_gateway != nullptr ) {
    res.append(", gateway: ");
    res.append(m_gateway->toString());
  }

  res.append(", interface: ");
  res.append(m_interfaceName);
  res.append(", metric: ");
  res.append(QString::number(m_metric));

  return res;
}

Route& Route::operator=(Route *other)
{
  m_network = other->getNetwork();
  m_gateway = other->getGateway();
  m_interfaceName = other->getInterfaceName();
  m_metric = other->getMetric();

  return *this;
}

bool Route::operator==(const Route &other)
{
  return ( m_network == other.getNetwork() &&
           m_gateway == other.getGateway() &&
           m_interfaceName == other.getInterfaceName() &&
           m_metric == other.getMetric()
         );
}

bool Route::operator!=(const Route &other)
{
  return ( m_network != other.getNetwork() ||
           m_gateway != other.getGateway() ||
           m_interfaceName != other.getInterfaceName() ||
           m_metric != other.getMetric()
         );
}


