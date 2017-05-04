#include <QtConcurrentRun> 
#include <QDebug>

// exception handling omitted for clarity.
void thread_func()
{
  qDebug() << "Hello from thread func with id = " << QThread::currentThreadId();
}

int main()
{
  qDebug() << "Starting thread func.";

  QFuture<void> future = QtConcurrent::run(thread_func);
  
  qDebug() << "Hello from main.";
  
  return 0;
}
