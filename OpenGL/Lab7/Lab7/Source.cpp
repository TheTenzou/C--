#include "stdlib.h"
#include <windows.h>
#include <glut.h>
#include <gl/GL.h>
#include <gl/GLU.h>

bool keys[256];
GLfloat rtri;
GLfloat rquad;

void Initialize()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-5.0, 5.0, -5.0, 5.0, -5.0, 5.0);
}

void Draw()
{
	rtri += 20.0f;
	rquad -= 1.0f;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	glTranslatef(-1.5f, 0.0f, 0.0f);

	glPushMatrix();
	glRotatef(30, 1, 0, 0);
	glRotatef(-15, 0, 2, 0);
	glBegin(GL_TRIANGLES);

	glColor3f(1, 0, 0);
	glVertex3f(0, 1, 0);

	glColor3f(0, 1, 0);
	glVertex3f(-1, -1, 1);

	glColor3f(0, 0, 1);
	glVertex3f(1, -1, 1);

	glColor3f(1, 0, 0);
	glVertex3f(0, 1, 0);

	glColor3f(0, 0, 1);
	glVertex3f(1, -1, 1);

	glColor3f(0, 1, 0);
	glVertex3f(1, -1, -1);

	glColor3f(1, 0, 0);
	glVertex3f(0, 1, 0);

	glColor3f(0, 1, 0);
	glVertex3f(1, -1, -1);

	glColor3f(0, 0, 1);
	glVertex3f(-1, -1, 1);
	
	glColor3f(1, 0, 0);
	glVertex3f(-1, -1, 1);

	glColor3f(0, 0, 1);
	glVertex3f(1, -1, 1);

	glColor3f(0, 1, 0);
	glVertex3f(1, -1, -1);

	glEnd();
	glPopMatrix();
	glTranslatef(3, 0, 0);
	glRotatef(35, 1, 0, 0);
	glRotatef(-35, 0, 1, 0);
	glBegin(GL_QUADS);
	glColor3f(0, 1, 1);
	glVertex3f(1, 1, -1);
	glVertex3f(-1, 1, -1);
	glVertex3f(-1, 1, 1);
	glVertex3f(1, 1, 1);

	glColor3f(1, 0, 1);
	glVertex3f(1, 1, 1);
	glVertex3f(-1, 1, 1);
	glVertex3f(-1, -1, 1);
	glVertex3f(1, -1, 1);

	glColor3f(1, 0, 1);
	glVertex3f(-1, 1, 1);
	glVertex3f(-1, 1, -1);
	glVertex3f(-1, -1, -1);
	glVertex3f(-1, -1, 1);

	glColor3f(1, 0, 1);
	glVertex3f(1, 1, -1);
	glVertex3f(1, 1, 1);
	glVertex3f(1, -1, 1);
	glVertex3f(1, -1, -1);

	glColor3f(1, 0.5, 0);
	glVertex3f(1, -1, 1);
	glVertex3f(-1, -1, 1);
	glVertex3f(-1, -1, -1);
	glVertex3f(1, -1, -1);

	glColor3f(0.5, 1.0, 0.5);
	glVertex3f(1, -1, -1);
	glVertex3f(-1, -1, -1);
	glVertex3f(-1, 1, -1);
	glVertex3f(1, 1, -1);
	glEnd();
	glPopMatrix();
	glFlush();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(100,100);
	glutCreateWindow("Polygon");
	Initialize();
	glutDisplayFunc(Draw);
	glutMainLoop();
}