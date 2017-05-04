#include "complex_widget.h"

#include <QWidget>
#include <QDoubleSpinBox>
#include <QLayout>
#include <QLineEdit>

ComplexWidget::ComplexWidget(QWidget *parent){

    realBox = new QDoubleSpinBox(this);
    realBox ->setMinimum (-100.0);
    realBox ->setMaximum (100.0);

    imagBox = new QDoubleSpinBox(this);
    imagBox ->setMinimum (-100.0);
    imagBox ->setMaximum (100.0);
    imagBox-> setSuffix("j");

    magDisplay = new QLineEdit;
    magDisplay -> setReadOnly(true);
    phaseDisplay = new QLineEdit;
    phaseDisplay -> setReadOnly(true);


    auto layout = new QGridLayout;

    layout->addWidget(realBox,0,0);
    layout->addWidget(imagBox,0,1);
    layout->addWidget(magDisplay,1,0);
    layout->addWidget(phaseDisplay,1,1);


    this -> setLayout(layout);
}
