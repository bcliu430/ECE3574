#include "widget_event.hpp"
#include <QApplication>

int main(int argc, char *argv[]) {

  QApplication app(argc, argv);

  WidgetEvent widget;

  widget.show();

  return app.exec();
}
