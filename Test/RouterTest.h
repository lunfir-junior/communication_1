#ifndef ROUTERTEST_H
#define ROUTERTEST_H

#include <QObject>
#include <QTest>

#include <Router.h>

class RouterTest : public QObject
{
    Q_OBJECT
  public:
    explicit RouterTest(QObject *parent = nullptr);
    ~RouterTest();

  private:
    QList<Route*> routes_this;
    Router *router_this;

  signals:

  private slots:
    void getRouteForAddress();

  public slots:

};

#endif // ROUTERTEST_H
