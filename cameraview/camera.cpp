#include "camera.h"
#include "basicmesh.h"
#include <cmath>
#include <QtOpenGL>

static const qreal Pi = 3.14159265358979323846264338327950288419717;
static const qreal radToDeg = (180.0/Pi);
static const qreal degToRad = (Pi/180.0);

static GLuint coneList;
static const float size = 2.0;

Camera::Camera(QGLWidget *parent):
    m_motion_on(false),
    m_eye(QVector3D(7,8,9)),
    m_ctr(QVector3D(0,0.5,0)),
    m_axis(QVector3D(0,1,0)),
    widget(parent)
{
}

void Camera::setup()
{
    Mesh *cone = createCone(0.2*size, 0.5*size, 10);
    coneList = glGenLists(1);
    glNewList(coneList, GL_COMPILE);
    {
        Mesh *mesh = cone;
        for (unsigned i=0; i<mesh->numIndices; i+=3) {
            glBegin(GL_TRIANGLES);
            for (int j=0; j<3; j++) {
                VertexData &v = mesh->vertices[mesh->indices[i+j]];
                glNormal3f(v.normal.x(), v.normal.y(), v.normal.z());
                glVertex3f(v.position.x(), v.position.y(), v.position.z());
            }
            glEnd();
        }
    }
    glEndList();
    delete cone;
}

void Camera::startMotion(QString mode, QVector2D pos)
{
    m_motion_on = true;
    m_motion_init_pos = pos;
    if (mode == QString("Left")) {
        m_motion_mode = 1;
    }
    else if (mode == QString("Middle")) {
        m_motion_mode = 2;
    }
    else if (mode == QString("Right")){
        m_motion_mode = 4;
    }
    else {
        m_motion_mode = 0;
    }
}

void Camera::stopMotion()
{
    m_motion_on = false;
}

void Camera::motion(QVector2D move_pos)
{
    if (!m_motion_on) return;

    QVector2D delta = m_motion_init_pos - move_pos;

    if (m_motion_mode == 1) {
        QVector3D vec = m_eye-m_ctr;
        QMatrix4x4 m;
        qreal angle1 = qreal(delta.x())*0.5;
        m.rotate(angle1,m_axis);
        qreal angle2 = qreal(delta.y())*0.5;
        QVector3D axis = QVector3D::crossProduct(m_axis,vec);
        m.rotate(angle2,axis);
        m_eye = m * vec + m_ctr;
    }
    else if (m_motion_mode == 2) {
        QVector3D vec = m_eye-m_ctr;
        QMatrix4x4 m;
        m.scale(1.0 + qreal(delta.y())*0.005);
        m_eye = m * vec + m_ctr;
    }
    else if (m_motion_mode == 4) {
        QVector3D vec = m_ctr-m_eye;
        QMatrix4x4 m;
        qreal angle1 = qreal(delta.x())*0.3;
        m.rotate(angle1,m_axis);
        qreal scale = 1.0+qreal(delta.y())*0.005;
        vec = QVector3D(vec.x()*scale, vec.y(), vec.z()*scale);
        m_ctr = m * vec + m_eye;
    }
    m_motion_init_pos = move_pos;

    qDebug() << "pos:" << m_eye << ", ctr:" << m_ctr;
}


const qreal* Camera::matrixData()
{
    m_matrix.setToIdentity();
    m_matrix.lookAt(m_eye, m_ctr, m_axis);
    return m_matrix.data();
}

void Camera::renderSubAxis(int w, int h)
{
    if (!m_motion_on) return;

    GLint viewport[4];

    glGetIntegerv(GL_VIEWPORT, viewport);

    glViewport(0+w, 0+h, 100, 100);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    //gluPerspective(45.0, 1, 0.1, 1000.0);
    {
        QMatrix4x4 m;
        m.perspective(45.0, 1, 0.1, 1000.0f);
        glMultMatrixd(m.data());
    }

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    //Camera
    {
        QMatrix4x4 m;
        QVector3D eye = (m_eye - m_ctr).normalized()*10.0;
        m.lookAt(eye, QVector3D(0.0, 0.0, 0.0), m_axis);
        glMultMatrixd(m.data());
    }

    glDisable(GL_LIGHTING);
    glDepthRange(0,0.01);

    glColor3f(1.0,0.0,0.0);
    widget->renderText(3.0,0.0,0.0,QString("x"));
    glPushMatrix();
        glBegin(GL_LINES);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(size, 0.0, 0.0);
        glEnd();
    glPopMatrix();
    glPushMatrix();
        glTranslatef(size, 0.0, 0.0);
        glRotatef(90.0, 0.0, 0.0, -1.0);
        glCallList(coneList);
    glPopMatrix();

    glColor3f(0.0,1.0,0.0);
    widget->renderText(0.0,3.0,0.0,QString("y"));
    glPushMatrix();
        glBegin(GL_LINES);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, size, 0.0);
        glEnd();
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0.0, size, 0.0);
        //glRotatef(90, -1.0, 0.0, 0.0);
        glCallList(coneList);
    glPopMatrix();

    glColor3f(0.0,0.0,1.0);
    widget->renderText(0.0,0.0,3.0,QString("z"));
    glPushMatrix();
        glBegin(GL_LINES);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, 0.0, size);
        glEnd();
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0.0, 0.0, size);
        glRotatef(90, 1.0, 0.0, 0.0);
        glCallList(coneList);
    glPopMatrix();

    glDepthRange(0,1.0);
    glEnable(GL_LIGHTING);

    glPopMatrix();
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

    glViewport(viewport[0], viewport[1], viewport[2], viewport[3]);
}

void Camera::render()
{
    if (!m_motion_on) return;

    const float offset = 0.5;
    const float length = 0.5;

    QVector3D vec = m_eye - m_ctr;
    qreal scale = 0.1*vec.length();

    glDisable(GL_LIGHTING);
    glPushMatrix();

    //position
    glTranslated(m_ctr.x(),m_ctr.y(),m_ctr.z());
    glScaled(scale,scale,scale);

    glColor3f(1.0,1.0,1.0); // white

    glBegin(GL_LINES);
    glVertex3f(offset, 0.0, 0.0);
    glVertex3f(offset+length, 0.0, 0.0);
    glEnd();

    glBegin(GL_LINES);
    glVertex3f(-offset, 0.0, 0.0);
    glVertex3f(-(offset+length), 0.0, 0.0);
    glEnd();

    glBegin(GL_LINES);
    glVertex3f(0.0, offset, 0.0);
    glVertex3f(0.0, offset+length, 0.0);
    glEnd();

    glBegin(GL_LINES);
    glVertex3f(0.0, -offset, 0.0);
    glVertex3f(0.0, -(offset+length), 0.0);
    glEnd();

    glBegin(GL_LINES);
    glVertex3f(0.0, 0.0, offset);
    glVertex3f(0.0, 0.0, offset+length);
    glEnd();

    glBegin(GL_LINES);
    glVertex3f(0.0, 0.0, -offset);
    glVertex3f(0.0, 0.0, -(offset+length));
    glEnd();

    glPopMatrix();
    glEnable(GL_LIGHTING);
}
