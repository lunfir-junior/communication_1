#include "Network.h"

#define BYTE_LEN 32

Network::Network(IPv4Address *address, int maskLength, QObject *parent) : QObject(parent)
{
//  qDebug() << __PRETTY_FUNCTION__;
  Q_UNUSED(parent);

  try {
    if ( maskLength > 32 || maskLength < 0 )
      throw IllegalArgumentException("mask length exception");

    quint32 invertLen = BYTE_LEN - maskLength;
    quint32 invertBytes = 0;

    for ( uint i = 0; i < invertLen; i++ ) {
      invertBytes += qPow(2, i);
    }

    m_maskLen = maskLength;
    m_prefix = UINT32_MAX - invertBytes;
  //  qDebug() << "m_prefix: " << m_prefix;
    m_host = ~m_prefix;
    m_address = new IPv4Address(address->toLong() & m_prefix);
    m_broadcast = new IPv4Address(m_address->toLong() | m_host);
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

  delete m_address;
  delete m_broadcast;
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

IPv4Address Network::getFirstUsableAddress()
{
  return IPv4Address(m_address->toLong() + 1);
}

IPv4Address Network::getLastUsableAddress()
{
  return IPv4Address(m_broadcast->toLong() - 1);
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
