#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();
  QString str;
  qint64 thetime;
  void timerEvent(QTimerEvent *event);

  public slots:
  void getData();
  void tcpConnect();
  void tcpDisconnect();
  void initTimer();
  void endTimer();
  private:
  Ui::MainWindow *ui;
  QTcpSocket *socket;
  int timerId, contTimer;
};

#endif // MAINWINDOW_H
