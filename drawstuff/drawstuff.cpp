#include "drawstuff.h"

#include <QDebug>
#include <QString>
#include <QtGui/QMessageBox>
#include <string.h>

#include "basicmesh.h"


static Mesh* plane;
static Mesh* sphere;
static Mesh* cube;
static Mesh* cylinder;
static Mesh* capsule;
static Mesh* cone;

Drawstuff::Drawstuff(QWidget *parent) :
    QGLWidget(parent),
    camera(new Camera(this))
{
    if ((QGLFormat::openGLVersionFlags() & QGLFormat::OpenGL_Version_1_1) == 0) {
        QMessageBox::critical(0,
            "OpenGL features missing",
            "OpenGL version 1.1 or higher is required.");
        close();
    }

    plane = createPlane(50.0, 50.0);
    sphere = createSphere(0.5, 10);
    cube = createCube(0.5);
    cylinder = createCylinder(0.5, 0.5, 10);
    capsule = createCapsule(0.5, 0.5, 10);
    cone = createCone(0.5, 0.8, 10);
}

void Drawstuff::mousePressEvent(QMouseEvent *e)
{
    if (e->buttons() & Qt::LeftButton) {
        camera->startMotion("Left", QVector2D(e->posF()));
    }
    else if (e->buttons() & Qt::MiddleButton) {
        camera->startMotion("Middle", QVector2D(e->posF()));
    }
    else if (e->buttons() & Qt::RightButton) {
        camera->startMotion("Right", QVector2D(e->posF()));
    }
    qDebug() << "pos=" << QVector2D(e->posF());
}

void Drawstuff::mouseMoveEvent(QMouseEvent *e)
{
    camera->motion(QVector2D(e->posF()));
}

void Drawstuff::mouseReleaseEvent(QMouseEvent *e)
{
    Q_UNUSED(e);
    camera->stopMotion();
}


void Drawstuff::viewSelect(bool odeOn)
{
    if (odeOn) {
        camera->setType("ode");
    }
    else {
        camera->setType("default");
    }
}

void Drawstuff::initializeGL()
{
    qDebug() << "OpenGL Ver. : " << (const char*)(glGetString(GL_VERSION));
    qDebug() << "Shader Ver. : " << (const char*)(glGetString(GL_SHADING_LANGUAGE_VERSION));
    qDebug() << "Vendor      : " << (const char*)(glGetString(GL_VENDOR));
    qDebug() << "GPU         : " << (const char*)(glGetString(GL_RENDERER));

    glClearColor(0.8, 0.8, 1.0, 1.0);
    glClearDepth(1.0);

    glEnable(GL_DEPTH_TEST);

    //Culling
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    // Light settings
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    GLfloat light_position[] = { -50.0, 50.0, 50.0, 1.0 };
    GLfloat light_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
    GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };

    glLightfv( GL_LIGHT0, GL_POSITION, light_position );
    glLightfv( GL_LIGHT0, GL_AMBIENT, light_ambient );
    glLightfv( GL_LIGHT0, GL_DIFFUSE, light_diffuse );
    glLightfv( GL_LIGHT0, GL_SPECULAR, light_specular );

    camera->setup();
}

void Drawstuff::resizeGL( int w, int h )
{
    glViewport(0, 0, w, h);

    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();

    QMatrix4x4 m;
    m.perspective(30, (qreal)w / (qreal)h, 1.0f, 1000.0f);
    glMultMatrixd(m.data());
}

void Drawstuff::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity();

    //Camera
//    QMatrix4x4 m;
//    m.lookAt(QVector3D(7.0, 8.0, 9.0),
//             QVector3D(0.0, 0.0, 0.0),
//             QVector3D(0.0, 1.0, 0.0) );
//    glMultMatrixd(m.data());
    glMultMatrixd(camera->matrixData());


    // draw plane
    glPushMatrix();
    {
        GLfloat color[] = { 0.3, 0.3, 0.2, 1.0 };
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color);

        glTranslatef(0.0, 0.0, 0.0);

        Mesh *mesh = plane;
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
    glPopMatrix();

    // grid line
    GLfloat m_gsize = 50.0;
    glDisable(GL_LIGHTING);
    glColor4f(0.5f, 0.5f, 0.5f, 1.0f);
    glBegin(GL_LINES);
    for (int i = -(int)m_gsize; i <= (int)m_gsize; i++) {
        glVertex3f((GLfloat)i, 0, -m_gsize);
        glVertex3f((GLfloat)i, 0,  m_gsize);
        glVertex3f(-m_gsize, 0, (GLfloat)i);
        glVertex3f( m_gsize, 0, (GLfloat)i);
    }
    glEnd();
    glEnable(GL_LIGHTING);

    glEnable (GL_POLYGON_OFFSET_FILL);
    glPolygonOffset (1.0, 0);


    // draw sphere
    glPushMatrix();
    {
        GLfloat color[] = { 1.0, 0.0, 0.0, 1.0 };
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color);

        glTranslatef(-3.0, 1.0, 0.0);

        Mesh *mesh = sphere;
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
    glPopMatrix();

    // draw cube
    glPushMatrix();
    {
        GLfloat color[] = { 1.0, 0.0, 1.0, 1.0 };
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color);

        glTranslatef(-1.0, 1.0, 0.0);

        Mesh *mesh = cube;
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
    glPopMatrix();

    // draw cylinder
    glPushMatrix();
    {
        GLfloat color[] = { 0.0, 1.0, 1.0, 1.0 };
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color);

        glTranslatef(1.0, 1.0, 0.0);

        Mesh *mesh = cylinder;
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
    glPopMatrix();

    // draw capsule
    glPushMatrix();
    {
        GLfloat color[] = { 1.0, 1.0, 0.0, 1.0 };
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color);

        glTranslatef(3.0, 1.0, 0.0);

        Mesh *mesh = capsule;
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
    glPopMatrix();

    // draw cone
    glPushMatrix();
    {
        GLfloat color[] = { 1.0, 1.0, 1.0, 1.0 };
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color);

        glTranslatef(1.0, 1.0, 2.0);

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
    glPopMatrix();

    camera->render();
    camera->renderSubAxis(0, 0);
}

