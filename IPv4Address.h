#ifndef IPV4ADDRESS_H
#define IPV4ADDRESS_H

#include <QObject>
#include <QRegularExpression>
#include <QtNetwork>
#include <QHostAddress>
#include "IllegalArgumentException.h"

class IPv4Address : public QObject
{
    Q_OBJECT

  public:
    explicit IPv4Address(QString address, QObject *parent = nullptr);
    explicit IPv4Address(quint32 address, QObject *parent = nullptr);

    virtual ~IPv4Address();

    bool lessThan(IPv4Address *address);
    bool greaterThan(IPv4Address *address);
    bool equals(IPv4Address *address);

    QString toString();
    quint32 toLong();

  private:
    QHostAddress *m_ipAddress;

  signals:

  public slots:
};

#endif // IPV4ADDRESS_H
