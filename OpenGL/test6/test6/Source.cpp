#include <stdlib.h>
#include <glut.h>

#ifdef random
#undef random
#endif

#define random(m) (float)rand()*m/RAND_MAX // ������ �������


GLint Width = 512, Height = 512; //������ ����
int   Times = 100;  //����������� ��������
int   FillFlag = 1; //���� ����������
long  Seed = 0; //��� 


void DrawRect(float x1, float y1, float x2, float y2, int FillFlag)
{
	glBegin(FillFlag ? GL_QUADS : GL_LINE_LOOP);//���������, ��� ����� ��������. GL_QUADS: ������ ������ ������ glVertex ������ ���������������. GL_LINE_LOOP: �������� ��������.
	glVertex2f(x1, y1);
	glVertex2f(x2, y1);
	glVertex2f(x2, y2);
	glVertex2f(x1, y2);
	glEnd();//��������� �������� �������
}

void Display(void)
{
	int i;
	float x1, y1, x2, y2;
	float r[2], g[2], b[2];

	srand(Seed);

	glClearColor(0, 0, 0, 0);     //������ �������� ������� ������ ������ �����.
	glClear(GL_COLOR_BUFFER_BIT); //������� ��������� ������. GL_COLOR_BUFFER_BIT - ������� ������ �����

	int size = 10; //������ ��������
	x1 = 2;			//���������� �������
	y1 = 2;
	x2 = x1 + size;
	y2 = y1 + size;

	int step = 2;// ���
	
	//������ ����
	r[0] = random(1);
	g[0] = random(1);
	b[0] = random(1);
	//������ ����
	r[1] = random(1);
	g[1] = random(1);
	b[1] = random(1);
	int k = 0;
	for (int i = 0; i < 99; i++)
	{
		for (int j = 0; j < 99; j++)
		{
			glColor3f(r[k], g[k], b[k]); //������������� ����
			DrawRect(x1, y1, x2, y2, FillFlag); //������ �������
			x1 = x1 + size + step; //������ �������
			x2 = x2 + size + step;
			k = !k;//������ ����
		}
		x1 = 2;//������ �������
		x2 = x1 + size;
		y1 = y1 + size + step;
		y2 = y2 + size + step;
	}
	glFinish();//����������� ��, ��� ��� ���������� ������� gl ����� ���������. 
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
	glutCreateWindow("Rect draw example (RGB)"); //�������� ���� � ���������� ���� �har

	// ����������� �������� �������
	glutDisplayFunc(Display);   //��������� ���� � ������� "���������". ���������� ��, ����� ����������/������������ ���������� ����.
	glutReshapeFunc(Reshape);   //�������, ������������� ��������� ����. ��� ������ � ���� ���������� �������, ���������� ����������� ����� ����������� ���������� ��� � ����� ���� � ������� ���������. 
	glutKeyboardFunc(Keyboard); //������ � �����������
	glutMouseFunc(Mouse);       //������ � �����   

	// �������� ���� GLUT
	glutMainLoop(); //�������, ����������� �������� ����, ����������� ��� � �������� ����
}

