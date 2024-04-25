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
		_.rc
        src/mainwindow.h
        src/mainwindow.cpp
		src/utils/tools.h
        src/utils/tools.cpp
        src/lib/popup/hotSearch.cpp
        src/lib/popup/hotSearch.h
        src/lib/popup/settMenu.cpp
        src/lib/popup/settMenu.h
        src/lib/popup/downInfo.cpp
		src/lib/popup/downInfo.h
		src/lib/popup/handleMenu.cpp
		src/lib/popup/handleMenu.h
		src/lib/popup/songInfo.cpp
		src/lib/popup/songInfo.h
		src/lib/rightMenu.cpp
        src/lib/rightMenu.h
        src/lib/container.cpp
        src/lib/container.h
        src/lib/topMenu.cpp
        src/lib/topMenu.h
		src/lib/recommend.cpp
		src/lib/recommend.h
		src/lib/musicHouse.cpp
		src/lib/musicHouse.h
		src/lib/houseSelected.cpp
		src/lib/houseSelected.h
		src/lib/houseRanking.cpp
		src/lib/houseRanking.h
		src/lib/houseSinger.cpp
		src/lib/houseSinger.h
		src/lib/videoContent.cpp
		src/lib/videoContent.h
		src/lib/videoRecom.cpp
		src/lib/videoRecom.h
		src/lib/videoRanking.cpp
		src/lib/videoRanking.h
		src/lib/videoLibrary.cpp
		src/lib/videoLibrary.h
		src/lib/radar.cpp
		src/lib/radar.h
)

target_link_libraries(QQMusicCopy PRIVATE Qt5::Widgets Qt5::Core Qt5::Network)
