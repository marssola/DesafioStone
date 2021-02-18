TEMPLATE = subdirs

cli.subdir                      = src/spotqt-cli
api.subdir                      = src/SpotQt
tests.subdir                    = src/Tests
widget.subdir                   = src/SpotifyWidget

cli.depends                     = api
widget.depends                  = api
tests.depends                   = api

SUBDIRS += \
    widget \
    cli \
    api \
    tests

