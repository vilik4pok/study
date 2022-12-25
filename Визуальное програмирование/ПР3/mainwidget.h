#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QJsonDocument>
#include <QJsonArray>
#include <QByteArray>
#include <QPushButton>
#include <QJsonObject>
#include <QJsonValue>
#include "playlist.h"

class MainWidget : public QWidget
{
    Q_OBJECT
public:
    QLabel *author_name, *song_name, *duration;
    MainWidget(QWidget *parent = 0);
    static void showMessageBox(QString text);
    ~MainWidget();
public slots:
    void playSong(QString title, QString author, QString duration);

};

#endif // MAINWINDOW_H
