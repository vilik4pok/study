#ifndef PALETTE_H
#define PALETTE_H

#include "palette_global.h"
#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QList>
#include <QColor>

class PALETTESHARED_EXPORT Palette : public QWidget
{
    Q_OBJECT
    QPushButton* selected;
    QList<QPushButton*> list;
    int row_count, column_count;
    void getPosition(QPushButton* w, int* row, int* column);
public:
    Palette(QWidget *parent = 0) : Palette(5, 5, parent){}
    Palette(int row_count, int column_count, QWidget *parent = 0);
    void getSelectedPosition(int* row, int* column);
    int getRowCount();
    int getColumnCount();
    void setColor(int row, int column, QColor color);
    QString getSelectedColor();
    ~Palette();
public slots:
    void buttonClicked();
signals:
    void selectedColorChanged(QString color, int row, int column);
};

#endif // PALETTE_H
