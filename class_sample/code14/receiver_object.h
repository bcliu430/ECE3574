#ifndef RECEIVER_OBJECT_H
#define RECEIVER_OBJECT_H

#include <QObject>

#include "settings.h"

class ReceiverObject: public QObject{
Q_OBJECT

public slots:

  void update(Settings s);

};



#endif
