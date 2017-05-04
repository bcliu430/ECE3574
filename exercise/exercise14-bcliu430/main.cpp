#include <QApplication>
#include <QTimer>

#include "traffic_light.h"

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  TrafficLight light;

  QTimer timer;
  QObject::connect(&timer,&QTimer::timeout, &light, &TrafficLight::toggle);
  timer.start(1000);
  // setup the timer and conenction here

  light.show();
  return app.exec();
}
