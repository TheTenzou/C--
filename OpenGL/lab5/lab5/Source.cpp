#include <glut.h>
#include <GL/gl.h>
#include <gl/GLU.h>

//BOOL keys[256];
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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//������� ��������� ������. GL_COLOR_BUFFER_BIT - ������� ������ �����
	glPushMatrix();
	glTranslatef(1.0f, 1.0f, 0.0f);
	glRotatef(-45, 0.0f, 1.0f, 0.0f);
	glRotatef(65, 1.0f, 0.0f, 0.0f);
	glBegin(GL_TRIANGLES); //���������, ��� ����� ��������. GL_TRIANGLES: ������ ��� ������ glVertex ������ �����������.
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 0.0f);
	glEnd();//��������� �������� ������
	glPopMatrix();
	glTranslatef(-1.0f, 0.0f, 0.0f);
	glColor3f(0.5f, 0.5f, 1.0f);
	glRotatef(65, 1.0f, 0.0f, 0.0f);
	glRotatef(0, 0.0f, 1.0f, 0.0f);
	glRotatef(35, 0.0f, 0.0f, 1.0f);
	glBegin(GL_QUADS);//���������, ��� ����� ��������. GL_QUADS: ������ ������ ������ glVertex ������ ���������������.
	glVertex3f(-1.0f, 1.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 0.0f);
	glEnd();//��������� �������� ������
	glFlush();
}

int main(int argc, char **argv)
{
	// ������������� GLUT � �������� ����
	glutInit(&argc, argv); //������� ��������� ������� main.
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);//������������� ������� 
	glutInitWindowSize(600, 600);//������ ����
	glutCreateWindow("Polygon");//�������� ���� � ���������� ���� �har
	glutDisplayFunc(Draw);//�������, ������������� ��������� ����. ��� ������ � ���� ���������� �������, ���������� ����������� ����� ����������� ���������� ��� � ����� ���� � ������� ���������
	Initialize();
	// �������� ���� GLUT
	glutMainLoop(); //�������, ����������� �������� ����, ����������� ��� � �������� ����

	return 0;
}
