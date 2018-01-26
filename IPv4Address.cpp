#include "QDebug"
#include <QtMath>
#include "IPv4Address.h"

IPv4Address::IPv4Address(QString address, QObject *parent) : QObject(parent)
{
  qDebug() << __PRETTY_FUNCTION__;
  Q_UNUSED(parent);

  try {
    stringValidate(address);

    unsigned char bytes[4];
    bytes[0] = 2131504406 & 0xFF;
    bytes[1] = (2131504406 >> 8) & 0xFF;
    bytes[2] = (2131504406 >> 16) & 0xFF;
    bytes[3] = (2131504406 >> 24) & 0xFF;
    qDebug() << bytes[3];
    qDebug() << bytes[2];
    qDebug() << bytes[1];
    qDebug() << bytes[0];

  }
  catch(IllegalArgumentException &exc) {
    qDebug() << exc.what();
  }
}

IPv4Address::IPv4Address(qlonglong address, QObject *parent)
{
  qDebug() << __PRETTY_FUNCTION__;
  Q_UNUSED(parent);

  try {
    if ( address > UINT32_MAX )
      throw IllegalArgumentException("overflow exception");

    m_address = address;
  } catch (IllegalArgumentException &exc) {
    qDebug() << exc.what();
  }

}

IPv4Address::~IPv4Address() {

  qDebug() << __PRETTY_FUNCTION__;
}

bool IPv4Address::lessThan(IPv4Address *address)
{
  return true;
}

bool IPv4Address::greaterThan(IPv4Address *address)
{
  return true;
}

bool IPv4Address::equals(IPv4Address *address)
{
  return true;
}

QString IPv4Address::toString()
{
  return QString("1111");
}

quint32 IPv4Address::toLong()
{
 return 23;
}

void IPv4Address::stringValidate(QString &addr)
{
  QStringList tmp;
  uint tmpLen, addrLen;

  if ( addr.isEmpty() || addr.isNull() ) {
    throw IllegalArgumentException("null exception");
  }

  addrLen = addr.length();
  for ( uint i = 0; i < addrLen; i++ ) {
    const QChar elem = addr.at(i);

    if ( elem > '9' || (elem < '0' && elem != '.') )
      throw IllegalArgumentException("data exception");
  }

  tmp = addr.split('.');
  tmpLen = tmp.size();

  if ( tmpLen != 4 ) {
    throw IllegalArgumentException("size exception");
  }

  for ( uint i = 0; i < tmpLen; i++ ) {
    QString elem = tmp.at(i);

    if ( elem.isEmpty() )
      throw IllegalArgumentException("null octet exception");
  }
}

