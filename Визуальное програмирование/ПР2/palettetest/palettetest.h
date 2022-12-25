#ifndef PALETTETEST_H
#define PALETTETEST_H


#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWidget>
#include <QTextEdit>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QDebug>
#include "palette.h"

namespace Ui {
class PaletteTest;
}

class PaletteTest : public QWidget
{
    Q_OBJECT
    QList<QLineEdit*> list;
    Palette* palette;
    void showMessageBox(QString text);
public:
    explicit PaletteTest(QWidget *parent = 0);
    ~PaletteTest();
public slots:
    void onButtonClicked();
    void onPalleteChangedColor(QString color, int row, int column);
private:
    Ui::PaletteTest *ui;
};

#endif // PALETTETEST_H
