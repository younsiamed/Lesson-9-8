#include "udpworker.h"

UDPworker::UDPworker(QObject *parent)
    : QObject(parent)
{
    udpSocket = new QUdpSocket(this);
}

bool UDPworker::bindSocket(quint16 port)
{
    localPort = port;
    bool result = udpSocket->bind(QHostAddress::LocalHost, localPort);
    if (result)
        connect(udpSocket, &QUdpSocket::readyRead, this, &UDPworker::processPendingDatagrams);
    return result;
}

void UDPworker::sendDatagram(const QString &message)
{
    QByteArray datagram = message.toUtf8();
    udpSocket->writeDatagram(datagram, QHostAddress::LocalHost, localPort);
}

void UDPworker::processPendingDatagrams()
{
    while (udpSocket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(int(udpSocket->pendingDatagramSize()));
        QHostAddress sender;
        quint16 senderPort;

        udpSocket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);

        QString info = QString("Принято сообщение от %1:%2 — \"%3\" (%4 байт)")
                           .arg(sender.toString())
                           .arg(senderPort)
                           .arg(QString::fromUtf8(datagram))
                           .arg(datagram.size());

        emit datagramReceived(info);
    }
}
