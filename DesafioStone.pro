TEMPLATE = subdirs

cli.subdir                      = src/spotqt-cli
api.subdir                      = src/SpotQt
tests.subdir                    = src/Tests
widget.subdir                   = src/SpotifyWidget
qml.subdir                      = src/SpotifyQML

cli.depends                     = api
widget.depends                  = api
qml.depends                     = api
tests.depends                   = api

SUBDIRS += \
    qml \
    widget \
    cli \
    api \
    tests

