#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "plotter.h"
#include <QDateTime>
#include <QObject>
#include <QTimerEvent>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  socket = new QTcpSocket(this);
  contTimer = 0;

  connect(ui->pushButtonConnect,
          SIGNAL(clicked(bool)),
          this,
          SLOT(tcpConnect()));

  connect(ui->pushButtonDisconnect,
          SIGNAL(clicked(bool)),
          this,
          SLOT(tcpDisconnect()));

  connect(ui->pushButtonStart,
          SIGNAL(clicked(bool)),
          this,
          SLOT(initTimer()));

  connect(ui->pushButtonStop,
          SIGNAL(clicked(bool)),
          this,
          SLOT(endTimer()));

}

void MainWindow::tcpConnect(){
    QString mString;
    bool flag = false;

    mString = ui->lineEditAddress->text();
    socket->connectToHost(mString,1234);

    if(socket->waitForConnected(3000)){
        qDebug() << "Connected";
        ui->listWidget->addItem(mString);
    }
    else{
        qDebug() << "Disconnected";
    }
}

void MainWindow::tcpDisconnect() {
    socket->disconnectFromHost();
    qDebug() << "Disconnect";
}

void MainWindow::initTimer() {
    if(contTimer == 0){
        timerId = startTimer(ui->horizontalSliderTiming->value()*1000);
        contTimer = contTimer + 1;
    }
}

void MainWindow::endTimer() {
    if (contTimer>0){
    killTimer(timerId);
        contTimer = 0;
    }
}

void MainWindow::timerEvent(QTimerEvent *event){
    getData();
}

void MainWindow::getData(){
  QString ipValue;
  QByteArray array;
  QStringList list;

  ipValue = ui->lineEditAddress->text();
  qDebug() << "to get data...";
  if(socket->state() == QAbstractSocket::ConnectedState){
    if(socket->isOpen()){
      qDebug() << "reading...";
        socket->write("get 127.0.0.1 5\r\n");
      socket->waitForBytesWritten();
      socket->waitForReadyRead();
      qDebug() << socket->bytesAvailable();
      while(socket->bytesAvailable()){
        str = socket->readLine().replace("\n","").replace("\r","");
        list = str.split(" ");
        if(list.size() == 2){
          bool ok;
          str = list.at(0);
          thetime = str.toLongLong(&ok);
          str = list.at(1);
          qDebug() << thetime << ": " << str;
        }
      }
    }
  }
}

MainWindow::~MainWindow()
{
  delete socket;
  delete ui;
}
