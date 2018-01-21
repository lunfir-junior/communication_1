#include "QDebug"
#include "IPv4Address.h"

IPv4Address::IPv4Address(QString address, QObject *parent) : QObject(parent)
{
  qDebug() << __PRETTY_FUNCTION__;
  Q_UNUSED(parent);

  try {
    m_ipAddress = new QHostAddress(address);
    qDebug() << "ip address: " << m_ipAddress->toString();
  }
  catch(IllegalArgumentException exc) {
    Q_UNUSED(exc);
    qDebug() << "IllegalArgumentException!!";
  }
}

IPv4Address::IPv4Address(quint32 address, QObject *parent)
{
  qDebug() << __PRETTY_FUNCTION__;
  Q_UNUSED(parent);

  try {
    m_ipAddress = new QHostAddress(address);
    qDebug() << "ip address: " << m_ipAddress->toString();
  }
  catch(IllegalArgumentException exc) {
    Q_UNUSED(exc);
    qDebug() << "IllegalArgumentException!!";
  }

}

IPv4Address::~IPv4Address() {
  if ( m_ipAddress )
    delete m_ipAddress;

  qDebug() << __PRETTY_FUNCTION__;
}

bool IPv4Address::lessThan(IPv4Address *address)
{
  return (this->toLong() < address->toLong());
}

bool IPv4Address::greaterThan(IPv4Address *address)
{
  return (this->toLong() > address->toLong());
}

bool IPv4Address::equals(IPv4Address *address)
{
  return (this->toString() == address->toString());
}

QString IPv4Address::toString()
{
  return m_ipAddress->QHostAddress::toString();
}

quint32 IPv4Address::toLong()
{
 return m_ipAddress->QHostAddress::toIPv4Address();
}



