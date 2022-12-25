#ifndef MYTEXTITEM_H
#define MYTEXTITEM_H

#include "mygraphicsitem.h"

class MyTextItem : public MyGraphicsItem
{
    QString text;
    qreal width, height;
public:
    MyTextItem(qreal width=60, qreal height=50, QString text = "Копибара") : MyGraphicsItem()
    {
        this->text = text;
        this->width = width;
        this->height = height;
    }
    QRectF boundingRect() const override
    {
        return QRectF(-width/2, -height/2, width, height);
    }
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override
    {
        painter->drawText(boundingRect(), Qt::AlignCenter, text);
    }
};

#endif // MYTEXTITEM_H
