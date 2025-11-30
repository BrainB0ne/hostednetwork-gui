cmake_minimum_required(VERSION 3.16)

project(hostednetwork-gui VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt5 REQUIRED COMPONENTS Widgets Gui)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Gui)

set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp mainwindow.h mainwindow.ui
    aboutdialog.cpp aboutdialog.h aboutdialog.ui
    licensedialog.cpp licensedialog.h licensedialog.ui
    hostednetwork-gui.rc
)

set(RESOURCE
    "hostednetwork-gui.qrc"
)

qt5_add_resources(PROJECT_RESOURCES ${RESOURCE})

add_executable(hostednetwork-gui
    ${PROJECT_SOURCES}
    ${PROJECT_RESOURCES}
)

target_link_libraries(hostednetwork-gui PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Gui
)

set_target_properties(hostednetwork-gui PROPERTIES
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS hostednetwork-gui
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
