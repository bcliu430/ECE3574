#include <cstdlib>
#include <iostream>

#include <QCoreApplication>
#include <QProcess>
#include <QLocalServer>
#include <QLocalSocket>

#include <QDebug>

#include <iostream>

class Server: public QObject
{
 Q_OBJECT

public :
 Server ();

private :  
  QLocalServer* lserver;
  QLocalSocket* connection;

private slots:
  void socket_new_connection();
};

Server::Server()
{
  lserver = new QLocalServer(this);
  if (!lserver->listen("qtipc")) {
    qDebug() << "Error: cannot start local server";
    qDebug() << lserver->errorString();
  }

  connect(lserver, SIGNAL(newConnection()),
          this, SLOT(socket_new_connection()));
}

void Server::socket_new_connection()
{
  qDebug() << "Parent: Connection";
  
  connection = lserver->nextPendingConnection();
  
  connection->waitForReadyRead();
  QByteArray result = connection->readAll();

  qDebug() << "Server: " << QString(result);

  QCoreApplication::quit();
  
}

#include "qprocess_localsocket_comm.moc"

int main(int argc, char*argv[])
{ 
  if(argc == 1){
    std::cout << "Parent Process: acting as a server" << std::endl;
        
    QString program = "./qtipc";
    QStringList arguments;
    arguments << "-c";

    QProcess *myProcess = new QProcess();
    myProcess->start(program, arguments);

    if (!myProcess->waitForStarted())
      return EXIT_FAILURE;

    qDebug() << "Starting Server";
    
    QCoreApplication app(argc, argv);
    Server server;

    // use the Qt event loop
    app.exec();
    
    if (!myProcess->waitForFinished())
      return EXIT_FAILURE;
  }
  else{
    std::cout << "Child Process: acting as a client" << std::endl;

    QLocalSocket connection;
    while(connection.state() != QLocalSocket::ConnectedState){
      connection.connectToServer("qtipc");
      if (connection.waitForConnected(1000)){
	qDebug() << "Child: Connected!";
      }
      qDebug() << "Child: Retrying Connection.";
    }
    connection.write("This is a test", 15);
    connection.flush();
    
  }
  
  return EXIT_SUCCESS;
}
