#
# WLAN Hosted Network Manager
# Copyleft 2012
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#

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
    hostednetwork-gui.rc \
    README \
    images/minimizetotray.png \
    images/clear.png

RESOURCES += \
    hostednetwork-gui.qrc
