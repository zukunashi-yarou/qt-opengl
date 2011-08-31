#include "glwidget.h"
#include <QDebug>
#include <QtGui/QMessageBox>


GLWidget::GLWidget(QWidget *parent) :
    Drawstuff(parent),
    timer(new QBasicTimer)
{
}


void GLWidget::timerEvent(QTimerEvent *e)
{
    Q_UNUSED(e);
    updateGL();
}


void GLWidget::initializeGL()
{
    Drawstuff::initializeGL();
    timer->start(16, this);
}

void GLWidget::resizeGL( int w, int h )
{
    Drawstuff::resizeGL(w, h);


}

void GLWidget::paintGL()
{
    Drawstuff::paintGL();

}

