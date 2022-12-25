#include "mainwidget.h"
#include <QDebug>
#include <QSlider>
#include <QErrorMessage>
#include <QFile>
#include <QMessageBox>
//#include <QStandardItem>


MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent)
{
    auto hlayout = new QHBoxLayout(this);
    auto vlayout = new QVBoxLayout();
    auto hlayout_buttons = new QHBoxLayout();
    auto hlayout_time = new QHBoxLayout();
    setLayout(hlayout);
    hlayout->addLayout(vlayout);

    auto image = new QLabel("image");
    author_name = new QLabel("author");
    song_name = new QLabel("song name");
    auto timebar = new QSlider(Qt::Horizontal, this);
    auto prev_song = new QPushButton("prev song");
    auto play_pause_song = new QPushButton("play pause song");
    auto next_song = new QPushButton("next song");
    auto time_now = new QLabel("00:00");
    duration = new QLabel("00:00");
    duration->setAlignment(Qt::AlignRight);
    image->setAlignment(Qt::AlignCenter);
    author_name->setAlignment(Qt::AlignCenter);
    song_name->setAlignment(Qt::AlignCenter);

    vlayout->addWidget(image);
    vlayout->addWidget(author_name);
    vlayout->addWidget(song_name);
    vlayout->addWidget(timebar);
    vlayout->addLayout(hlayout_time);
    hlayout_time->addWidget(time_now);
    hlayout_time->addWidget(duration);
    vlayout->addLayout(hlayout_buttons);
    hlayout_buttons->addWidget(prev_song);
    hlayout_buttons->addWidget(play_pause_song);
    hlayout_buttons->addWidget(next_song);

    auto playlist = new Playlist(this);
    hlayout->addWidget(playlist);

    connect(playlist, &Playlist::playSong, this, &MainWidget::playSong);
    connect(prev_song, &QPushButton::clicked, playlist, &Playlist::prevSong);
    connect(next_song, &QPushButton::clicked, playlist, &Playlist::nextSong);
    connect(play_pause_song, &QPushButton::clicked, playlist, &Playlist::onPlaySong);
}

void MainWidget::showMessageBox(QString text)
{
    QMessageBox msgBox;
    msgBox.setText(text);
    msgBox.exec();
}

void MainWidget::playSong(QString title, QString author, QString duration)
{
    song_name->setText(title);
    author_name->setText(author);
    this->duration->setText(duration);
}
MainWidget::~MainWidget()
{
}
