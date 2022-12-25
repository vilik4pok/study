#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QObject>
#include <QWidget>
#include <QVBoxLayout>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QTreeView>
#include <QList>
#include <QMenu>
class Playlist : public QWidget
{
    Q_OBJECT
    QMenu itemContextMenu;
    QMenu headerContextMenu;
    QStandardItemModel* standard_model;
    int clickedRow, currentSong;
    void fill(QList<QMap<QString, QString>*>* list);
    void setItem(QStandardItem* item, int row, int column);
    void initItemContextMenu();
    void initHeaderContextMenu();
    void _nextPrevSong(int i);
public:
    Playlist(QWidget *parent = nullptr);
    static const QMap<QString, QString> definedTags;
    static const QMap<QString, int> tagsColumn, ruTagsColumn;
    QTreeView* playlist;
    void openFile();
signals:
    void playSong(QString title, QString author, QString duration);
public slots:
    void onItemContextMenu(const QPoint &point);
    void onHeaderContextMenu(const QPoint &point);
    void onPlaySong();
    void removeFromPlaylist();
    void onHeaderContextMenuItem(bool checked);
    void nextSong();
    void prevSong();


};

#endif // PLAYLIST_H
