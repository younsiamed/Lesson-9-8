#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUdpSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButtonSend_clicked();    // слот для кнопки "Отправить датаграмму"
    void processPendingDatagrams();      // слот для приема сообщений

private:
    Ui::MainWindow *ui;
    QUdpSocket *udpSocket;
    quint16 localPort = 12345;          // порт для приёма и отправки
};

#endif // MAINWINDOW_H
