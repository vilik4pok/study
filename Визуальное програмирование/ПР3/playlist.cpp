#include "playlist.h"
#include <QHeaderView>
#include <QMenu>
#include <QFileDialog>
#include <QTreeView>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QMenu>
#include <QAction>
#include "mainwidget.h"
const QMap<QString, QString> Playlist::definedTags = {
    {"title", "Название"}, {"artist", "Исполнитель"}, {"duration", "Продолжительность"},
    {"year", "Год"}, {"genre", "Жанр"}
};
const QMap<QString, int> Playlist::tagsColumn = {
    {"title", 1}, {"artist", 2}, {"duration", 3}, {"year", 4}, {"genre", 5}
};
const QMap<QString, int> Playlist::ruTagsColumn = {
    {"Название", 1}, {"Исполнитель", 2}, {"Продолжительность", 3}, {"Год", 4}, {"Жанр", 5}
};

Playlist::Playlist(QWidget *parent) : QWidget(parent)
{

    currentSong = clickedRow = -1;
    auto vlayout = new QVBoxLayout(this);
    playlist = new QTreeView(this);
    playlist->setDragDropMode(QAbstractItemView::NoDragDrop);
    standard_model = new QStandardItemModel(this);
    this->setLayout(vlayout);
    vlayout->addWidget(playlist);
    playlist->setModel(standard_model);
    standard_model->setHorizontalHeaderItem(0, new QStandardItem("№"));
    QMapIterator<QString, int> i(tagsColumn);
    while (i.hasNext()) {
        i.next();
        standard_model->setHorizontalHeaderItem(i.value(), new QStandardItem(definedTags[i.key()]));
    }
    playlist->setEditTriggers(QAbstractItemView::NoEditTriggers);
    playlist->setStyleSheet( "QTreeView::branch {  border-image: url(none.png); }" );
    playlist->setRootIsDecorated(false);
    playlist->setContextMenuPolicy(Qt::CustomContextMenu);
    auto playlistHeader = playlist->header();
    playlistHeader->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(playlistHeader,&QTreeView::customContextMenuRequested,this,&Playlist::onHeaderContextMenu);
    connect(playlist,&QTreeView::customContextMenuRequested,this,&Playlist::onItemContextMenu);
    initItemContextMenu();
    initHeaderContextMenu();
    openFile();
}

void Playlist::_nextPrevSong(int i)
{
    currentSong+=i;
    currentSong = currentSong < 0 ? 0 : currentSong;
    currentSong = currentSong >= standard_model->rowCount() ? standard_model->rowCount()-1 : currentSong;
    onPlaySong();
}

void Playlist::nextSong()
{
    _nextPrevSong(1);
}
void Playlist::prevSong()
{
    _nextPrevSong(-1);
}

void Playlist::onItemContextMenu(const QPoint &point)
{
    QTreeView* sender = (QTreeView*)(QObject::sender());
    QModelIndex index = sender->indexAt(point);
    if (index.isValid()) {
        auto tmp = currentSong;
        currentSong = index.row();
        auto action = itemContextMenu.exec(sender->viewport()->mapToGlobal(point));
        if(!action || action->text() == "Удалить")
            currentSong = tmp;
    }
}

void Playlist::initItemContextMenu()
{
    QList<void (Playlist::*)()> functions = {
        &Playlist::onPlaySong,
        &Playlist::removeFromPlaylist
    };
    QList<QString> names = {"Воспроизвести", "Удалить"};
    for(int i=0; i<names.length()&&i<functions.length(); i++){
        auto action = itemContextMenu.addAction(names[i]);
        connect(action, &QAction::triggered, this, functions[i]);
    }
}
void Playlist::initHeaderContextMenu()
{
    QMapIterator<QString, int> i(ruTagsColumn);
    while (i.hasNext()) {
        i.next();
        auto action = new QAction(i.key());
        action->setCheckable(true);
        action->setChecked(true);
        connect(action, &QAction::triggered, this, &Playlist::onHeaderContextMenuItem);
        headerContextMenu.addAction(action);
    }
}

void Playlist::onHeaderContextMenuItem(bool checked)
{
    QAction* sender = (QAction*)(QObject::sender());
    playlist->setColumnHidden(ruTagsColumn[sender->text()], !checked);
}
void Playlist::onPlaySong()
{
    if(standard_model->rowCount()>0)
    {
        currentSong = currentSong < 0 ? 0 : currentSong;
        emit playSong(
            standard_model->item(currentSong, tagsColumn["title"])->text(),
            standard_model->item(currentSong, tagsColumn["artist"])->text(),
            standard_model->item(currentSong, tagsColumn["duration"])->text()
        );
    }
}
void Playlist::removeFromPlaylist()
{
    standard_model->removeRow(currentSong);
    for(int i=currentSong; i<standard_model->rowCount(); i++)
        standard_model->item(i)->setText(QString::number(i+1));
}

void Playlist::onHeaderContextMenu(const QPoint &point)
{
    QMenu *menu = new QMenu(this);
    QMapIterator<QString, QString> i(definedTags);
    while (i.hasNext()) {
        i.next();
        menu->addAction(i.value());
    }
    headerContextMenu.exec(((QHeaderView*)QObject::sender())->viewport()->mapToGlobal(point));
}
void Playlist::openFile()
{
    QList<QMap<QString, QString>*> list;
    QString filename = QFileDialog::getOpenFileName(this,"Выбрать плэйлист", ".","Файлы json (*.json)");
    if(filename != "")
    {
        QFile file(filename);
        if (file.open(QFile::ReadOnly | QFile::Text)){

            auto doc = QJsonDocument::fromJson(QByteArray(file.readAll()));
            if(!doc.isNull())
            {
                QJsonArray song = doc.array();
                QMap<QString, QString> *map;
                foreach(auto i, song)
                {
                    map = new QMap<QString, QString>();
                    foreach(auto j, i.toArray())
                    {
                        auto obj = j.toObject();
                        auto tag = obj.value("tag").toString();
                        if(definedTags.contains(tag))
                            (*map)[tag] = obj.value("value").toString();
                    }
                    list.append(map);
                }
                this->fill(&list);
                file.close();
            }
            else
                MainWidget::showMessageBox("Не удалось прочитать файл");
        }
    }
}

void Playlist::fill(QList<QMap<QString, QString>*>* list)
{
    int count = 0;
    foreach (auto map, *list) {
        setItem(new QStandardItem(QString::number(count+1)), count, 0);
        QMapIterator<QString, QString> i(*map);
        while (i.hasNext()) {
            i.next();
            setItem(new QStandardItem(i.value()), count, tagsColumn[i.key()]);
        };
        count++;
    }
}

void Playlist::setItem(QStandardItem* item, int row, int column)
{
    ((QStandardItemModel*)playlist->model())->setItem(row, column, item);
}
