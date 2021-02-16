QT += gui qml quick webenginecore webengine sql

CONFIG += console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

include($$PWD/../globals.pri)

SOURCES += \
        $$PWD/src/main.cpp

INCLUDEPATH += $$DIR_INCLUDE

LIBS += -L$${DIR_LIB} -lSpotQt

# Default rules for deployment.
unix {
    target.path = $$DIR_INSTALL/bin
}

!isEmpty(target.path): INSTALLS += target
