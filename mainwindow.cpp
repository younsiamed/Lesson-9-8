#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QHostAddress>
#include <QByteArray>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Создаём UDP-сокет
    udpSocket = new QUdpSocket(this);

    // Привязываем сокет к локальному порту
    udpSocket->bind(QHostAddress::LocalHost, localPort);

    // Связываем сигнал readyRead с нашим слотом
    connect(udpSocket, &QUdpSocket::readyRead, this, &MainWindow::processPendingDatagrams);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonSend_clicked()
{
    QString message = ui->lineEditMessage->text();
    QByteArray datagram = message.toUtf8();

    // Отправляем на localhost и тот же порт
    udpSocket->writeDatagram(datagram, QHostAddress::LocalHost, localPort);

    ui->lineEditMessage->clear();
}

void MainWindow::processPendingDatagrams()
{
    while (udpSocket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(int(udpSocket->pendingDatagramSize()));
        QHostAddress sender;
        quint16 senderPort;

        udpSocket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);

        QString msg = QString("Принято сообщение от %1, размер сообщения(байт) %2")
                          .arg(sender.toString())
                          .arg(datagram.size());

        ui->textEditReceived->append(msg);
    }
}
