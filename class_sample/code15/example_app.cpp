#include <QApplication>

#include "example_widget.h"


int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  ExampleWidget example;

  example.show();
  
  return app.exec();
}
