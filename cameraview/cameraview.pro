#-------------------------------------------------
#
# Project created by QtCreator 2011-08-20T18:20:17
#
#-------------------------------------------------

QT       += core gui opengl

TARGET = cameraview
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    glwidget.cpp \
    basicmesh.cpp \
    camera.cpp

HEADERS  += mainwindow.h \
    mesh.h \
    glwidget.h \
    basicmesh.h \
    camera.h

FORMS    += mainwindow.ui
