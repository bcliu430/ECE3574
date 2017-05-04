#include "widget_event.hpp"
#include <QDebug>
#include <QWidget>
#include <QEvent>
#include <iostream>
WidgetEvent::WidgetEvent(QWidget * parent ): QWidget(parent){


}

bool WidgetEvent::event(QEvent *e){
    qDebug() << e->type();
    int foo;
    std::cin  >> foo;
    return true;
}
