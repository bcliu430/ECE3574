#ifndef QGRAPHICS_ARC_ITEM_HPP
#define QGRAPHICS_ARC_ITEM_HPP

#include <QGraphicsItem>
#include <QGraphicsEllipseItem>
#include <QObject>
#include <QPainter>
#include <QWidget>

class QGraphicsArcItem : public QGraphicsEllipseItem {

public:
    void paint(QPainter *qpainter,
               const QStyleOptionGraphicsItem * option,
               QWidget * widget = 0);

};
#endif
