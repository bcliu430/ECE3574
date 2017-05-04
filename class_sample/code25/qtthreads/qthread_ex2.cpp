#include <QCoreApplication>
#include <QThread>
#include <QString>
#include <QTimer>
#include <QDebug>

class Worker : public QObject
{
  Q_OBJECT
  
public slots:
  
  void doit(const QString & name) {
    // example work
    QString result;
    QTextStream output(&result);
    
    output << "Hello " << name << " from MyThread with id = " << QThread::currentThreadId();

      emit resultReady(result);
    }

signals:
    void resultReady(const QString &result);
};

class Controller : public QObject
{
    Q_OBJECT

public:

    Controller() {
      // this is just used to generate a recurring event
      timer = new QTimer(this);
      connect(timer, SIGNAL(timeout()), this, SLOT(update()));

      
      worker = new Worker;
      worker->moveToThread(&workerThread);

      connect(this, SIGNAL(go(QString)), worker, SLOT(doit(QString)));
      connect(worker, SIGNAL(resultReady(QString)), this, SLOT(handleResults(QString)));

      workerThread.start();

      timer->start(2000); // emit timeout every 2 sec
    }

    ~Controller() {
        workerThread.quit();
        workerThread.wait();
	delete worker;
    }

public slots:

  void handleResults(const QString & result){
    qDebug() << result;
  }

  void update(){
    emit go(QString("class"));
  }

signals:
  void go(const QString &);

private:
  
  Worker *worker;
  QThread workerThread;
  QTimer *timer;
};

#include "qthread_ex2.moc"

int main(int argc, char *argv[])
{
  QCoreApplication app(argc, argv);
  Controller c;

  app.exec();
  
  return 0;
}
