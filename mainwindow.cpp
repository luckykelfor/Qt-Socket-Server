#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    server = new QTcpServer();


//    clientConnectionList = new QTcpSocket[2];
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
        clientCurrentConnection = server->nextPendingConnection();


        clientConnectionList.push_back(clientCurrentConnection);
//        clientCurrentConnection->setSocketDescriptor();


        connect(clientCurrentConnection, &QTcpSocket::readyRead, this, &MainWindow::readClient);
        qDebug("Connet Receiving .");//clientConnectionList.size());

}
void MainWindow::sendMsg()
{
    QTextCodec *code= QTextCodec::codecForName("UTF-8");
    QByteArray bytest = code->fromUnicode((ui->plainTextEdit_sendMsg->toPlainText())+"\n");
    qDebug("sending msg.");

    //QTcpSocket  *iter = clientConnectionList.front();
    for(std::list<QTcpSocket*>::const_iterator iter = clientConnectionList.begin();iter!=clientConnectionList.end();iter++)
    {
             (*iter)->write(bytest);//(msg.toLatin1(),msg.length());
    }


//    iter->write(bytest);

 //   clientConnection->write("Hello sdfsdfosdfjsdofosdjfoaijsdojfsdofjaodsjfois到付件搜sdfdsfds是的发生的发生的发生的发放的撒旦法水电费是打发士大夫士大夫的减肥");
}
void MainWindow::readClient()
{

       QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender());

        QString str = socket->readAll();

        int desc =  ((int)(socket->socketDescriptor()));
//        switch(clientCurrentConnection)
        qDebug("Received Something from: %d",desc);
       // char buf[1024];
        //clientConnection->read(buf,1024);
        ui->resultLabel->setText(str);



}
MainWindow::~MainWindow()
{
    delete ui;
}
