#ifndef IPV4ADDRESS_H
#define IPV4ADDRESS_H

#include <QObject>
#include "IllegalArgumentException.h"

class IPv4Address : public QObject
{
    Q_OBJECT

  public:
    explicit IPv4Address(QString address, QObject *parent = nullptr);
    explicit IPv4Address(qlonglong address, QObject *parent = nullptr);
    IPv4Address(const IPv4Address &other);

    virtual ~IPv4Address();

    bool lessThan(IPv4Address *address);
    bool greaterThan(IPv4Address *address);
    bool equals(IPv4Address *address);

    QString toString() const;
    quint32 toLong() const;

    IPv4Address& operator=(IPv4Address* other);

  private:
    quint32 m_address;
    void stringValidate(QString &addr);

  signals:

  public slots:
};

#endif // IPV4ADDRESS_H
