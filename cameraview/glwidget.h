#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QBasicTimer>
#include "camera.h"

class GLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = 0);

protected:
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void timerEvent(QTimerEvent *e);

private slots:
    void viewSelect(bool odeOn);

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

private:
    QBasicTimer *timer;
    Camera *camera;
};

#endif // GLWIDGET_H
