#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QDateTime>
#include <QRandomGenerator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    socket = new QTcpSocket(this);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(enviaDados()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnConnect_clicked()
{
    QString ip = ui->lineEditIP->text();
    socket->connectToHost(ip, 1234);
    ui->textBrowserLogs->append("Tentando conectar a " + ip + "...");
}


void MainWindow::on_btnDisconnect_clicked()
{
    socket->disconnectFromHost();
    ui->textBrowserLogs->append("Desconectado do servidor.");
}

void MainWindow::enviaDados()
{
    if(socket->state() == QAbstractSocket::ConnectedState) {

        int min = ui->sliderMin->value();
        int max = ui->sliderMax->value();

        if(min > max) {
            int temp = min;
            min = max;
            max = temp;
        }

        int dado = QRandomGenerator::global()->bounded(min, max + 1);

        qint64 tempo = QDateTime::currentMSecsSinceEpoch();

        QString mensagem = "set " + QString::number(tempo) + " " + QString::number(dado) + "\n";

        socket->write(mensagem.toUtf8());

        ui->textBrowserLogs->append(mensagem.trimmed());
    }
}

void MainWindow::on_btnStart_clicked()
{
    int tempo = ui->sliderTiming->value() * 1000;
    timer->start(tempo);
    ui->textBrowserLogs->append("Transmissão iniciada!");
}


void MainWindow::on_btnStop_clicked()
{
    timer->stop();
    ui->textBrowserLogs->append("Transmissão parada.");
}

