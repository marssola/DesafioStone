QT       += core gui sql multimedia qml

unix {
    QT += webengine
}

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

include($$PWD/../globals.pri)

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    spotifyui.cpp \
    spotifywidget.cpp

HEADERS += \
    spotifyui.h \
    spotifywidget.h

INCLUDEPATH += $$DIR_INCLUDE

LIBS += -L$${DIR_LIB} -lSpotQt
message($$DIR_LIB)

# Default rules for deployment.
!macx {
    target.path = $$DIR_INSTALL/bin
    !isEmpty(target.path): INSTALLS += target
}

FORMS += \
    spotifyui.ui
