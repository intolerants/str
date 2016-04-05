#-------------------------------------------------
#
# Project created by QtCreator 2016-03-29T09:02:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = taskManager
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    manager.cpp

HEADERS  += mainwindow.h \
    manager.h

FORMS    += mainwindow.ui
