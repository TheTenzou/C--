#include <glut.h>
#include "stdlib.h"

// ��������� ��������� ����
float mat1_dif[] = { 0.0f, 0.4f, 0.9f };
float mat1_amb[] = { 0.2f, 0.2f, 0.2f };
float mat1_spec[] = { 0.6f, 0.6f, 0.6f };
float mat1_shininess = 0.5f * 128;

// ��������� ��������� ������
float mat2_dif[] = { 1.0f, 1.0f, 1.0f };
float mat2_amb[] = { 0.2f, 0.2f, 0.2f };
float mat2_spec[] = { 0.6f, 0.6f, 0.6f };
float mat2_shininess = 0.7f * 128;

// ��������� ��������� ����
float mat3_dif[] = { 0.9f, 0.7f, 0.0f };
float mat3_amb[] = { 0.2f, 0.2f, 0.2f };
float mat3_spec[] = { 0.6f, 0.6f, 0.6f };
float mat3_shininess = 0.2f * 128;

void init(void) //������������� ���������
{
	GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);  //������� ���������
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);  //�������� ���������
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular); //����������� ����������
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);  // ������� ��������� �����

	glEnable(GL_LIGHTING);  //���������
	glEnable(GL_LIGHT0);  //���������
	glEnable(GL_DEPTH_TEST); //�������� �������� �� �������
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //���������� ��� ����� �������� ��� ������ ����� � ������
	glPushMatrix();//���������� ������� ��������� �������

		glRotatef(20.0, 1.0, 0.0, 0.0); //������� ����� ������
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat1_amb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat1_dif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat1_spec);
		glMaterialf(GL_FRONT, GL_SHININESS, mat1_shininess);
		glPushMatrix();//���������� ������� ��������� �������
			glTranslatef(-0.75, 0.3, 0.0); //�������� ���� �1
			glRotatef(90.0, 1.0, 0.0, 0.0); // ������� �����
			glutSolidTorus(0.275, 0.85, 30, 30); //������ ��� �1
			glTranslatef(0.0, 0.0, -0.43); //�������� ���� �2
			glutSolidTorus(0.175, 0.75, 30, 30); //������ ��� �2
		glPopMatrix();//����������� ����������� �������� �������

		glMaterialfv(GL_FRONT, GL_AMBIENT, mat2_amb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat2_dif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat2_spec);
		glMaterialf(GL_FRONT, GL_SHININESS, mat2_shininess);
		glPushMatrix();//���������� ������� ��������� �������
			glTranslatef(-0.75, -0.5, 0.0); //�������� ������
			glRotatef(270.0, 1.0, 0.0, 0.0); //������� ������
			glutSolidCone(1.0, 2.0, 15, 15); //������ �����
		glPopMatrix();//����������� ����������� �������� �������

		glMaterialfv(GL_FRONT, GL_AMBIENT, mat3_amb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat3_dif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat3_spec);
		glMaterialf(GL_FRONT, GL_SHININESS, mat3_shininess);
		glPushMatrix();//���������� ������� ��������� �������
			glTranslatef(0.75, 0.0, -1.0); // �������� ����
			glutSolidSphere(1.0, 15, 15); // ������ ���
			glTranslatef(2, -2, -5); // �������� ����
			glutSolidSphere(0.7, 15, 15); // ������ ���
		glPopMatrix();//����������� ����������� �������� �������
	glPopMatrix();//����������� ����������� �������� �������
	glFlush();
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h); //����� ����� �������������� �� ���� ������� ������ ����
	glMatrixMode(GL_PROJECTION);			//����� ��������� �����: ����� ���������� �������, ��� ������� �� � ���������� ����� ����������� ��������. GL_PROJECTION � ������� ��������. 
	glLoadIdentity();						//������� �������. ������� �������� ������� ������� �� ���������
	gluPerspective(40.0, (GLfloat)w / h, 1, 100.0); // ��������� ������������� �������� ���������� ������ �� ���������
	glMatrixMode(GL_MODELVIEW); // ������������� � �������� ������� ������� �������� - ������� �������
	glLoadIdentity(); //������� �������. ������� �������� ������� ������� �� ���������
	gluLookAt(0.0f, 0.0f, 8.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27: exit(0); break;
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv); //������� ��������� ������� main.
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH); //������������� ������� 
	glutInitWindowSize(500, 500);//������ ����
	glutCreateWindow(argv[0]);//�������� ����
	init();
	glutReshapeFunc(reshape);//�������, ������������� ��������� ����. ��� ������ � ���� ���������� �������, ���������� ����������� ����� ����������� ���������� ��� � ����� ���� � ������� ���������. 
	glutDisplayFunc(display);//��������� ���� � ������� "���������". ���������� ��, ����� ����������/������������ ���������� ����.
	glutKeyboardFunc(keyboard);//������ � �����������
	glutMainLoop();
	return 0;
}
