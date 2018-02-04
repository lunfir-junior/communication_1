#include "Network.h"

#define BYTE_LEN 32

Network::Network(IPv4Address *address, int maskLength, QObject *parent) : QObject(parent)
{
//  qDebug() << __PRETTY_FUNCTION__;
  Q_UNUSED(parent);

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

IPv4Address Network::getAddress()
{
  return *m_address;
}

IPv4Address Network::getBroadcastAddress()
{
  return *m_broadcast;
}

IPv4Address Network::getFirstUsableAddress()
{
  return IPv4Address(m_address->toLong() + 1);
}

IPv4Address Network::getLastUsableAddress()
{
  return IPv4Address(m_broadcast->toLong() - 1);
}

quint32 Network::getMask()
{
 return m_prefix;
}

QString Network::getMaskString()
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

int Network::getMaskLength()
{
  return m_maskLen;
}

//QVector<Network> Network::getSubnets() // produce two half-sized subnets
//{

//}

//long Network::getTotalHosts() // excluding network and broadcast
//{

//}

bool Network::isPublic()
{
  return ( (m_address->toString() == "10.0.0.0" && m_maskLen == 8) ||
           (m_address->toString() == "172.16.0.0" && m_maskLen == 12) ||
           (m_address->toString() == "192.168.0.0" && m_maskLen == 16));
}
