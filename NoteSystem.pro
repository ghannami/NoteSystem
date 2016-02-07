#-------------------------------------------------
#
# Project created by QtCreator 2016-01-09T19:25:38
#
#-------------------------------------------------

QT       += core gui webkitwidgets sql

CONFIG   += c++11;
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NoteSystem
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    TreeItem.cpp \
    TreeModel.cpp \
    Global.cpp

HEADERS  += MainWindow.h \
    TreeItem.h \
    TreeModel.h \
    Global.h

FORMS    += MainWindow.ui


