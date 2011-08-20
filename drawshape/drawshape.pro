#-------------------------------------------------
#
# Project created by QtCreator 2011-08-20T11:34:00
#
#-------------------------------------------------

QT       += core gui opengl

TARGET = drawshape
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    glwidget.cpp \
    basicmesh.cpp

HEADERS  += mainwindow.h \
    glwidget.h \
    mesh.h \
    basicmesh.h

FORMS    += mainwindow.ui
