#include "Network.h"

#define BYTE_LEN 32

Network::Network(IPv4Address *address, int maskLength, QObject *parent) : QObject(parent)
{
//  qDebug() << __PRETTY_FUNCTION__;
  Q_UNUSED(parent);

  try {
    if ( maskLength > 32 || maskLength < 0 || maskLength == 31 )
      throw IllegalArgumentException("mask length exception");

    quint32 invertLen = BYTE_LEN - maskLength;
    quint32 invertBytes = 0;

    for ( uint i = 0; i < invertLen; i++ ) {
      invertBytes += qPow(2, i);
    }

    m_maskLen = maskLength;
    m_prefix = UINT32_MAX - invertBytes;
    m_host = ~m_prefix;
    m_address = new IPv4Address(address->toLong() & m_prefix);

    if ( m_maskLen == 32 ) {
      m_broadcast = m_address;
      m_first = m_address;
      m_last = m_address;
    } else if ( m_maskLen == 30 ) {
      m_broadcast = new IPv4Address(m_address->toLong() | m_host);
      m_first = new IPv4Address(m_address->toLong() + 1);
      m_last = m_first;
    } else {
      m_broadcast = new IPv4Address(m_address->toLong() | m_host);
      m_first = new IPv4Address(m_address->toLong() + 1);
      m_last = new IPv4Address(m_broadcast->toLong() - 1);
    }


//    qDebug() << "mask length: " << m_maskLen;
//    qDebug() << "byte len: " << BYTE_LEN;
//    qDebug() << "max int: " << UINT32_MAX;
//    qDebug() << "m_prefix: " << m_prefix;
//    qDebug() << "m_host: " << m_host;
//    qDebug() << "address: " << m_address->toString() << "   " << m_address->toLong();
//    qDebug() << "broadcast: " << m_broadcast->toString() << "   " << m_broadcast->toLong();
//    qDebug() << "first: " << m_first->toString();
//    qDebug() << "last: " << m_last->toString();

  }
  catch (IllegalArgumentException &exc) {
    qDebug() << exc.what();
  }
}

Network::Network(const Network &other)
  : QObject(other.parent()),
    m_prefix(other.getMask()),
    m_host(other.getHost()),
    m_maskLen(other.getMaskLength()),
    m_address(other.getAddress()),
    m_broadcast(other.getBroadcastAddress())
{

}

Network::~Network()
{
//  qDebug() << __PRETTY_FUNCTION__;

  if ( m_maskLen == 32 ) {
    delete m_address;
  } else if ( m_maskLen == 30 ) {
    delete m_address;
    delete m_broadcast;
    delete m_first;
  } else {
    delete m_address;
    delete m_broadcast;
    delete m_first;
    delete m_last;
  }
}

bool Network::contains(IPv4Address *address)
{
  return ( (address->toLong() >= m_address->toLong()) &&
           (address->toLong() <= m_broadcast->toLong()) );
}

QString Network::toString() const
{
  QString res = m_address->toString();

  res.append('/');
  res.append(QString::number(m_maskLen));
  return res;
}

IPv4Address *Network::getAddress() const
{
  return m_address;
}

IPv4Address *Network::getBroadcastAddress() const
{
  return m_broadcast;
}

IPv4Address *Network::getFirstUsableAddress() const
{
  return m_first;
}

IPv4Address* Network::getLastUsableAddress() const
{
  return m_last;
}

quint32 Network::getMask() const
{
 return m_prefix;
}

QString Network::getMaskString() const
{
  QString output;
  std::array<int, 4> bytes;

  for ( int i = 0, j = 0; i < 4; i++, j += 8 ) {
    bytes[i] = (m_prefix >> j) & 0xFF;
  }

  for ( int i = 3 ; i > 0; i-- ) {
    output.append(QString::number(bytes[i]));
    output.append('.');
  }
  output.append(QString::number(bytes[0]));

  return output;
}

int Network::getMaskLength() const
{
  return m_maskLen;
}

quint32 Network::getHost() const
{
  return m_host;
}

QVector<Network*> Network::getSubnets() // produce two half-sized subnets
{
  int newMaskLen = m_maskLen + qPow(2, 0);
  QVector<Network*> res;

  res.append(new Network(m_address, newMaskLen));
  res.append(new Network( new IPv4Address(res[0]->getBroadcastAddress()->toLong() + 1), newMaskLen));

  return res;
}

long Network::getTotalHosts() // excluding network and broadcast
{
  if ( m_maskLen == 32 )
    return 0;

  if ( m_maskLen == 30 )
    return 1;

  return (qPow(2, (32 - m_maskLen)) - 2);
}

bool Network::isPublic()
{
  return ( (m_address->toString() == "10.0.0.0" && m_maskLen == 8) ||
           (m_address->toString() == "172.16.0.0" && m_maskLen == 12) ||
           (m_address->toString() == "192.168.0.0" && m_maskLen == 16));
}

Network& Network::operator=(Network *other)
{
  this->m_address = other->getAddress();
  this->m_broadcast = other->getBroadcastAddress();
  this->m_maskLen = other->getMaskLength();
  this->m_prefix = other->getMask();
  this->m_host = other->getHost();

  return *this;
}
