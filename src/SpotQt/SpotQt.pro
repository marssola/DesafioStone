QT += gui network widgets qml quick sql

unix {
    QT += webengine
}

TEMPLATE = lib
win32-msvc {
    CONFIG += dll staticlib
}

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

include($$PWD/../globals.pri)

SOURCES += \
    $$PWD/src/authentication/authenticationgui.cpp \
    $$PWD/src/authentication/authenticationservice.cpp \
    $$PWD/src/settings/settings.cpp \
    $$PWD/src/database/abstractdao.cpp \
    $$PWD/src/database/databaseconnection.cpp \
    $$PWD/src/settings/itemsettings.cpp \
    $$PWD/src/settings/settingsdao.cpp \
    $$PWD/src/playlist/playlistdao.cpp \
    $$PWD/src/playlist/playlists.cpp \
    $$PWD/src/playlist/track.cpp \
    $$PWD/src/spotify.cpp

HEADERS += \
    $$PWD/src/authentication/authenticationgui.h \
    $$PWD/src/authentication/authenticationservice.h \
    $$PWD/src/authentication/authenticationconsts.h \
    $$PWD/src/settings/settings.h \
    $$PWD/src/database/abstractdao.h \
    $$PWD/src/database/databaseconnection.h \
    $$PWD/src/settings/itemsettings.h \
    $$PWD/src/settings/settingsdao.h \
    $$PWD/src/playlist/playlistdao.h \
    $$PWD/src/playlist/playlists.h \
    $$PWD/src/playlist/track.h \
    $$PWD/src/spotify.h

RESOURCES += \
    $$PWD/qml.qrc

!macx {
    target.path = $$DIR_INSTALL/lib
    !isEmpty(target.path): INSTALLS += target
}
