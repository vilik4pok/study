#include "palettetest.h"
#include <QSizePolicy>
#include <QLayout>
PaletteTest::PaletteTest(QWidget *parent) :
    QWidget(parent)
{
    auto hLayout = new QHBoxLayout();
    auto mainGLayout = new QGridLayout();
    auto button = new QPushButton("Задать цвет");
    palette = new Palette(this);
    QList<QList<QString>> labels_text{{"0", "0", "row"}, {"0","1","column"}, {"1","0","hex color"}};
    for(int i = 0; i<labels_text.size(); i++)
    {
        auto tmp = new QGridLayout();
        tmp->setSizeConstraint(QLayout::SetFixedSize);
        mainGLayout->addLayout(tmp, labels_text[i][0].toInt(), labels_text[i][1].toInt());
        auto label = new QLabel(labels_text[i][2]);
        label->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        tmp->addWidget(label, 0, 0);
        list.append(new QLineEdit(this));
        tmp->addWidget(list.back(), 1, 0);
    }
    this->setLayout(hLayout);
    mainGLayout->addWidget(button, 2,0);
    hLayout->addWidget(palette);
    hLayout->addLayout(mainGLayout);


    connect(button, &QPushButton::clicked, this, &PaletteTest::onButtonClicked);
    connect(palette, &Palette::selectedColorChanged, this, &PaletteTest::onPalleteChangedColor);
}

void PaletteTest::onPalleteChangedColor(QString color, int row, int column)
{
    if(row != -1)
        list[0]->setText(QString::number(row));
    else
        list[0]->setText("");
    if(column != -1)
        list[1]->setText(QString::number(column));
    else
        list[1]->setText("");
    list[2]->setText(color);
}

void PaletteTest::showMessageBox(QString text)
{
    QMessageBox msgBox;
    msgBox.setText(text);
    msgBox.exec();
}

void PaletteTest::onButtonClicked()
{
    QList<bool> success {false, false, false};
    int row = list[0]->text().toInt(&success[0]);
    int column = list[1]->text().toInt(&success[1]);
    success[2] = QColor::isValidColor(list[2]->text());
    if(success[0]&& row >= 0 && row < palette->getRowCount()) {
        if (success[1]&&column >= 0 && column < palette->getColumnCount()) {
            if(success[2])
                palette->setColor(row, column, QColor(list[2]->text()));
            else
                showMessageBox("Invalid hex color");
        } else
             showMessageBox("Invalid column");
    } else
        showMessageBox("Invalid row");
}

PaletteTest::~PaletteTest()
{
}
