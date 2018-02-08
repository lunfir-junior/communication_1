#ifndef ROUTER_H
#define ROUTER_H

#include <QObject>
#include <QList>
#include <Route.h>
#include <IllegalArgumentException.h>

class Router : public QObject
{
  Q_OBJECT
public:
  explicit Router(QList<Route*> &routes, QObject *parent = nullptr);
  virtual ~Router();

  void addRoute(Route *route);
  Route *getRouteForAddress(IPv4Address *address);
  QList<Route*> getRoutes();
  void removeRoute(Route *route);
  QString toString();

private:
  QList<Route*> m_routes;

  static bool cmp(Route *first, Route *second);

signals:

public slots:
};

#endif // ROUTER_H
