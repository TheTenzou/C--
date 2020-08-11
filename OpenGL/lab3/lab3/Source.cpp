#include <glut.h>
#include "stdlib.h"

// параметры материала тора
float mat1_dif[] = { 0.0f, 0.4f, 0.9f };
float mat1_amb[] = { 0.2f, 0.2f, 0.2f };
float mat1_spec[] = { 0.6f, 0.6f, 0.6f };
float mat1_shininess = 0.5f * 128;

// параметры материала конуса
float mat2_dif[] = { 1.0f, 1.0f, 1.0f };
float mat2_amb[] = { 0.2f, 0.2f, 0.2f };
float mat2_spec[] = { 0.6f, 0.6f, 0.6f };
float mat2_shininess = 0.7f * 128;

// параметры материала шара
float mat3_dif[] = { 0.9f, 0.7f, 0.0f };
float mat3_amb[] = { 0.2f, 0.2f, 0.2f };
float mat3_spec[] = { 0.6f, 0.6f, 0.6f };
float mat3_shininess = 0.2f * 128;

void init(void) //Инициализация освешения
{
	GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);  //фоновое освешение
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);  //дифузное освешение
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular); //зеркального обаржаения
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);  // позиция источника света

	glEnable(GL_LIGHTING);  //освешение
	glEnable(GL_LIGHT0);  //освешение
	glEnable(GL_DEPTH_TEST); //включаем проверку на глубину
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //обозначаем что буфер доступен для записи цвета и глбины
	glPushMatrix();//Сохранение ткошего состояния матрицы

		glRotatef(20.0, 1.0, 0.0, 0.0); //поворот точки обзора
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat1_amb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat1_dif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat1_spec);
		glMaterialf(GL_FRONT, GL_SHININESS, mat1_shininess);
		glPushMatrix();//Сохранение ткошего состояния матрицы
			glTranslatef(-0.75, 0.3, 0.0); //смешение тора №1
			glRotatef(90.0, 1.0, 0.0, 0.0); // поворот торов
			glutSolidTorus(0.275, 0.85, 30, 30); //рисуем тор №1
			glTranslatef(0.0, 0.0, -0.43); //смешение тора №2
			glutSolidTorus(0.175, 0.75, 30, 30); //рисуем тор №2
		glPopMatrix();//возврашение предыдушего значения матрицы

		glMaterialfv(GL_FRONT, GL_AMBIENT, mat2_amb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat2_dif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat2_spec);
		glMaterialf(GL_FRONT, GL_SHININESS, mat2_shininess);
		glPushMatrix();//Сохранение ткошего состояния матрицы
			glTranslatef(-0.75, -0.5, 0.0); //смешение конуса
			glRotatef(270.0, 1.0, 0.0, 0.0); //поворот конуса
			glutSolidCone(1.0, 2.0, 15, 15); //рисуем конус
		glPopMatrix();//возврашение предыдушего значения матрицы

		glMaterialfv(GL_FRONT, GL_AMBIENT, mat3_amb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat3_dif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat3_spec);
		glMaterialf(GL_FRONT, GL_SHININESS, mat3_shininess);
		glPushMatrix();//Сохранение ткошего состояния матрицы
			glTranslatef(0.75, 0.0, -1.0); // смешение шара
			glutSolidSphere(1.0, 15, 15); // рисуем шар
			glTranslatef(2, -2, -5); // смешение шара
			glutSolidSphere(0.7, 15, 15); // рисуем шар
		glPopMatrix();//возврашение предыдушего значения матрицы
	glPopMatrix();//возврашение предыдушего значения матрицы
	glFlush();
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h); //Вывод будет осуществляться во всей области нашего окна
	glMatrixMode(GL_PROJECTION);			//Задаём матричный режим: будет определена матрица, над которой мы в дальнейшем будем производить операции. GL_PROJECTION – матрица проекций. 
	glLoadIdentity();						//Очищаем матрицу. функция заменяет текущую матрицу на единичную
	gluPerspective(40.0, (GLfloat)w / h, 1, 100.0); // Выполняет ортогональную проекцию указанного объема на плоскость
	glMatrixMode(GL_MODELVIEW); // Устанавливаем в качестве текущей матрицы объектно - видовую матрицу
	glLoadIdentity(); //Очищаем матрицу. функция заменяет текущую матрицу на единичную
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
	glutInit(&argc, argv); //Передаём параметры функции main.
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH); //Инициализация дисплея 
	glutInitWindowSize(500, 500);//Размер окна
	glutCreateWindow(argv[0]);//Создание окна
	init();
	glutReshapeFunc(reshape);//Функция, отслеживающая изменения окна. Как только у окна изменились размеры, необходимо перестроить вывод графической информации уже в новое окно с другими размерами. 
	glutDisplayFunc(display);//Связываем окно с выводом "рисования". Вызывается ОС, чтобы нарисовать/перерисовать содержимое окна.
	glutKeyboardFunc(keyboard);//Работа с клавиатурой
	glutMainLoop();
	return 0;
}
