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
//  return ( first->getMetric() < second->getMetric() );
  return ( first->getNetwork()->getAddress()->toLong() < second->getNetwork()->getAddress()->toLong() );
}

Router::~Router()
{

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
    for (i = 1; i < len && !(m_routes[i]->getNetwork()->contains(address)); i++ );

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
  int lim = m_routes.length() - 1;

  for ( int i = 0; i < lim; i++ ) {
    out.append(m_routes.at(i)->toString());
    out.append("\n");
  }

  out.append(m_routes.at(lim)->toString());

  return out;
}
