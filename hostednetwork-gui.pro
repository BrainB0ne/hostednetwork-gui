#-------------------------------------------------
#
# Project created by QtCreator 2012-06-05T20:38:03
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = hostednetwork-gui
TEMPLATE = app

# ensure one "debug_and_release" in CONFIG, for clarity...
debug_and_release {
    CONFIG -= debug_and_release
    CONFIG += debug_and_release
}

# ensure one "debug" or "release" in CONFIG so they can be used as
# conditionals instead of writing "CONFIG(debug, debug|release)"...
CONFIG(debug, debug|release) {
    CONFIG -= debug release
    CONFIG += debug
}
CONFIG(release, debug|release) {
    CONFIG -= debug release
    CONFIG += release
}

release {
    OUTPUT_DIR = "release"
}

debug {
    OUTPUT_DIR = "debug"
}

win32 {
RC_FILE = hostednetwork-gui.rc
}

SOURCES += main.cpp\
        mainwindow.cpp \
    aboutdialog.cpp \
    licensedialog.cpp

HEADERS  += mainwindow.h \
    aboutdialog.h \
    licensedialog.h

FORMS    += mainwindow.ui \
    aboutdialog.ui \
    licensedialog.ui

OTHER_FILES += \
    images/wifi.png \
    images/stop.png \
    images/start.png \
    images/show.png \
    images/refresh.png \
    images/exit.png \
    images/about.png \
    images/wifi.ico \
    gpl-3.0.txt \
    hostednetwork-gui.rc

RESOURCES += \
    hostednetwork-gui.qrc
