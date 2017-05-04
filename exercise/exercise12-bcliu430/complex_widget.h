#ifndef COMPLEX_WIDGET_H
#define COMPLEX_WIDGET_H

#include <QWidget>

class QDoubleSpinBox;
class QLineEdit;

class ComplexWidget: public QWidget{
Q_OBJECT
public:
   ComplexWidget(QWidget *parrent = nullptr);

private:
    QDoubleSpinBox *realBox;
    QDoubleSpinBox *imagBox;

    QLineEdit *magDisplay;
    QLineEdit *phaseDisplay;


};

#endif
