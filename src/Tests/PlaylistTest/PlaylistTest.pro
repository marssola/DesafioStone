QT += testlib sql
QT -= gui

include(../../globals.pri)

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_playlist.cpp

HEADERS += \
    $$PWD/../../SpotQt/src/database/abstractdao.h \
    $$PWD/../../SpotQt/src/database/databaseconnection.h \
    $$PWD/../../SpotQt/src/playlist/track.h \
    $$PWD/../../SpotQt/src/playlist/playlists.h \
    $$PWD/../../SpotQt/src/playlist/playlistdao.h

SOURCES += \
    $$PWD/../../SpotQt/src/database/abstractdao.cpp \
    $$PWD/../../SpotQt/src/database/databaseconnection.cpp \
    $$PWD/../../SpotQt/src/playlist/track.cpp \
    $$PWD/../../SpotQt/src/playlist/playlists.cpp \
    $$PWD/../../SpotQt/src/playlist/playlistdao.cpp

INCLUDEPATH += \
    $$PWD/../../SpotQt/src

DEFINES += RUN_TEST=\\\"Test-\\\"
