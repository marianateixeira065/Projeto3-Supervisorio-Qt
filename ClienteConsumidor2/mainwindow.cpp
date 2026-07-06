#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <vector>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    socket = new QTcpSocket(this);
    timer = new QTimer(this);

    connect(socket, &QTcpSocket::readyRead, this, &MainWindow::lerDados);

    connect(timer, &QTimer::timeout, this, &MainWindow::pedirDados);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnConnect_clicked()
{
    QString ip = ui->lineEditIP->text();
    socket->connectToHost(ip, 1234);
}


void MainWindow::on_btnDisconnect_clicked()
{
    socket->disconnectFromHost();
}


void MainWindow::on_btnUpdate_clicked()
{
    if(socket->state() == QAbstractSocket::ConnectedState) {
        socket->write("list\n");
    }
}



void MainWindow::pedirDados()
{
    if(ui->listWidgetIPs->currentItem() != nullptr) {
        QString ipSelecionado = ui->listWidgetIPs->currentItem()->text();

        QString comando = "get " + ipSelecionado + " 30\n";

        socket->write(comando.toUtf8());
    }
}

void MainWindow::lerDados()
{

    std::vector<double> tempos;
    std::vector<double> valores;

    while(socket->bytesAvailable()){

        QString linha = socket->readLine().trimmed();
        if(linha.isEmpty()) continue;

        // Separa os textos usando o espaço
        QStringList partes = linha.split(" ");

        if(partes.size() == 1) {
            ui->listWidgetIPs->addItem(partes[0]);
        }

        else if(partes.size() == 2) {
            tempos.push_back(partes[0].toDouble());
            valores.push_back(partes[1].toDouble());
        }
    }

    if(!valores.empty()){
        ui->widgetGrafico->setDados(tempos, valores);
    }
}

void MainWindow::on_btnStart_clicked()
{
    int tempo = ui->horizontalSlider->value() * 1000;
    timer->start(tempo);
}


void MainWindow::on_btnStop_clicked()
{
    timer->stop();
}


void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    if(timer->isActive()) {
        timer->start(value * 1000);
    }
}

