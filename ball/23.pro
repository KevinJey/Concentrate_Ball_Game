#-------------------------------------------------
#
# Project created by QtCreator 2019-05-06T13:08:21
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = chess
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    myscence.cpp \
    myitem.cpp

HEADERS  += mainwindow.h \
    myitem.h \
    myScence.h

FORMS    += mainwindow.ui

RESOURCES += \
    picture.qrc

DISTFILES += \
    chooseleftup.png \
    chooserightdown.png \
    leftup.png
