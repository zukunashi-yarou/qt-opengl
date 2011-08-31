#ifndef DRAWSTUFF_H
#define DRAWSTUFF_H

#include <QGLWidget>
#include "camera.h"

class Drawstuff : public QGLWidget
{
    Q_OBJECT
public:
    explicit Drawstuff(QWidget *parent = 0);

protected:
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

private slots:
    void viewSelect(bool odeOn);

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();


private:
    Camera *camera;
};

#endif // DRAWSTUFF_H
