cmake_minimum_required(VERSION 3.5)

project(QQMusicCopy LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(QQMusicCopy
        main.cpp
        src/header/mainwindow.h
        src/source/mainwindow.cpp
        src/source/rightMenu.cpp
        src/header/rightMenu.h
        src/source/container.cpp
        src/header/container.h
)

target_link_libraries(QQMusicCopy PRIVATE Qt5::Widgets Qt5::Core)
