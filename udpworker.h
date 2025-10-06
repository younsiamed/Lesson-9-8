#ifndef UDPWORKER_H
#define UDPWORKER_H

#include <QObject>
#include <QUdpSocket>
#include <QHostAddress>

class UDPworker : public QObject
{
    Q_OBJECT
public:
    explicit UDPworker(QObject *parent = nullptr);

    void sendDatagram(const QString &message);
    bool bindSocket(quint16 port = 12345);

signals:
    void datagramReceived(const QString &info);

private slots:
    void processPendingDatagrams();

private:
    QUdpSocket *udpSocket;
    quint16 localPort = 12345;
};

#endif // UDPWORKER_H
