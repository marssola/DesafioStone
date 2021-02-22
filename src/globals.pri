!win32-msvc {
    CONFIG += c++17
    QMAKE_CXXFLAGS += -std=c++17

    QMAKE_CXXFLAGS_RELEASE -= -O1
    QMAKE_CXXFLAGS_RELEASE -= -O2
    QMAKE_CXXFLAGS_RELEASE *= -O3
}

CONFIG(debug, debug|release) {
    win32-* {
        DIR_INSTALL=$$OUT_PWD/../SpotQt/debug
    } unix:!macx {
        DIR_INSTALL=$$OUT_PWD/../SpotQtd
    }
} else {
    win32-* {
        DIR_INSTALL=$$OUT_PWD/../SpotQt/release
    } unix:!macx {
        DIR_INSTALL=$$OUT_PWD/../SpotQt
    }
}

DEFINES += ROOT_PATH=\\\"$$DIR_INSTALL\\\"
DEFINES += RUN_TEST=\\\"\\\"

DIR_LIB=$$DIR_INSTALL

DIR_INCLUDE += $$PWD/SpotQt/src
