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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//Очищает указанные буферы. GL_COLOR_BUFFER_BIT - Очистка буфера цвета
	glPushMatrix();
	glTranslatef(1.0f, 1.0f, 0.0f);
	glRotatef(-45, 0.0f, 1.0f, 0.0f);
	glRotatef(65, 1.0f, 0.0f, 0.0f);
	glBegin(GL_TRIANGLES); //Указываем, как будем рисовать. GL_TRIANGLES: каждые три вызова glVertex задают треугольник.
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 0.0f);
	glEnd();//Закончили рисовать объект
	glPopMatrix();
	glTranslatef(-1.0f, 0.0f, 0.0f);
	glColor3f(0.5f, 0.5f, 1.0f);
	glRotatef(65, 1.0f, 0.0f, 0.0f);
	glRotatef(0, 0.0f, 1.0f, 0.0f);
	glRotatef(35, 0.0f, 0.0f, 1.0f);
	glBegin(GL_QUADS);//Указываем, как будем рисовать. GL_QUADS: каждые четыре вызова glVertex задают четырехугольник.
	glVertex3f(-1.0f, 1.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 0.0f);
	glEnd();//Закончили рисовать объект
	glFlush();
}

int main(int argc, char **argv)
{
	// инициализация GLUT и создание окна
	glutInit(&argc, argv); //Передаём параметры функции main.
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);//Инициализация дисплея 
	glutInitWindowSize(600, 600);//Размер окна
	glutCreateWindow("Polygon");//Создание окна с заголовком типа сhar
	glutDisplayFunc(Draw);//Функция, отслеживающая изменения окна. Как только у окна изменились размеры, необходимо перестроить вывод графической информации уже в новое окно с другими размерами
	Initialize();
	// Основной цикл GLUT
	glutMainLoop(); //функция, завершающая описание окна, переводящая нас в основной цикл

	return 0;
}
