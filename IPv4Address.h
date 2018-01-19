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
    explicit IPv4Address(QString i_address, QObject *parent = nullptr);
    explicit IPv4Address(long i_address, QObject *parent = nullptr);

    virtual ~IPv4Address();

    bool lessThan(IPv4Address i_address);
    bool greaterThan(IPv4Address i_address);
    bool equals(IPv4Address i_address);

    QString toString();
    long toLong();

  private:
    QRegularExpression *m_ipRegExp;
    QHostAddress m_ipAddress;

  signals:

  public slots:
};

#endif // IPV4ADDRESS_H
