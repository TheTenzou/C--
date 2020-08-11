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


void coordinates(float x1, float y1, float x2, float y2, float stepX, float stepY)
{
	glColor3f(0.0, 0, 0);
	glBegin(GL_QUADS);//���������, ��� ����� ��������. GL_QUADS: ������ ������ ������ glVertex ������ ���������������. GL_LINE_LOOP: �������� ��������.
	glVertex2f(x1, fabs(y1 - y2) / 2 + (y1 < y2 ? y1 : y2) + 1);
	glVertex2f(x1, fabs(y1 - y2) / 2 + (y1 < y2 ? y1 : y2) - 1);
	glVertex2f(x2, fabs(y1 - y2) / 2 + (y1 < y2 ? y1 : y2) - 1);
	glVertex2f(x2, fabs(y1 - y2) / 2 + (y1 < y2 ? y1 : y2) + 1);

	glVertex2f(fabs(x1 - x2) / 2 + (x1 < x2 ? x1 : x2) + 1, y1);
	glVertex2f(fabs(x1 - x2) / 2 + (x1 < x2 ? x1 : x2) - 1, y1);
	glVertex2f(fabs(x1 - x2) / 2 + (x1 < x2 ? x1 : x2) - 1, y2);
	glVertex2f(fabs(x1 - x2) / 2 + (x1 < x2 ? x1 : x2) + 1, y2);

	float y = fabs(y1 - y2) / 2 + (y1 < y2 ? y1 : y2);
	for (float x = fabs(x1 - x2) / 2 + (x1 < x2 ? x1 : x2) + stepX; x < (x1 > x2 ? x1 : x2); x += stepX)
	{
		glVertex2f(x - 1, y - 3);
		glVertex2f(x - 1, y + 3);
		glVertex2f(x + 1, y + 3);
		glVertex2f(x + 1, y - 3);
	}
	for (float x = fabs(x1 - x2) / 2 + (x1 < x2 ? x1 : x2) + stepX; x > (x1 < x2 ? x1 : x2); x -= stepX)
	{
		glVertex2f(x - 1, y - 3);
		glVertex2f(x - 1, y + 3);
		glVertex2f(x + 1, y + 3);
		glVertex2f(x + 1, y - 3);
	}
	float x = fabs(x1 - x2) / 2 + (x1 < x2 ? x1 : x2);
	for (float y = fabs(y1 - y2) / 2 + (y1 < y2 ? y1 : y2) + stepY; y < (y1 > y2 ? y1 : y2); y += stepY)
	{
		glVertex2f(x - 3, y - 1);
		glVertex2f(x - 3, y + 1);
		glVertex2f(x + 3, y + 1);
		glVertex2f(x + 3, y - 1);
	}
	for (float y = fabs(y1 - y2) / 2 + (y1 < y2 ? y1 : y2) + stepY; y > (y1 < y2 ? y1 : y2); y -= stepY)
	{
		glVertex2f(x - 3, y - 1);
		glVertex2f(x - 3, y + 1);
		glVertex2f(x + 3, y + 1);
		glVertex2f(x + 3, y - 1);
	}
	glEnd(); //��������� �������� �������
}

void DrawDot(float x, float y, float r, int FillFlag) // ������
{

	glBegin(FillFlag ? GL_POLYGON : GL_LINE_LOOP);
	int k = 25;
	for (int i = 0; i < k; i++)
	{
		glVertex2f(x + r * cos(2 * PI / k * i), (y + r * sin(2 * PI / k * i)));
	}
	glEnd();
}

void grafDots(float x1, float y1, float x2, float y2, float stepX, float stepY, float drawStepX, float drawStepY)
{
	float centreX = fabs(x1 - x2) / 2 + (x1 < x2 ? x1 : x2);
	float centreY = fabs(y1 - y2) / 2 + (y1 < y2 ? y1 : y2);
	
	float r = 3;
	

	for (float x = 0; x <= x2 + centreX; x += drawStepX)
	{
		glBegin(GL_POLYGON);
		int k = 12;
		for (int i = 0; i < k; i++)
		{
			glVertex2f(x +centreX + r * cos(2 * PI / k * i), ( (pow(2, asin(x/ stepX))) *stepX + centreY +  r * sin(2 * PI / k * i)));
		}
		glEnd();
	}

	for (float x = 0; x >= x1 - centreX; x -= drawStepX)
	{
		glBegin(GL_POLYGON);
		int k = 12;
		for (int i = 0; i < k; i++)
		{
			glVertex2f(x + centreX + r * cos(2 * PI / k * i), ((pow(2, asin(x / stepX))) *stepX + centreY + r * sin(2 * PI / k * i)));
		}
		glEnd();
	}
}

void grafLine(float x1, float y1, float x2, float y2, float stepX, float stepY, float drawStepX, float drawStepY)
{
	float centreX = fabs(x1 - x2) / 2 + (x1 < x2 ? x1 : x2);
	float centreY = fabs(y1 - y2) / 2 + (y1 < y2 ? y1 : y2);


	glBegin(GL_LINE_STRIP);
	for (float x = 0; x < x2 + centreX; x += drawStepX)
	{
		glVertex2f(x + centreX, (pow(2, asin(x / stepX))) *stepX + centreY);
	}
	glEnd();

	glBegin(GL_LINE_STRIP);
	for (float x = 0; x > x1 - centreX; x -= drawStepX)
	{
		glVertex2f(x + centreX, (pow(2, asin(x / stepX))) *stepX + centreY);
	}
	glEnd();
}

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




void Display(void)
{
	int i;
	float x1, y1, x2, y2;
	float r, g, b;

	srand(Seed);

	glClearColor(1, 1, 1, 0);     //������ �������� ������� ������ ������ �����.
	glClear(GL_COLOR_BUFFER_BIT); //������� ��������� ������. GL_COLOR_BUFFER_BIT - ������� ������ �����
	coordinates(20, 20, 880, 580, 75, 75);
	if (FillFlag)
	{
		grafLine(20, 20, 880, 580, 75, 75, 1, 1);
	}
	else
	{
		grafDots(20, 20, 880, 580, 75, 75, 10, 10);
	}
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

