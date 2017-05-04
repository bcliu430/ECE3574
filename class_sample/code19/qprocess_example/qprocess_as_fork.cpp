#include <QProcess>
#include <QTextStream>

#include <iostream>

// here I am simply using the command line arguments
// to determine if I am a child
int main(int argc, char*argv[])
{ 
  if(argc == 1){
    std::cout << "Parent Process: " << argc << std::endl;
    
    QString program = "./qtfork";
    QStringList arguments;
    arguments << "-c";

    QProcess *myProcess = new QProcess();
    myProcess->start(program, arguments);

    if (!myProcess->waitForStarted())
      return EXIT_FAILURE;
    
    if (!myProcess->waitForFinished())
      return EXIT_FAILURE;

    myProcess->waitForReadyRead();
    QByteArray result = myProcess->readAll();

    QTextStream(stdout) << QString(result);
  }
  else{
    std::cout << "Child Process: " << argc << std::endl;
  }
  
  return EXIT_SUCCESS;
}
