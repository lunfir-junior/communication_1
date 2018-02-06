#ifndef ROUTER_H
#define ROUTER_H

#include <QObject>
#include <QList>
#include <Route.h>


class Router : public QObject
{
  Q_OBJECT
public:
  explicit Router(QList<Route*> routes, QObject *parent = nullptr);
  virtual ~Router();

  void addRoute(Route *route);
  Route *getRouteForAddress(IPv4Address *address);
  QList<Route*> getRoutes();
  void removeRoute(Route *route);

private:
  QList<Route*> m_routes;

signals:

public slots:
};

#endif // ROUTER_H
