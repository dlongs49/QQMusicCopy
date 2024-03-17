QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    main.cpp \
    src\source\mainwindow.cpp\
    src\source\rightMenu.cpp\
    src\source\container.cpp

HEADERS += \
    src\header\mainwindow.h\
    src\header\rightMenu.h\
    src\header\container.h

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
   res.qrc \
