#include "glos.h"

#include "gl.h"
#include "glu.h"
#include "glaux.h"

static GLfloat x = 0;
static GLfloat y = 0;
static GLUquadricObj* obj;

void myInit() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
}

void CALLBACK MutaStanga()
{
    x = x - 10;
}

void CALLBACK MutaDreapta()
{
    x = x + 10;
}

void CALLBACK display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glLoadIdentity();

    //glTranslatef(x, 0, 0.0);

    obj = gluNewQuadric();

    //disc
    glColor3f(1, 0, 0);
    glPushMatrix();
    glTranslatef(x , y, 0);
    gluQuadricDrawStyle(obj, GLU_LINE);
    glRotatef(200,1,1,1);
    gluDisk(obj, 10, 30, 20, 5);
    glPopMatrix();

    //con
    glColor3f(1, 0, 0);
    glPushMatrix();
    glTranslatef(x - 55, 0, 0);
    gluQuadricDrawStyle(obj, GLU_LINE);
    glRotatef(180, 1, 1, 1);
    gluCylinder(obj, 20, 0, 50, 100, 15);
    glPopMatrix();


    //cilindru
    glColor3f(1, 0, 0);
    glPushMatrix();
    glTranslatef(x-90, 0, 0);
    gluQuadricDrawStyle(obj, GLU_LINE);
    glRotatef(240, 1, 1, 0.1);
    gluCylinder(obj, 20, 20, 20, 100, 15);
    glPopMatrix();


    //sferta
    glColor3f(1, 0, 0);
    glPushMatrix();
    glTranslatef(x - 160, 0, 0);
    gluQuadricDrawStyle(obj, GLU_LINE);
    glRotatef(240, 1, 1, 0.2);
    gluSphere(obj, 30, 30, 20);
    glPopMatrix();

    //cerc
    glColor3f(1, 0, 0);
    glPushMatrix();
    glTranslatef(x+65, y, 0.0);
    //glRotatef(200, 1, 1, 1);
    gluQuadricDrawStyle(obj, GLU_LINE);
    gluDisk(obj, 0, 30, 360, 10);
    glPopMatrix();

    //sector de disc
    glColor3f(1, 0, 0);
    glPushMatrix();
    glTranslatef(x + 100, y, 0.0);
    //glRotatef(200, 1, 1, 1);
    gluQuadricDrawStyle(obj, GLU_LINE);
    gluPartialDisk(obj, 10, 30, 360, 10, 10, 60);
    glPopMatrix();

    //sector de cerc
    glColor3f(1, 0, 0);
    glPushMatrix();
    glTranslatef(x + 140, y, 0.0);
    //glRotatef(200, 1, 1, 1);
    gluQuadricDrawStyle(obj, GLU_LINE);
    gluPartialDisk(obj, 0, 30, 360, 10, 10, 60);
    glPopMatrix();

    /*glBegin(GL_QUADS);
    {
        glColor3f(1.0, 0.0, 0.0);
        glVertex2f(100, 100);
        glColor3f(1.0, 1.0, 0.0);
        glVertex2f(150.0, 100.0);
        glColor3f(0.0, 0.0, 1.0);
        glVertex2f(150.0, 150.0);
        glColor3f(0.0, 1.0, 0.0);
        glVertex2f(100.0, 150.0);
    }
    glEnd();*/

    glFlush();
}

#define ISOTROPIC
#ifdef ISOTROPIC
void CALLBACK myReshape(GLsizei w, GLsizei h)
{
    if (!h) {
        return;
    }
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h) {
        glOrtho(-160.0, 160.0, 160.0 * (GLfloat)h / (GLfloat)w, -160.0 * (GLfloat)h / (GLfloat)w, -100.0, 100.0);
    }
    else {
        glOrtho(-160.0 * (GLfloat)w / (GLfloat)h, 160.0 * (GLfloat)w / (GLfloat)h, -160.0, 160.0, -100.0, 100.0);
    }
    glMatrixMode(GL_MODELVIEW);
}
#else
void CALLBACK myReshape(GLsizei w, GLsizei h)
{
    if (!h) return;			//transformare anizotropica, forma se modifica functie de forma(dimens) viewportului
    glViewport(0, 0, w, h);	//daca w>h stabilim ca baza inaltime, si stab unit logica de dimens in fct de h(h/320, 320 lungime lat patrat)
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-160.0, 160.0, -160.0, 160.0, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
}
#endif

int main(int argc, char** argv)
{
    auxInitDisplayMode(AUX_SINGLE | AUX_RGB);
    auxInitPosition(0, 0, 800, 600);
    auxInitWindow("Un patrat");
    myInit();
    auxKeyFunc(AUX_LEFT, MutaStanga);
    auxKeyFunc(AUX_RIGHT, MutaDreapta);

    auxReshapeFunc(myReshape);
    auxMainLoop(display);
    return(0);
}
