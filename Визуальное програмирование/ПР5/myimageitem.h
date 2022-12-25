#ifndef MYIMAGEITEM_H
#define MYIMAGEITEM_H
#include <QFileDialog>
#include "mygraphicsitem.h"


class MyImageItem : public MyGraphicsItem
{
    QPixmap pixmap;
public:
    MyImageItem() : MyGraphicsItem(){}
    QRectF boundingRect() const override
    {
        return pixmap.rect();
    }
    bool init() override
    {
        QString filename = QFileDialog::getOpenFileName(nullptr,"Выбрать изображение", ".","Файлы изображений (*.png *.jpg *.jpeg *.bmp)");    //Диалог открытия файла с изображением
        if(filename != "")
        {
            QImage img(filename); //Открывается изображение из файла
            pixmap = QPixmap::fromImage(img.scaled(150,150)); //Создаётся новый элемент
            return true;
        }
        return false;
    }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override
    {
        Q_UNUSED(option)
        Q_UNUSED(widget)
        painter->setBrush(pixmap);
        painter->drawRect(boundingRect());
    }
};
#endif // MYIMAGEITEM_H
