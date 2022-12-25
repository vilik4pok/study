#ifndef MYGRAPHICSITEM_H
#define MYGRAPHICSITEM_H

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QPainter>

class MyGraphicsItem : public QGraphicsItem
{    
public:
    MyGraphicsItem() : QGraphicsItem() {
        setFlag(QGraphicsItem::ItemIsMovable, true);
    }
    virtual bool init()
    {
        return true;
    }
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override
    {
        if(event->button() == Qt::RightButton)
            scene()->removeItem(this);
        else
            QGraphicsItem::mousePressEvent(event);
    }
};

#endif // MYGRAPHICSITEM_H
