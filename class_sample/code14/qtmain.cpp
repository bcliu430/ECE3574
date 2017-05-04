#include <QApplication>

#include "settings_widget.h"
#include "receiver_object.h"
#include "settings.h"

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  SettingsWidget widget;
  ReceiverObject object;

  QObject::connect(&widget, SIGNAL(changed(Settings)), &object, SLOT(update(Settings)));

  widget.show();
  
  return app.exec();
}
