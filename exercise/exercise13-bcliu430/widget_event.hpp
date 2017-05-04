#ifndef WIDGET_EVENT_HPP
#define WIDGET_EVENT_HPP

#include <QWidget>

class WidgetEvent : public QWidget{

Q_OBJECT
public:
    WidgetEvent(QWidget * parent = nullptr);
    bool event (QEvent *e);

private:

};

#endif
