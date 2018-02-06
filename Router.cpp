#include "Router.h"

Router::Router(QList<Route*> routes, QObject *parent) : QObject(parent)
{
  Q_UNUSED(parent);

  m_routes.clear();
  m_routes.append(routes);
}

Router::~Router()
{
  qDeleteAll(m_routes.begin(), m_routes.end());
  m_routes.clear();
}

void Router::addRoute(Route *route)
{

}

Route* Router::getRouteForAddress(IPv4Address *address)
{
  int len = m_routes.length();
  int i;

  for ( i = 0; m_routes[i]->getGateway()->toLong() != address->toLong() && i < len; i++ );

  return m_routes[i]; // in all cases
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
