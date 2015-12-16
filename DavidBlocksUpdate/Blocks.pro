#-------------------------------------------------
#
# Project created by QtCreator 2015-09-26T07:35:07
#
#-------------------------------------------------

QT       += widgets

QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


TARGET = Blocks
TEMPLATE = app


SOURCES += main.cpp \
    blockswindow.cpp \
    blockspiece.cpp \
    blocksboard.cpp \
    control.cpp \
    player.cpp

HEADERS  += \
    blockswindow.h \
    blockspiece.h \
    blocksboard.h \
    control.h \
    startwindow.h \
    player.h

RESOURCES += \
    images.qrc


