#ifndef SETTINGS_WIDGET_H
#define SETTINGS_WIDGET_H

#include <QWidget>

#include "settings.h"

class SettingsWidget: public QWidget{
Q_OBJECT

public:
  SettingsWidget(QWidget * parent = nullptr);

protected slots:

  void slider1_update(int value);
  void slider2_update(int value);
  
signals:

  void changed(Settings s);

private:

  Settings s;
};


#endif
