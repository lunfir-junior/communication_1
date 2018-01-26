#include <QCoreApplication>
#include <QDebug>
#include "IPv4Address.h"
#include "Network.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    IPv4Address *ip = new IPv4Address("127.1.5.22");
//    qDebug() << ip->toString();  // 127.12.45.22
//    qDebug() << ip->toLong();    // 2131504406

//    ip = new IPv4Address(2131504406);
//    qDebug() << ip->toString();  // 127.12.45.22
//    qDebug() << ip->toLong();    // 2131504406

//    qDebug() << ip->equals(new IPv4Address("127.12.45.22"));        // true
//    qDebug() << ip->equals(new IPv4Address(2131504406L));           // true
//    qDebug() << ip->equals(new IPv4Address(0xF834AD02L));           // false
//    qDebug() << ip->equals(new IPv4Address("189.11.23.211"));       // false
//    qDebug() << ip->greaterThan(new IPv4Address("131.16.34.66"));   // false
//    qDebug() << ip->lessThan(new IPv4Address("131.16.34.66"));      // true

    delete ip;
    return a.exec();
}
