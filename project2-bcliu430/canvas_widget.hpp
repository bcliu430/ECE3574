#ifndef CANCAS_WINDOW_HPP
#define CANCAS_WINDOW_HPP
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QPainter>
#include "canvas_widget.hpp"

class CanvasWidget:public QWidget{
Q_OBJECT
public:
  // Default construct a CanvasWidget
  CanvasWidget(QWidget * parent = nullptr);

public slots:
  // A public slot that accepts a signal in the form of a QGraphicsItem pointer containing an
  // object derived from QGraphicsItem to draw
  void addGraphic(QGraphicsItem *item);
private:
QGraphicsScene *scene;
};
#endif
