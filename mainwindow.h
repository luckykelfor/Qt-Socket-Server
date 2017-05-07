#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QtNetwork/QtNetwork>
#include<QPushButton>
#include<QLabel>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QTcpServer *server;
    std::list<QTcpSocket*> clientConnectionList;
    QTcpSocket *clientCurrentConnection;
    void acceptConnection();



    QLabel resultLabel;
    void onListenBtnClicked();
    void sendMsg();
    void readClient();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H


