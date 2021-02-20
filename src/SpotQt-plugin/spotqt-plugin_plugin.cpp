#include "spotqt-plugin_plugin.h"

#include <spotify.h>
#include <playlist/track.h>
#include <playlist/playlists.h>
#include <qqml.h>

void SpotQtPlugin::registerTypes(const char *uri)
{
    // @uri SpotQt
    qmlRegisterType<Spotify>(uri, 1, 0, "Spotify");
    qmlRegisterType<Track>(uri, 1, 0, "Track");
    qmlRegisterType<Playlists>(uri, 1, 0, "Playlists");
}

