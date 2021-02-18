#include "spotifywidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    SpotifyWidget w;
    w.show();

    return QApplication::exec();
}
