#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setWindowTitle("Блокнот");
    this->setWindowIcon(QIcon(":/res/new.png"));
    this->setMinimumSize(250,250);
    this->resize(250,250);

    QWidget *centralwidget = new QWidget(this);
    QMenu *menu = menuBar()->addMenu("Действия");
    QToolBar *toolBar = new QToolBar(this);
    QTextEdit *textEdit = new QTextEdit(centralwidget);
    QVBoxLayout *vLayout = new QVBoxLayout(centralwidget);
    QList<QAction*> actions = {
        new QAction(QIcon(":/res/new.png"), "Новый"),
        new QAction(QIcon(":/res/cut.png"), "Вырезать"),
        new QAction(QIcon(":/res/paste.png"), "Вставить"),
        new QAction(QIcon(":/res/copy.png"), "Скопировать"),
        new QAction(QIcon(":/res/undo.png"), "Отменить"),
        new QAction(QIcon(":/res/redo.png"), "Повторить"),
        new QAction("Выход")
    };

    menu->addActions(actions);
    menu->insertSeparator(actions[4]);
    menu->insertSeparator(actions[6]);

    toolBar->addActions(actions.mid(0,6));
    this->addToolBar(toolBar);

    textEdit->setLineWrapMode(QTextEdit::NoWrap);
    vLayout->addWidget(textEdit);

    centralwidget->setLayout(vLayout);
    this->setCentralWidget(centralwidget);

    connect(actions.front(), &QAction::triggered, textEdit, &QTextEdit::clear);
    connect(actions.back(), &QAction::triggered, this, &QMainWindow::close);
}

MainWindow::~MainWindow(){}
