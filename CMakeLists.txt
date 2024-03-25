cmake_minimum_required(VERSION 3.5)

project(QQMusicCopy LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets Network REQUIRED)

add_executable(QQMusicCopy
        main.cpp
        res.qrc
        src/mainwindow.h
        src/mainwindow.cpp
        src/lib/rightMenu.cpp
        src/lib/rightMenu.h
        src/lib/container.cpp
        src/lib/container.h
        src/lib/topMenu.cpp
        src/lib/topMenu.h
        src/lib/popup/hotSearch.cpp
        src/lib/popup/hotSearch.h
        src/utils/tools.h
        src/utils/tools.cpp
)

target_link_libraries(QQMusicCopy PRIVATE Qt5::Widgets Qt5::Core Qt5::Network)
