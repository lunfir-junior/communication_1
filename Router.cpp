#include "Router.h"

Router::Router(QList<Route*> &routes, QObject *parent) : QObject(parent)
{
  Q_UNUSED(parent);

  m_routes.clear();
  m_routes.append(routes);

  std::stable_sort(m_routes.begin(), m_routes.end(), cmp);
}

bool Router::cmp(Route *first, Route *second)
{
  return ( first->getNetwork()->getAddress()->toLong() < second->getNetwork()->getAddress()->toLong() );
}

Router::~Router()
{
  qDeleteAll(m_routes.begin(), m_routes.end());
  m_routes.clear();
}

void Router::addRoute(Route *route)
{
  int len = m_routes.length();
  int i;

  for ( i = 0; i < len && cmp(m_routes[i], route); i++ );

  m_routes.insert((i-1), route);

}

Route* Router::getRouteForAddress(IPv4Address *address)
{
  int len = m_routes.length();
  int i;

  try {
    for (i = 0; !m_routes[i]->getNetwork()->contains(address) && i < len; i++ );

    if ( i >= len )
      throw IllegalArgumentException("network exception");

  } catch (IllegalArgumentException &exc) {
    qDebug() << exc.what();
  }
  return m_routes[i];
}

QList<Route*> Router::getRoutes()
{
  return m_routes;
}

void Router::removeRoute(Route *route)
{
  QList<Route*>::iterator iter;

  for (iter = m_routes.begin(); **iter != *route && iter != m_routes.end(); iter++);

  m_routes.erase(iter);
}

QString Router::toString()
{
  QString out;
  int len = m_routes.length();

  for ( int i = 0; i < len; i++ ) {
    Route *current = m_routes.at(i);

    out = "net: " % current->getNetwork()->getAddress()->toString();
//    out.append();

    if ( current->getGateway() != nullptr )
      out %= ", gateway: " % current->getGateway()->toString();

    out += ", interface: " + current->getInterfaceName() + ", metric: ";
//    out.append();
//    out.append();
    out.append(QString::number(current->getMetric()));
    out.append(QChar('/0'));
  }

//net: 192.168.0.0/24, interface: en0, metric: 10
//net: 0.0.0.0/0, gateway: 192.168.0.1, interface: en0, metric: 10
  return out;
}
