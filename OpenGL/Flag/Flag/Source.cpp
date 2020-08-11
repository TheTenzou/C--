#include <stdlib.h>
#include <glut.h>
#include <math.h>


#ifdef random
#undef random
#endif

#define random(m) (float)rand()*m/RAND_MAX
#define PI 3.14159265

GLint Width = 900, Height = 600;	//������ ����			
int   FillFlag = 1;	//���������� ��� ����������� ����� �����������
long  Seed = 0;  //��� 


void DrawRect(float x1, float y1, float x2, float y2,
	int FillFlag)
{
	glBegin(FillFlag ? GL_QUADS : GL_LINE_LOOP);//���������, ��� ����� ��������. GL_QUADS: ������ ������ ������ glVertex ������ ���������������. GL_LINE_LOOP: �������� ��������.
	glVertex2f(x1, y1);
	glVertex2f(x2, y1);
	glVertex2f(x2, y2);
	glVertex2f(x1, y2);
	glEnd(); //��������� �������� �������
}

void DrawStar(float x, float y, float R , int FillFlag) // ������
{	
	float r = (cos(PI / 5 * 2)) / (cos(PI / 5))*R;
	glBegin(FillFlag ? GL_POLYGON : GL_LINE_LOOP);
	glVertex2f(x + r * cos(double(54 * PI / 180)), y + r * sin(double(54 * PI / 180)));		//inner 3
	glVertex2f(x, y + R);																	//outer top 1
	glVertex2f(x - r * cos(double(54 * PI / 180)), y + r * sin(double(54 * PI / 180)));		//inner 4
	glVertex2f(x - R * cos(double(18 * PI / 180)), y + R * sin(double(18 * PI / 180)));		//outer 2
	glVertex2f(x - r * cos(double(18 * PI / 180)), y - r * sin(double(18 * PI / 180)));		//inner 5
	glVertex2f(x - R * cos(double(54 * PI / 180)), y - R * sin(double(54 * PI / 180)));		//outer 3
	glVertex2f(x, y - r);																	//inner bot 1
	glVertex2f(x + R * cos(double(54 * PI / 180)), y - R * sin(double(54 * PI / 180)));		//outer 4
	glVertex2f(x + r * cos(double(18 * PI / 180)), y - r * sin(double(18 * PI / 180)));		//inner 2
	glVertex2f(x + R * cos(double(18 * PI / 180)), y + R * sin(double(18 * PI / 180)));		//outer 5
	glEnd();
}


void Display(void)
{
	int i;
	float x1, y1, x2, y2;
	float r, g, b;

	srand(Seed);

	glClearColor(0, 0, 0, 0);     //������ �������� ������� ������ ������ �����.
	glClear(GL_COLOR_BUFFER_BIT); //������� ��������� ������. GL_COLOR_BUFFER_BIT - ������� ������ �����


	r = 0;
	g = 0;
	b = 0;
	glColor3f(r, g, b);
	DrawRect(0, 0, 900, 200, 1);
	r = 1;
	g = 1;
	b = 1;
	glColor3f(r, g, b);
	DrawRect(0, 200, 900, 400, 1);
	r = (float)206/256;
	g = (float)17/256;
	b = (float)38/256;
	glColor3f(r, g, b);
	DrawRect(0, 400, 900, 600, 1);

	r = (float)0 / 256;
	g = (float)122 / 256;
	b = (float)61/ 256;
	glColor3f(r, g, b);
	DrawStar(270, 300, 70, 1);
	DrawStar(630, 300, 70, 1);



	glFinish(); //����������� ��, ��� ��� ���������� ������� gl ����� ���������
}

void Reshape(GLint w, GLint h)
{
	Width = w;
	Height = h;

	glViewport(0, 0, w, h);         //����� ����� �������������� �� ���� ������� ������ ����

	glMatrixMode(GL_PROJECTION);    //����� ��������� �����: ����� ���������� �������, ��� ������� �� � ���������� ����� ����������� ��������. GL_PROJECTION � ������� ��������. 
	glLoadIdentity();               //������� �������. ������� �������� ������� ������� �� ���������
	glOrtho(0, w, 0, h, -1.0, 1.0); //��������� ������������� �������� ���������� ������ �� ���������

	glMatrixMode(GL_MODELVIEW);     //������������� � �������� ������� ������� ��������-������� ������� 
	glLoadIdentity();               //������� �������. ������� �������� ������� ������� �� ���������
}

void Mouse(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN) //���������, ������ �� ������ ����
	{
		switch (button)
		{
		case GLUT_LEFT_BUTTON: //���� ������ ����� ������ ����
			Seed = random(RAND_MAX);
			break;
		case GLUT_RIGHT_BUTTON: //���� ������ ������ ������ ����
			FillFlag = !FillFlag; //"������" �������
			break;
		}
		glutPostRedisplay(); //�������� �������� ����, ������� ������ ���� ������������, ��� ������ ��������� �����
	}
}


void Keyboard(unsigned char key, int x, int y)
{
#define ESCAPE '\033' //������������� ������� escape

	if (key == ESCAPE) //��������� ������ �� ��� 
		exit(0);    //���� ��, �� ��������� ����
}

int main(int argc, char *argv[])
{
	// ������������� GLUT � �������� ����
	glutInit(&argc, argv); //������� ��������� ������� main.
	glutInitDisplayMode(GLUT_RGB);     //������������� ������� 
	glutInitWindowSize(Width, Height); //������ ����
	glutCreateWindow("Flag"); //�������� ���� � ���������� ���� �har

	// ����������� �������� �������
	glutDisplayFunc(Display);   //��������� ���� � ������� "���������". ���������� ��, ����� ����������/������������ ���������� ����.
	glutReshapeFunc(Reshape);   //�������, ������������� ��������� ����. ��� ������ � ���� ���������� �������, ���������� ����������� ����� ����������� ���������� ��� � ����� ���� � ������� ���������. 
	glutKeyboardFunc(Keyboard); //������ � �����������
	glutMouseFunc(Mouse);       //������ � �����   

	// �������� ���� GLUT
	glutMainLoop(); //�������, ����������� �������� ����, ����������� ��� � �������� ����
}

