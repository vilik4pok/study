#ifndef PALETTE_H
#define PALETTE_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QList>
#include <QColor>

class Palette : public QWidget
{
    Q_OBJECT
    QPushButton* selected;
    QList<QPushButton*> list;
    int row_count, column_count;
public:
    Palette(int row_count, int column_count, QWidget *parent = 0);
    void setColor(int row, int column, QColor color);
     ~Palette();
    QColor getSelectedColor();
public slots:
    void buttonClicked();
signals:
    void selectedColorChanged(QString color);
};

#endif // PALETTE_H
