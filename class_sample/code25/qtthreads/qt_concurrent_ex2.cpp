#include <QtConcurrentRun> 
#include <QString>
#include <QDebug>

// exception handling omitted for clarity.
void thread_func(QString name)
{
  qDebug() << "Hello " << name << " from thread func with id = " << QThread::currentThreadId();
}

int main()
{
  qDebug() << "Starting thread func.";

  QFuture<void> future = QtConcurrent::run(thread_func, QString("class"));
  
  qDebug() << "Hello from main.";

  future.waitForFinished();
  
  return 0;
}
