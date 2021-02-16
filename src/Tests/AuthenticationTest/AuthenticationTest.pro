QT += testlib
QT += gui network widgets qml quick webenginecore webengine

CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app

SOURCES +=  tst_authenticationtest.cpp

HEADERS += \
    $$PWD/../../SpotQt/src/authentication/authenticationservice.h \
    $$PWD/../../SpotQt/src/authentication/authenticationgui.h \
    $$PWD/../../SpotQt/src/authentication/authenticationconsts.h

SOURCES += \
    $$PWD/../../SpotQt/src/authentication/authenticationservice.cpp \
    $$PWD/../../SpotQt/src/authentication/authenticationgui.cpp

INCLUDEPATH += \
    $$PWD/../../SpotQt/src/
