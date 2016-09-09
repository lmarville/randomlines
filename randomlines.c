#include <stdio.h>
#include <glut/glut.h>
#include <math.h>
#include <time.h>

int window_id;
float r,g,b;
int width, height;

float rando();

GLfloat xRotated, yRotated, zRotated;

void Display(void)
{
	int i;
	float w,h;
	w=(float)glutGet(GLUT_SCREEN_WIDTH);
	h=(float)glutGet(GLUT_SCREEN_HEIGHT);
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(-w/2,-h/2,-500.0);
	//glViewport(0,0,GLUT_SCREEN_WIDTH,GLUT_SCREEN_HEIGHT);
	//glOrtho(-0.5,0.5,-0.5,0.5,-1.0,1.0);
	//glRotatef(xRotated,1.0,0.0,0.0);
	//glRotatef(yRotated,0.0,1.0,0.0);
	//glRotatef(zRotated,0.0,0.0,1.0);

	glBegin(GL_LINES);
		glColor3f(1,1,1);
		glVertex2f(0, 0);
		glVertex2f(0, h);
		glVertex2f(0, h);
		glVertex2f(w, h);
		glVertex2f(w, h);
		glVertex2f(w, 0);
		glVertex2f(w, 0);
		glVertex2f(0, 0);
	glEnd();

	glBegin(GL_LINES);
	for(i=0;i<5000;i++) {
		glColor3f(rando(),rando(),rando());
		glVertex2f(rando()*w, rando()*h);
		glVertex2f(rando()*w, rando()*h);
	}
	glEnd();


	glFlush();
	//glutSwapBuffers();
}

void Reshape(int x, int y)
{
	if (y == 0 || x == 0) return;
	width=x; height = y;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(40.0,(GLdouble)x/(GLdouble)y,0.1,2000.0);
	glMatrixMode(GL_MODELVIEW);
	glViewport(0,0,x,y);  //Use the whole window for rendering
}

void Keyboard(unsigned char key, int x, int y) {
	switch(key) {
			case 27:
			glutDestroyWindow(window_id);
			exit(0);
			break;

			default:
			break;
		}
}

void Idle(void)
{
	xRotated += 0.3;
	yRotated += 0.1;
	zRotated += -0.4;
	sleep(1);
	Display();
}

int main (int argc, char **argv)
{

	//Initialize
	srand (time(NULL));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	int Maxx = glutGet(GLUT_SCREEN_WIDTH);
	int Maxy = glutGet(GLUT_SCREEN_HEIGHT);

	glutInitWindowSize(10,10);
	//printf("Screen is %d by %d\n",Maxx,Maxy);
	//printf("RAND MAX is %d\n",RAND_MAX);

	window_id = glutCreateWindow("Draw something...");
	glutFullScreen();

	xRotated = yRotated = zRotated = 0.0;
	glLineWidth(3.0);

	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutIdleFunc(Idle);
	glutKeyboardFunc(Keyboard);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	r = rando(); g = rando(); b = rando();
	glutMainLoop();

	return 0;
}

float rando() {
	return((float)(rand() % 5000) / 5000.0);
}
