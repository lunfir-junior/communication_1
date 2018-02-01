#include "Network.h"

#define BYTE_LEN 32

Network::Network(IPv4Address *address, int maskLength, QObject *parent) : QObject(parent)
{
  qDebug() << __PRETTY_FUNCTION__;
  Q_UNUSED(parent);

  quint32 invertLen = BYTE_LEN - maskLength;
  quint32 invertBytes = 0;

  for ( uint i = 0; i < invertLen; i++ ) {
    invertBytes += qPow(2, i);
  }

  m_prefix = UINT32_MAX - invertBytes;
  qDebug() << "m_mask: " << m_prefix;
  qDebug() << this->getMaskString();

  m_address = address;
}

Network::~Network()
{
  qDebug() << __PRETTY_FUNCTION__;

  delete m_address;
}

//bool Network::contains(IPv4Address address)
//{

//}

IPv4Address Network::getAddress()
{
  return IPv4Address(m_address->toLong() & m_prefix);
}

//IPv4Address *Network::getBroadcastAddress()
//{
//  return new IPv4Address((m_address->toLong() & m_prefix) + m_prefix + 256);
//}

//IPv4Address Network::getFirstUsableAddress()
//{

//}

//IPv4Address Network::getLastUsableAddress()
//{

//}

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

//int Network::getMaskLength()
//{

//}

//QVector<Network> Network::getSubnets() // produce two half-sized subnets
//{

//}

//long Network::getTotalHosts() // excluding network and broadcast
//{

//}

//bool Network::isPublic()
//{

//}
