#include <glut.h>
#include <math.h>

#define PI 3.14159265

void reshape(int w, int h)
{
	glViewport(0, 0 ,w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, w, 0, h);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


void DrawRectGrad(float x1, float y1, float x2, float y2,
	int FillFlag)
{
	glBegin(FillFlag ? GL_QUADS : GL_LINE_LOOP);//Указываем, как будем рисовать. GL_QUADS: каждые четыре вызова glVertex задают четырехугольник. GL_LINE_LOOP: рисуется ломанная.
	glColor3f(1.0, 1.0, 1.0);
	glVertex2i(x1, y2);
	glColor3f(0.0, 0.0, 1.0);
	glVertex2i(x1, y1);
	glColor3f(0.0, 1.0, 0.0);
	glVertex2i(x2, y1);
	glColor3f(1.0, 0.0, 0.0);
	glVertex2i(x2, y2);
	glEnd(); //Закончили рисовать объекты
	
}

void DrawStar(float x, float y, float R, int FillFlag) // звезда
{
	float r = (cos(PI / 5 * 2)) / (cos(PI / 5))*R;

	GLfloat outer_corner_top[]			= { 1.0, 1.0, 0.0 };
	GLfloat outer_corner_left[]			= { 0.0, 0.8, 0.3 };
	GLfloat outer_corner_buttom_left[]  = { 0.0, 1.0, 1.0 };
	GLfloat outer_corner_buttom_right[] = { 0.0, 0.0, 1.0 };
	GLfloat outer_corner_right[]		= { 1.0, 0.0, 0.0 };

/*	GLfloat iner_corner_buttom[]		= { 0.0, 0.0, 0.0 };
	GLfloat iner_corner_left[]			= { 0.0, 0.0, 0.0 };
	GLfloat iner_corner_top_left[]		= { 0.0, 0.0, 0.0 };
	GLfloat iner_corner_top_right[]		= { 0.0, 0.0, 0.0 };
	GLfloat iner_corner_right[]			= { 0.0, 0.0, 0.0 };*/

	//GLfloat centre[]					= { 1.0, 1.0, 1.0 };

	GLfloat iner_corner_buttom[] = { (outer_corner_buttom_left[0] + outer_corner_buttom_right[0]) / 2, (outer_corner_buttom_left[1] + outer_corner_buttom_right[1]) / 2, (outer_corner_buttom_left[2] + outer_corner_buttom_right[2]) / 2 };
	GLfloat iner_corner_left[] = { (outer_corner_left[0] + outer_corner_buttom_left[0]) / 2, (outer_corner_left[1] + outer_corner_buttom_left[1]) / 2, (outer_corner_left[2] + outer_corner_buttom_left[2]) / 2 };
	GLfloat iner_corner_top_left[] = { (outer_corner_left[0] + outer_corner_top[0]) / 2, (outer_corner_left[1] + outer_corner_top[1]) / 2, (outer_corner_left[2] + outer_corner_top[2]) / 2 };
	GLfloat iner_corner_top_right[] = { (outer_corner_top[0] + outer_corner_right[0]) / 2, (outer_corner_top[1] + outer_corner_right[1]) / 2, (outer_corner_top[2] + outer_corner_right[2]) / 2 };
	GLfloat iner_corner_right[] = { (outer_corner_right[0]+ outer_corner_buttom_right[0])/2, (outer_corner_right[1] + outer_corner_buttom_right[1]) / 2, (outer_corner_right[2] + outer_corner_buttom_right[2]) / 2 };
	
	GLfloat centre[] = { (outer_corner_top[0]+ outer_corner_left[0]+ outer_corner_buttom_left[0]+ outer_corner_buttom_right[0]+ outer_corner_right[0])/5,(outer_corner_top[1] + outer_corner_left[1] + outer_corner_buttom_left[1] + outer_corner_buttom_right[1] + outer_corner_right[1]) / 5, (outer_corner_top[2] + outer_corner_left[2] + outer_corner_buttom_left[2] + outer_corner_buttom_right[2] + outer_corner_right[2]) / 5 };

	glBegin(FillFlag ? GL_TRIANGLES : GL_LINE_LOOP);
	//=================================================================================
	//first outer trangle
	//right corner
	glColor3fv(iner_corner_top_right);
	glVertex2f(x + r * cos(double(54 * PI / 180)), y + r * sin(double(54 * PI / 180)));
	//outer corner
	glColor3fv(outer_corner_top);
	glVertex2f(x, y + R);
	//left corner
	glColor3fv(iner_corner_top_left);
	glVertex2f(x - r * cos(double(54 * PI / 180)), y + r * sin(double(54 * PI / 180)));	

	//second outer trangle
	//corner top right
	glColor3fv(iner_corner_top_left);
	glVertex2f(x - r * cos(double(54 * PI / 180)), y + r * sin(double(54 * PI / 180)));	
	//outer corner
	glColor3fv(outer_corner_left);
	glVertex2f(x - R * cos(double(18 * PI / 180)), y + R * sin(double(18 * PI / 180)));	
	//corner buttom left
	glColor3fv(iner_corner_left);
	glVertex2f(x - r * cos(double(18 * PI / 180)), y - r * sin(double(18 * PI / 180)));	

	//third outer trangle
	//top corner
	glColor3fv(iner_corner_left);
	glVertex2f(x - r * cos(double(18 * PI / 180)), y - r * sin(double(18 * PI / 180)));
	//outer corner
	glColor3fv(outer_corner_buttom_left);
	glVertex2f(x - R * cos(double(54 * PI / 180)), y - R * sin(double(54 * PI / 180)));
	//buttom corner
	glColor3fv(iner_corner_buttom);
	glVertex2f(x, y - r);

	//forth outer trangle
	//buttom corner
	glColor3fv(iner_corner_buttom);
	glVertex2f(x, y - r);
	//outer corner
	glColor3fv(outer_corner_buttom_right);
	glVertex2f(x + R * cos(double(54 * PI / 180)), y - R * sin(double(54 * PI / 180)));
	//top corner
	glColor3fv(iner_corner_right);
	glVertex2f(x + r * cos(double(18 * PI / 180)), y - r * sin(double(18 * PI / 180)));

	//fifth outer trangle
	//buttom corner
	glColor3fv(iner_corner_right);
	glVertex2f(x + r * cos(double(18 * PI / 180)), y - r * sin(double(18 * PI / 180)));
	//outer corner
	glColor3fv(outer_corner_right);
	glVertex2f(x + R * cos(double(18 * PI / 180)), y + R * sin(double(18 * PI / 180)));
	//top left corner
	glColor3fv(iner_corner_top_right);
	glVertex2f(x + r * cos(double(54 * PI / 180)), y + r * sin(double(54 * PI / 180)));

	//=================================================================================
	//first iner trangle
	//right corner
	glColor3fv(iner_corner_top_right);
	glVertex2f(x + r * cos(double(54 * PI / 180)), y + r * sin(double(54 * PI / 180)));
	//centre
	glColor3fv(centre);
	glVertex2f(x, y);
	//left corner
	glColor3fv(iner_corner_top_left);
	glVertex2f(x - r * cos(double(54 * PI / 180)), y + r * sin(double(54 * PI / 180)));

	//second iner trangle
	//corner top right
	glColor3fv(iner_corner_top_left);
	glVertex2f(x - r * cos(double(54 * PI / 180)), y + r * sin(double(54 * PI / 180)));
	//centre
	glColor3fv(centre);
	glVertex2f(x, y);
	//corner buttom left
	glColor3fv(iner_corner_left);
	glVertex2f(x - r * cos(double(18 * PI / 180)), y - r * sin(double(18 * PI / 180)));

	//third iner trangle
	//top corner
	glColor3fv(iner_corner_left);
	glVertex2f(x - r * cos(double(18 * PI / 180)), y - r * sin(double(18 * PI / 180)));
	//centre
	glColor3fv(centre);
	glVertex2f(x, y);
	//buttom corner
	glColor3fv(iner_corner_buttom);
	glVertex2f(x, y - r);

	//forth iner trangle
	//buttom corner
	glColor3fv(iner_corner_buttom);
	glVertex2f(x, y - r);
	//centre
	glColor3fv(centre);
	glVertex2f(x, y);
	//top corner
	glColor3fv(iner_corner_right);
	glVertex2f(x + r * cos(double(18 * PI / 180)), y - r * sin(double(18 * PI / 180)));

	//fifth iner trangle
	//buttom corner
	glColor3fv(iner_corner_right);
	glVertex2f(x + r * cos(double(18 * PI / 180)), y - r * sin(double(18 * PI / 180)));
	//centre
	glColor3fv(centre);
	glVertex2f(x, y);
	//top left corner
	glColor3fv(iner_corner_top_right);
	glVertex2f(x + r * cos(double(54 * PI / 180)), y + r * sin(double(54 * PI / 180)));

	/*
	glColor3f(1.0, 1.0, 1.0);
	glVertex2f(x + r * cos(double(54 * PI / 180)), y + r * sin(double(54 * PI / 180)));		//inner 3
	glColor3f(0.5, 1.0, 0.0);
	glVertex2f(x, y + R);																	//outer top 1
	glColor3f(0.75, 0.5, 0.0);
	glVertex2f(x - r * cos(double(54 * PI / 180)), y + r * sin(double(54 * PI / 180)));		//inner 4
	glColor3f(1.0, 0.0, 0.0);
	glVertex2f(x - R * cos(double(18 * PI / 180)), y + R * sin(double(18 * PI / 180)));		//outer 2
	glColor3f(1.0, 1.0, 1.0);
	glVertex2f(x - r * cos(double(18 * PI / 180)), y - r * sin(double(18 * PI / 180)));		//inner 5
	glColor3f(0.0, 0.0, 1.0);
	glVertex2f(x - R * cos(double(54 * PI / 180)), y - R * sin(double(54 * PI / 180)));		//outer 3
	glColor3f(0.0, 1.0, 0.0);
	glVertex2f(x, y - r);																	//inner bot 1
	glColor3f(1.0, 0.0, 0.0);
	glVertex2f(x + R * cos(double(54 * PI / 180)), y - R * sin(double(54 * PI / 180)));		//outer 4
	glColor3f(1.0, 1.0, 1.0);
	glVertex2f(x + r * cos(double(18 * PI / 180)), y - r * sin(double(18 * PI / 180)));		//inner 2
	glColor3f(0.0, 0.0, 1.0);
	glVertex2f(x + R * cos(double(18 * PI / 180)), y + R * sin(double(18 * PI / 180)));		//outer 5*/
	glEnd();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
	glTranslated(400,300,0);
	glRotated(10, 0, 0, 1);
	
	
	
	DrawStar(0, 0, 200, 1);
	glPopMatrix();
	
	//DrawRectGrad(250,150,550,450,1);
	
	glutSwapBuffers();
}

int main(int argc, char * argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Square");
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}