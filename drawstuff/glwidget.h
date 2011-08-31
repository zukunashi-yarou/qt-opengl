#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QBasicTimer>
#include "drawstuff.h"

class GLWidget : public Drawstuff
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = 0);

protected:
    void timerEvent(QTimerEvent *e);

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

private:
    QBasicTimer *timer;
};

#endif // GLWIDGET_H
