#include <stdlib.h>
#include <glut.h>

#ifdef random
#undef random
#endif

#define random(m) (float)rand()*m/RAND_MAX // макрос рандома


GLint Width = 512, Height = 512; //размер окна
int   Times = 100;  //Колличество объектов
int   FillFlag = 1; //флаг заполнения
long  Seed = 0; //сид 


void DrawRect(float x1, float y1, float x2, float y2, int FillFlag)
{
	glBegin(FillFlag ? GL_QUADS : GL_LINE_LOOP);//Указываем, как будем рисовать. GL_QUADS: каждые четыре вызова glVertex задают четырехугольник. GL_LINE_LOOP: рисуется ломанная.
	glVertex2f(x1, y1);
	glVertex2f(x2, y1);
	glVertex2f(x2, y2);
	glVertex2f(x1, y2);
	glEnd();//Закончили рисовать объекты
}

void Display(void)
{
	int i;
	float x1, y1, x2, y2;
	float r[2], g[2], b[2];

	srand(Seed);

	glClearColor(0, 0, 0, 0);     //Задает значения очистки цветом буфера цвета.
	glClear(GL_COLOR_BUFFER_BIT); //Очищает указанные буферы. GL_COLOR_BUFFER_BIT - Очистка буфера цвета

	int size = 10; //Размер квадрата
	x1 = 2;			//Координаты первого
	y1 = 2;
	x2 = x1 + size;
	y2 = y1 + size;

	int step = 2;// Шаг
	
	//Первый цвет
	r[0] = random(1);
	g[0] = random(1);
	b[0] = random(1);
	//Второй цвет
	r[1] = random(1);
	g[1] = random(1);
	b[1] = random(1);
	int k = 0;
	for (int i = 0; i < 99; i++)
	{
		for (int j = 0; j < 99; j++)
		{
			glColor3f(r[k], g[k], b[k]); //Устанавливаем цвет
			DrawRect(x1, y1, x2, y2, FillFlag); //Рисуем квадрат
			x1 = x1 + size + step; //меняем позиции
			x2 = x2 + size + step;
			k = !k;//меняем цвет
		}
		x1 = 2;//меняем позиции
		x2 = x1 + size;
		y1 = y1 + size + step;
		y2 = y2 + size + step;
	}
	glFinish();//Гарантирует то, что все предыдущие команды gl будут выполнены. 
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
	glutCreateWindow("Rect draw example (RGB)"); //Создание окна с заголовком типа сhar

	// регистрация обратных вызовов
	glutDisplayFunc(Display);   //Связываем окно с выводом "рисования". Вызывается ОС, чтобы нарисовать/перерисовать содержимое окна.
	glutReshapeFunc(Reshape);   //Функция, отслеживающая изменения окна. Как только у окна изменились размеры, необходимо перестроить вывод графической информации уже в новое окно с другими размерами. 
	glutKeyboardFunc(Keyboard); //Работа с клавиатурой
	glutMouseFunc(Mouse);       //Работа с мышью   

	// Основной цикл GLUT
	glutMainLoop(); //функция, завершающая описание окна, переводящая нас в основной цикл
}

