#include "settings_widget.h"

#include <QWidget>
#include <QLayout>
#include <QSlider>
#include <QDebug>

#include "settings.h"

SettingsWidget::SettingsWidget(QWidget * parent): QWidget(parent) {

  auto slider1 = new QSlider(Qt::Horizontal);
  slider1->setTracking(false);
  QObject::connect(slider1, &QSlider::valueChanged,
		   this, &SettingsWidget::slider1_update);
  
  auto slider2 = new QSlider(Qt::Horizontal);
  slider2->setTracking(false);
  QObject::connect(slider2, &QSlider::valueChanged,
		   this, &SettingsWidget::slider2_update);
    
  auto layout = new QVBoxLayout;
  layout->addWidget(slider1);
  layout->addWidget(slider2);

  setLayout(layout);
};


void SettingsWidget::slider1_update(int value){

  qDebug() << "Slider1 update" << value;

  s.width = static_cast<double>(value)/99.0;

  emit changed(s);
}

void SettingsWidget::slider2_update(int value){

  qDebug() << "Slider2 update" << value;

  s.height = static_cast<double>(value)/99.0;

  emit changed(s);
}

