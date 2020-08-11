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

void DrawStar(float x, float y, float R , int FillFlag) // звезда
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

	glClearColor(0, 0, 0, 0);     //Задает значения очистки цветом буфера цвета.
	glClear(GL_COLOR_BUFFER_BIT); //Очищает указанные буферы. GL_COLOR_BUFFER_BIT - Очистка буфера цвета


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

