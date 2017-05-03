#include "qgraphics_arc_item.hpp"

#include <QGraphicsItem>
#include <QGraphicsEllipseItem>

void QGraphicsArcItem::paint(QPainter *qpainter,
           const QStyleOptionGraphicsItem * option,
           QWidget * widget)
{
    qpainter->drawArc (this->rect(), this->startAngle(), this->spanAngle());
}
