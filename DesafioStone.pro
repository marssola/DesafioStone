TEMPLATE = subdirs

cli.subdir                      = src/spotqt-cli
api.subdir                      = src/SpotQt
tests.subdir                    = src/Tests

cli.depends                     = api
tests.depends                   = api

SUBDIRS += \
    cli \
    api \
    tests

