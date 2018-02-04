#include "QDebug"
#include <QtMath>
#include "IPv4Address.h"

IPv4Address::IPv4Address(QString address, QObject *parent) : QObject(parent)
{
//  qDebug() << __PRETTY_FUNCTION__;
  Q_UNUSED(parent);

  try {
    stringValidate(address);
    QStringList temp = address.split('.');

    m_address = 0;
    for ( int i = 3, j = 0; i >= 0; i--, j += 8 ) {
      m_address += (temp[i].toInt() << j);
    }
  }

  catch(IllegalArgumentException &exc) {
    qDebug() << exc.what();
  }
}

IPv4Address::IPv4Address(qlonglong address, QObject *parent) : QObject(parent)
{
//  qDebug() << __PRETTY_FUNCTION__;
  Q_UNUSED(parent);

  try {
    if ( address > UINT32_MAX )
      throw IllegalArgumentException("overflow exception");

    m_address = address;
  }

  catch (IllegalArgumentException &exc) {
    qDebug() << exc.what();
  }

}

IPv4Address::IPv4Address(const IPv4Address& other)
  : QObject(other.parent()),
    m_address(other.toLong())
{

}

IPv4Address::~IPv4Address()
{
//  qDebug() << __PRETTY_FUNCTION__;
}

bool IPv4Address::lessThan(IPv4Address *address)
{
  return m_address < address->toLong();
}

bool IPv4Address::greaterThan(IPv4Address *address)
{
  return m_address > address->toLong();
}

bool IPv4Address::equals(IPv4Address *address)
{
  return m_address == address->toLong();
}

QString IPv4Address::toString() const
{
  QString output;
  quint32 tmp_address = m_address;
  std::array<int, 4> bytes;

  for ( int i = 0, j = 0; i < 4; i++, j += 8 ) {
    bytes[i] = (tmp_address >> j) & 0xFF;
  }

  for ( int i = 3 ; i > 0; i-- ) {
    output.append(QString::number(bytes[i]));
    output.append('.');
  }
  output.append(QString::number(bytes[0]));

  return output;
}

quint32 IPv4Address::toLong() const
{
 return m_address;
}

IPv4Address& IPv4Address::operator=(IPv4Address* other)
{
  this->m_address = other->toLong();

  return *this;
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

