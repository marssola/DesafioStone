TEMPLATE = subdirs

cli.subdir                      = src/spotqt-cli
api.subdir                      = src/SpotQt
tests.subdir                    = src/Tests
widget.subdir                   = src/SpotifyWidget
qml.subdir                      = src/SpotifyQML
plugin.subdir                   = src/SpotQt-plugin

cli.depends                     = api
widget.depends                  = api
plugin.depends                  = api
qml.depends                     = plugin
tests.depends                   = api

SUBDIRS += \
    api \
    widget \
    plugin \
    qml \
    cli \
    tests

