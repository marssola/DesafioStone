QT += testlib sql
QT -= gui

include(../../globals.pri)

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_settingstest.cpp

HEADERS += \
    $$PWD/../../SpotQt/src/database/abstractdao.h \
    $$PWD/../../SpotQt/src/database/databaseconnection.h \
    $$PWD/../../SpotQt/src/settings/settingsdao.h \
    $$PWD/../../SpotQt/src/settings/itemsettings.h \
    $$PWD/../../SpotQt/src/settings/settings.h

SOURCES += \
    $$PWD/../../SpotQt/src/database/abstractdao.cpp \
    $$PWD/../../SpotQt/src/database/databaseconnection.cpp \
    $$PWD/../../SpotQt/src/settings/settingsdao.cpp \
    $$PWD/../../SpotQt/src/settings/itemsettings.cpp \
    $$PWD/../../SpotQt/src/settings/settings.cpp

INCLUDEPATH += \
    $$PWD/../../SpotQt/src

DEFINES += TEST=\\\"Test-\\\"
