TEMPLATE = lib
TARGET = SpotQt-plugin
QT += qml quick sql multimedia
CONFIG += plugin

unix {
    QT += webengine
}

include($$PWD/../globals.pri)

TARGET = $$qtLibraryTarget($$TARGET)
uri = SpotQt

# Input
SOURCES += \
        spotqt-plugin_plugin.cpp

HEADERS += \
        spotqt-plugin_plugin.h

DISTFILES = qmldir

qmldir.files = qmldir
!macx {
    installPath = $$DIR_INSTALL/plugins/$$replace(uri, \., /)
    qmldir.path = $$installPath
    target.path = $$installPath
    INSTALLS += target qmldir
}

INCLUDEPATH += $$DIR_INCLUDE

DESTDIR += $$DIR_LIB

LIBS += -L$${DIR_LIB} -lSpotQt
