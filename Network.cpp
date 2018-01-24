#include "Network.h"

Network::Network(IPv4Address address, int maskLength, QObject *parent) : QObject(parent)
{
  Q_UNUSED(parent);


}

Network::~Network()
{

}

bool Network::contains(IPv4Address address)
{

}

IPv4Address Network::getAddress()
{
  return
}

IPv4Address Network::getBroadcastAddress()
{

}

IPv4Address Network::getFirstUsableAddress()
{

}

IPv4Address Network::getLastUsableAddress()
{

}

long Network::getMask()
{

}

QString Network::getMaskString()
{

}

int Network::getMaskLength()
{

}

QVector<Network> Network::getSubnets() // produce two half-sized subnets
{

}

long Network::getTotalHosts() // excluding network and broadcast
{

}

bool Network::isPublic()
{

}
