#include "canvas_widget.hpp"

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QWidget>
#include <QLayout>
#include <QPainter>


CanvasWidget::CanvasWidget(QWidget *parent):QWidget(parent){
    scene = new QGraphicsScene(this);
    QGraphicsView *view = new QGraphicsView();

    view ->setScene(scene);

    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(view);
    this ->setLayout(layout);

}

void CanvasWidget::addGraphic(QGraphicsItem * item){
  scene->addItem(item);

}
