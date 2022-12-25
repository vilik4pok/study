#ifndef EQUILATERALTRIANGLE_H
#define EQUILATERALTRIANGLE_H
#include <QtMath>
#include <QPainter>
#include <QPainterPath>
#include "mygraphicsitem.h"

class EquilateralTriangle : public MyGraphicsItem
{
    qreal lenght;
    QPolygonF polygon;
public:
    EquilateralTriangle(qreal lenght = 100) : MyGraphicsItem(){
        this->lenght = lenght;
        polygon << QPointF(-lenght/2, (qSqrt(3)/2*lenght)/2)
                << QPointF(lenght/2, (qSqrt(3)/2*lenght)/2)
                << QPointF(0, (-qSqrt(3)/2*lenght)/2);
    }
    QRectF boundingRect() const override
    {
        return QRectF(-lenght/2, (-qSqrt(3)/2*lenght)/2, lenght, qSqrt(3)/2*lenght);
    }
    QPainterPath shape() const
    {
        QPainterPath path;
        path.addPolygon(polygon);
        return path;
    }
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override
    {
        painter->setBrush(Qt::green);
        painter->setPen(Qt::NoPen);
        painter->drawPolygon(polygon);
    }
};
#endif // EQUILATERALTRIANGLE_H
