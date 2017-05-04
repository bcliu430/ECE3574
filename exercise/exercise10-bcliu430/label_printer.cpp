#include "label_printer.h"
#include <iostream>
#include <QDebug>

LabelPrinter::LabelPrinter(const char * labelstr): QLabel(labelstr) {};

void LabelPrinter::keyPressEvent(QKeyEvent *ev){
    qDebug() << "Hello World!";
}
