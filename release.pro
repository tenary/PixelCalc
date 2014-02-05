QT += core gui opengl

TEMPLATE = app
TARGET = PixelCalc

INCLUDEPATH = inc
HEADERS = ./inc/mainwindow.h        \
          ./inc/displaywidget.h

SOURCES += ./src/main.cpp           \
           ./src/mainwindow.cpp     \
           ./src/displaywidget.cpp

MOC_DIR = moc
OBJECTS_DIR = obj
DESTDIR = dist
