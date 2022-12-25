#include "palette.h"
Palette::Palette(int row_count, int column_count, QWidget *parent)
    : QWidget(parent)
{
    this->row_count = row_count;
    this->column_count = column_count;
    selected = 0;
    setStyleSheet(
        "QPushButton:checked{"
            "border: 2px solid red;"
        "}"
    );
    auto grid_layout = new QGridLayout(this);
    QPushButton *button;
    grid_layout->setSpacing(0);
    for(int i=0; i<row_count; i++)
        for(int j=0; j<column_count; j++)
        {
            button = new QPushButton("", this);
            button->setStyleSheet("background: #ffffff");
            button->setObjectName("#ffffff");
            button->setCheckable(true);
            button->setFocusPolicy(Qt::NoFocus);
            button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            connect(button, &QPushButton::clicked, this, &Palette::buttonClicked);
            list.append(button);
            grid_layout->addWidget(button,i,j);
        }

    setLayout(grid_layout);

}

void Palette::setColor(int row, int column, QColor color)
{

    list[row*column_count+column]->setObjectName(color.name(QColor::HexRgb));
    list[row*column_count+column]->setStyleSheet("background:" + color.name(QColor::HexRgb));
}

Palette::~Palette()
{

}

QColor Palette::getSelectedColor()
{
    return QColor(selected->objectName());
}

void Palette::buttonClicked()
{
    auto sender = ((QPushButton*)QObject::sender());
    if(selected && selected != sender)
        selected->setChecked(false);
    selected = (sender == selected) ? 0 : sender;
    emit selectedColorChanged(selected ? selected->objectName() : "Не выбран");
}
