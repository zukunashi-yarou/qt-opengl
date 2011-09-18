#-------------------------------------------------
#
# Project created by QtCreator 2011-08-31T21:19:00
#
#-------------------------------------------------

QT       += core gui opengl

TARGET = drawstuff
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    camera.cpp \
    basicmesh.cpp \
    glwidget.cpp \
    drawstuff.cpp \
    objmesh.cpp

HEADERS  += mainwindow.h \
    mesh.h \
    camera.h \
    basicmesh.h \
    glwidget.h \
    drawstuff.h \
    objmesh.h

FORMS    += mainwindow.ui

OTHER_FILES +=

RESOURCES += \
    mesh.qrc





