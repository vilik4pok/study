#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    auto mainlayout = new QHBoxLayout();
    auto buttonsLayout = new QVBoxLayout();
    auto scene = new QGraphicsScene(this);
    auto gview = new QGraphicsView(this);
    for(int i = 0; i<classNames.length(); i++)
    {
        auto btn = new QPushButton(classNames[i], this);
        connect(btn, &QPushButton::clicked, this, [this, scene](){
           auto obj = this->funcArray[(((QPushButton*)QObject::sender())->objectName()).toInt()]();
           if(obj != nullptr)
                scene->addItem(obj);
        });
        btn->setObjectName(QString::number(i));
        buttonsLayout->addWidget(btn);
    };
    setLayout(mainlayout);
    gview->setScene(scene);
    mainlayout->addWidget(gview);
    mainlayout->addLayout(buttonsLayout);
}

Widget::~Widget(){}
