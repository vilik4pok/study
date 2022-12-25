#include "palettetest.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PaletteTest w;
    w.show();

    return a.exec();
}
