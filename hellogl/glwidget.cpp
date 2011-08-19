#include "glwidget.h"
#include <QDebug>
#include <QtGui/QMessageBox>

GLWidget::GLWidget(QWidget *parent) :
    QGLWidget(parent)
{
    if ((QGLFormat::openGLVersionFlags() & QGLFormat::OpenGL_Version_1_1) == 0) {
        QMessageBox::critical(0,
            "OpenGL features missing",
            "OpenGL version 1.1 or higher is required.");
        close();
    }
}

void GLWidget::initializeGL()
{
    glClearColor(0.3, 0.3, 0.3, 1.0);
}

void GLWidget::resizeGL( int w, int h )
{
    glViewport(0, 0, w, h);
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glColor3d(1.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex2d(-0.5, -0.5);
    glVertex2d(0.5, -0.5);
    glVertex2d(0.5, 0.5);
    glVertex2d(-0.5, 0.5);
    glEnd();
}

