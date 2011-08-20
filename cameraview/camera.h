#ifndef CAMERA_H
#define CAMERA_H

#include <QVector2D>
#include <QVector3D>
#include <QString>
#include <QMatrix4x4>
#include <QGLWidget>

class Camera
{
public:
    Camera(QGLWidget *parent=0);
    void setup();

    void startMotion(QString mode, QVector2D pos);
    void stopMotion();
    void motion(QVector2D mpos);
    const qreal* matrixData();

    void renderSubAxis(int w, int h);

private:
    bool      m_motion_on;       // モーションOn/Off
    int       m_motion_mode;     // カメラ移動モード
    QVector2D m_motion_init_pos; // 初期位置

    QVector3D m_eye;
    QVector3D m_ctr;
    QVector3D m_axis;

    QMatrix4x4 m_matrix;

    QGLWidget *widget;
};

#endif // CAMERA_H
