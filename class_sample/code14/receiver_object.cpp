#include "receiver_object.h"

#include "settings.h"

#include <QDebug>

void ReceiverObject::update(Settings s){

  qDebug() << "Updating settings.";
  qDebug() << "Width: " << s.width;
  qDebug() << "Height: " << s.height;
}
