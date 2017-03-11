#-------------------------------------------------
#
# Project created by QtCreator 2017-02-25T18:20:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FileExplorer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    archivo.cpp \
    folder.cpp \
    archivotexto.cpp \
    filesystem.cpp \
    lista.cpp \
    files.cpp \
    input.cpp

HEADERS  += mainwindow.h \
    lista.h \
    archivo.h \
    folder.h \
    archivotexto.h \
    filesystem.h \
    files.h \
    input.h

FORMS    += mainwindow.ui \
    input.ui
