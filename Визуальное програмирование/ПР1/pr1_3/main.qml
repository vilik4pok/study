import QtQuick 2.12
import QtQuick.Controls 2.5

ApplicationWindow {
    id: mWindow
    minimumWidth: 350
    minimumHeight: 350
    visible: true
    title: "Блокнот"

    menuBar: MenuBar{
        Menu {
            id: menu
            title: "Действия"
            MenuItem {
                text: "Новый"
                icon.source: "qrc:/res/new.png"
                onClicked: textArea.clear()
            }
            MenuItem {
                text: "Вырезать"
                icon.source: "qrc:/res/cut.png"
            }
            MenuItem {
                text: "Вставить"
                icon.source: "qrc:/res/paste.png"
            }
            MenuItem {
                text: "Скопировать"
                icon.source: "qrc:/res/copy.png"
            }
            MenuSeparator { }
            MenuItem {
                text: "Отменить"
                icon.source: "qrc:/res/undo.png"
            }
            MenuItem {
                text: "Повторить"
                icon.source: "qrc:/res/redo.png"
            }
            MenuSeparator { }
            MenuItem {
                text: "Выход"
                onClicked: mWindow.close()
            }
        }
    }

    header: ToolBar {
        Row {
            ToolButton {
                icon.source:  "qrc:/res/new.png"
                onClicked: textArea.clear()
            }
            ToolButton {
                icon.source: "qrc:/res/cut.png"
            }
            ToolButton {
                icon.source: "qrc:/res/paste.png"
            }
            ToolButton {
                icon.source: "qrc:/res/copy.png"
            }
            ToolButton {
                icon.source: "qrc:/res/undo.png"
            }
            ToolButton {
                icon.source: "qrc:/res/redo.png"
            }
            ToolButton {
                text: "Закрыть окно"
                onClicked: mWindow.close()
            }
        }
    }

    ScrollView{
        anchors.fill: parent
        TextArea {
            id: textArea
            textFormat: RichText
            wrapMode: NoWrap
            focus: true
            selectByMouse: true
            persistentSelection: true
            background: null
            font.pixelSize: 12

            MouseArea {
                acceptedButtons: Qt.RightButton
                anchors.fill: parent
                onClicked: menu.open()
            }
        }
    }
}
