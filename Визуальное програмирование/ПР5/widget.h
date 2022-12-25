#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPushButton>
#include <QFileDialog>
#include "equilateraltriangle.h"
#include "mytextitem.h"
#include "myimageitem.h"

template <typename T>
static MyGraphicsItem* createObject()
{
    MyGraphicsItem* obj = new T();
    if(obj->init())
        return obj;
    else {
        delete obj;
        return nullptr;
    }
}

class Widget : public QWidget
{
    Q_OBJECT

    QList<QString> classNames = {"Копибара", "Треугольник", "Изображение"};
    QList<MyGraphicsItem*(*)()> funcArray = {
            &createObject<MyTextItem>,
            &createObject<EquilateralTriangle>,
            &createObject<MyImageItem>
    };
public:
    Widget(QWidget *parent = 0);
    ~Widget();
};

#endif // WIDGET_H
