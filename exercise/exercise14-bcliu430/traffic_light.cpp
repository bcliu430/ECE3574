#include "traffic_light.h"

#include <QWidget>
#include <QLayout>
#include <QRadioButton>
#include <cassert>     /* assert */


TrafficLight::TrafficLight(QWidget * parent): QWidget(parent){

  redlight = new QRadioButton;
  redlight->setEnabled(false);
  redlight->toggle();
  redlight->setStyleSheet("QRadioButton::indicator:checked { background-color: red;}");

  yellowlight = new QRadioButton;
  yellowlight->setEnabled(false);
  yellowlight->setStyleSheet("QRadioButton::indicator:checked { background-color: yellow;}");

  greenlight = new QRadioButton;
  greenlight->setEnabled(false);
  greenlight->setStyleSheet("QRadioButton::indicator:checked { background-color: green;}");

  auto layout = new QVBoxLayout;
  layout->addWidget(redlight);
  layout->addWidget(yellowlight);
  layout->addWidget(greenlight);

  setLayout(layout);

  state = RED;
}

void TrafficLight::toggle(){
    switch (state){
        case RED:
          state = YELLOW_GREEN;
          yellowlight->toggle();
          break;
        case YELLOW_GREEN:
        state = GREEN;
        greenlight->toggle();
          break;
        case GREEN:
        state = YELLOW_RED;
        yellowlight->toggle();
          break;
        case YELLOW_RED:
        state = RED;
        redlight->toggle();
          break;
        default:
          assert(false && "should never get here");
          break;
    }
}
