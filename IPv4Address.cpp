#include "QDebug"
#include "IPv4Address.h"
//^(\d|[1-9]\d|1\d\d|2([0-4]\d|5[0-5]))\.(\d|[1-9]\d|1\d\d|2([0-4]\d|5[0-5]))\.(\d|[1-9]\d|1\d\d|2([0-4]\d|5[0-5]))\.(\d|[1-9]\d|1\d\d|2([0-4]\d|5[0-5]))$


IPv4Address::IPv4Address(QString address, QObject *parent) : QObject(parent)
{
  QRegularExpressionMatch match;

  m_ipRegExp = new QRegularExpression("^#include <[^>]+>$");

  match = m_ipRegExp->QRegularExpression::match(&address);

  qDebug() << ( match.hasMatch() ? "matched  " : "dismatched  " ) << address;

//  delete *match;
}

IPv4Address::~IPv4Address() {

  delete m_ipRegExp;
}



