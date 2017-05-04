#include <QCoreApplication>
#include <QThread>
#include <QString>
#include <QDebug>

class MyThread: public QThread
{
  Q_OBJECT

public:
  MyThread(QObject * parent = 0): QThread(parent){
    qDebug() << "MyThread Constructor in thread with id = " << QThread::currentThreadId();
  }
  
  void run() { // started is emitted right before this runs
    
    QString result;
    QTextStream output(&result);
    
    output << "Hello from MyThread with id = " << QThread::currentThreadId();
    
    emit done(result);

    // could go on and do other stuff
    // when this returns, finished is emitted
  }
  
signals:

  void done(const QString &s);
};

class Main: public QObject
{
  Q_OBJECT

public:
  
  void doStuff(){
    thread = new MyThread(this);
    connect(thread, SIGNAL(done(QString)), this, SLOT(handleResults(QString)));
    connect(thread, SIGNAL(finished()), this, SLOT(cleanup()));
    thread->start();
  }

protected slots:
  
  void handleResults(const QString & result){
    qDebug() << result;
  }
  
  void cleanup(){
    delete thread;
    QCoreApplication::exit();
  }
  
private:
  
  MyThread *thread;
};
  
#include "qthread_ex1.moc"

int main(int argc, char *argv[])
{
  QCoreApplication app(argc, argv);
  Main m;

  m.doStuff();

  app.exec();
  
  return 0;
}
