#include <QFile>
#include <QDataStream>
#include <QList>
#include "file_header.h"

int main(int argc, char *argv[])
{
  QFile file("temp.dat");
  file.open(QIODevice::WriteOnly);

  // treat the file as consuming a data stream
  QDataStream out(&file);

  // Write a header with a magic number and a version
  out << MAGIC;
  out << VERSION;

  // use a specific streaming format
  out.setVersion(QDataStream::Qt_5_0);

  // write some data
  QList<QString> msg;
  msg.append( "This is a test.");
  msg.append( "This is only a test");
  out << msg;

  return 0;
}
