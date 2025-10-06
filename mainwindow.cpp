#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    udpWorker = new UDPworker(this);
    udpWorker->bindSocket(12345);

    connect(udpWorker, &UDPworker::datagramReceived, this, &MainWindow::onDatagramReceived);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonSend_clicked()
{
    QString message = ui->lineEditMessage->text();

    if (message.isEmpty()) {
        ui->textEditReceived->append("⚠️ Введите сообщение перед отправкой!");
        return;
    }

    udpWorker->sendDatagram(message);
    ui->textEditReceived->append("✅ Отправлено: " + message);
    ui->lineEditMessage->clear();
}

void MainWindow::onDatagramReceived(const QString &info)
{
    ui->textEditReceived->append(info);
}
