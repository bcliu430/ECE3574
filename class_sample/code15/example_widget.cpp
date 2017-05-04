#include "example_widget.h"

#include <QCheckBox>
#include <QDial>
#include <QLabel>
#include <QLineEdit>
#include <QLayout>

ExampleWidget::ExampleWidget(QWidget * parent): QWidget(parent){

  // make some check boxes and give them names
  auto check1 = new QCheckBox("Option 1");
  check1->setObjectName("Option 1 CheckBox");
  
  auto check2 = new QCheckBox("Option 2");
  check2->setObjectName("Option 1 CheckBox");
    
  auto check3 = new QCheckBox("Option 3");
  check3->setObjectName("Option 1 CheckBox");

  // make a dial
  auto dial = new QDial;

  // make a label
  auto label = new QLabel("Label:");
  
  // make a line edit
  auto edit = new QLineEdit;

  // layout the widgets
  auto layout = new QGridLayout;

  layout->addWidget(check1, 0, 0);
  layout->addWidget(check2, 0, 1);
  layout->addWidget(check3, 0, 2);
  layout->addWidget(dial, 1, 0, 1, 3, Qt::AlignHCenter);
  layout->addWidget(label, 2, 0);
  layout->addWidget(edit, 2, 1, -1,-1, Qt::AlignLeft);

  setLayout(layout);
}
