#include <stdlib.h>
#include <glut.h>
#include <math.h>


#ifdef random
#undef random
#endif

#define random(m) (float)rand()*m/RAND_MAX
#define PI 3.14159265

GLint Width = 900, Height = 600;	//Размер окна			
int   FillFlag = 1;	//Переменная для определения стиля изображения
long  Seed = 0;  //сид 


void coordinates(float x1, float y1, float x2, float y2, float stepX, float stepY)
{
	glColor3f(0.0, 0, 0);
	glBegin(GL_QUADS);//Указываем, как будем рисовать. GL_QUADS: каждые четыре вызова glVertex задают четырехугольник. GL_LINE_LOOP: рисуется ломанная.
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
	glEnd(); //Закончили рисовать объекты
}

void DrawDot(float x, float y, float r, int FillFlag) // звезда
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
	glBegin(FillFlag ? GL_QUADS : GL_LINE_LOOP);//Указываем, как будем рисовать. GL_QUADS: каждые четыре вызова glVertex задают четырехугольник. GL_LINE_LOOP: рисуется ломанная.
	glVertex2f(x1, y1);
	glVertex2f(x2, y1);
	glVertex2f(x2, y2);
	glVertex2f(x1, y2);
	glEnd(); //Закончили рисовать объекты
}




void Display(void)
{
	int i;
	float x1, y1, x2, y2;
	float r, g, b;

	srand(Seed);

	glClearColor(1, 1, 1, 0);     //Задает значения очистки цветом буфера цвета.
	glClear(GL_COLOR_BUFFER_BIT); //Очищает указанные буферы. GL_COLOR_BUFFER_BIT - Очистка буфера цвета
	coordinates(20, 20, 880, 580, 75, 75);
	if (FillFlag)
	{
		grafLine(20, 20, 880, 580, 75, 75, 1, 1);
	}
	else
	{
		grafDots(20, 20, 880, 580, 75, 75, 10, 10);
	}
	glFinish(); //Гарантирует то, что все предыдущие команды gl будут выполнены
}

void Reshape(GLint w, GLint h)
{
	Width = w;
	Height = h;

	glViewport(0, 0, w, h);         //Вывод будет осуществляться во всей области нашего окна

	glMatrixMode(GL_PROJECTION);    //Задаём матричный режим: будет определена матрица, над которой мы в дальнейшем будем производить операции. GL_PROJECTION – матрица проекций. 
	glLoadIdentity();               //Очищаем матрицу. функция заменяет текущую матрицу на единичную
	glOrtho(0, w, 0, h, -1.0, 1.0); //Выполняет ортогональную проекцию указанного объема на плоскость

	glMatrixMode(GL_MODELVIEW);     //Устанавливаем в качестве текущей матрицы объектно-видовую матрицу 
	glLoadIdentity();               //Очищаем матрицу. функция заменяет текущую матрицу на единичную
}

void Mouse(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN) //Проверяем, нажата ли кнопка мыши
	{
		switch (button)
		{
		case GLUT_LEFT_BUTTON: //Если нажата левая конпка мыши
			Seed = random(RAND_MAX);
			break;
		case GLUT_RIGHT_BUTTON: //Если нажата правая конпка мыши
			FillFlag = !FillFlag; //"Меняем" рисунок
			break;
		}
		glutPostRedisplay(); //Помечает активное окно, которое должно быть перерисовано, для вызова основного цикла
	}
}


void Keyboard(unsigned char key, int x, int y)
{
#define ESCAPE '\033' //Инициализация клавиши escape

	if (key == ESCAPE) //Проверяем нажата ли она 
		exit(0);    //Если да, то закрываем окно
}

int main(int argc, char *argv[])
{
	// инициализация GLUT и создание окна
	glutInit(&argc, argv); //Передаём параметры функции main.
	glutInitDisplayMode(GLUT_RGB);     //Инициализация дисплея 
	glutInitWindowSize(Width, Height); //Размер окна
	glutCreateWindow("Flag"); //Создание окна с заголовком типа сhar

	// регистрация обратных вызовов
	glutDisplayFunc(Display);   //Связываем окно с выводом "рисования". Вызывается ОС, чтобы нарисовать/перерисовать содержимое окна.
	glutReshapeFunc(Reshape);   //Функция, отслеживающая изменения окна. Как только у окна изменились размеры, необходимо перестроить вывод графической информации уже в новое окно с другими размерами. 
	glutKeyboardFunc(Keyboard); //Работа с клавиатурой
	glutMouseFunc(Mouse);       //Работа с мышью   

	// Основной цикл GLUT
	glutMainLoop(); //функция, завершающая описание окна, переводящая нас в основной цикл
}

