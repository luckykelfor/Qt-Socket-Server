#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    server = new QTcpServer();

    connect(ui->listenBtn,&QPushButton::clicked,this,&MainWindow::onListenBtnClicked);
    connect(ui->pushButton_sendMsg,&QPushButton::clicked,this,&MainWindow::sendMsg);
    ui->resultLabel->show();
    //sendBtn.show();

}
void MainWindow::onListenBtnClicked()
{
    server->listen(QHostAddress::Any, 9527);
    connect(server, &QTcpServer::newConnection, this, &MainWindow::acceptConnection);
}
void MainWindow::acceptConnection()
{
        qDebug("Incoming");
        clientConnection = server->nextPendingConnection();

        connect(clientConnection, &QTcpSocket::readyRead, this, &MainWindow::readClient);
        qDebug("Connet Receiving.");

}
void MainWindow::sendMsg()
{
    QTextCodec *code= QTextCodec::codecForName("UTF-8");
    QByteArray bytest = code->fromUnicode((ui->plainTextEdit_sendMsg->toPlainText())+"\n");
    clientConnection->write(bytest);//(msg.toLatin1(),msg.length());

}
void MainWindow::readClient()
{

        QString str = clientConnection->readAll();
        //或者
        qDebug("Received Something");
       // char buf[1024];
        //clientConnection->read(buf,1024);
        ui->resultLabel->setText(str);



}
MainWindow::~MainWindow()
{
    delete ui;
}
