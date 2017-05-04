#include <QtConcurrentRun> 
#include <QString>
#include <QTextStream>
#include <QDebug>

// exception handling omitted for clarity.
QString thread_func(QString name)
{
  QString result;
  QTextStream output(&result);
  
  output << "Hello " << name << " from thread func with id = " << QThread::currentThreadId();

  return result;
}

int main()
{
  qDebug() << "Starting thread func.";

  QFuture<QString> future = QtConcurrent::run(thread_func, QString("class"));
  
  qDebug() << "Hello from main.";

  QString result = future.result();

  qDebug() << result;
  
  return 0;
}
