#include <GL/glut.h>

/*
 * Name: Krishanu Saini
 * Roll: 190001029
 * Ques: Problem 2) House
 * Date: 13/01/22
 */ 

void Draw() {
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(10);
	
	/*-------- big_rectangle --------*/
	glColor3f(0.5, 0.3, 0);
	glBegin(GL_POLYGON);
	glVertex2i(200, 100);
	glVertex2i(200, 400);
	glVertex2i(600, 400);
	glVertex2i(600, 100);	
	glEnd();

	/*-------- roof_triangle --------*/
	glColor3f(0.5, 0.3, 0.5);
	glBegin(GL_POLYGON);
	glVertex2i(100, 401);
	glVertex2i(400, 700);
	glVertex2i(700, 401);
	glEnd();

	/*-------- door --------*/
	glColor3f(0, 0.2, 0.6);
	glBegin(GL_POLYGON);
	glVertex2i(360, 150);
	glVertex2i(360, 320);
	glVertex2i(440, 320);
	glVertex2i(440,150);
	glEnd();

	/*-------- door_knob --------*/
	glColor3f(0, 0, 0);
	glEnable(GL_POINT_SMOOTH);
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
	glBegin(GL_POINTS);
	glPointSize(10);
	glVertex2i(370, 240);	
	glEnd();

	/*-------- window_left --------*/
	glColor3f(0.2, 0.8, 1);
	glBegin(GL_POLYGON);
	glVertex2i(240, 240);
	glVertex2i(240, 320);
	glVertex2i(320, 320);
	glVertex2i(320, 240);
	glEnd();

	/*-------- window_right --------*/
	glColor3f(0.2, 0.8, 1);
	glBegin(GL_POLYGON);
	glVertex2i(480, 240);
	glVertex2i(480, 320);
	glVertex2i(560, 320);
	glVertex2i(560, 240);
	glEnd();


	glFlush();
}

int main(int argc, char *argv[]) {
	glutInit(&argc, argv);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 800);
	glutInitDisplayMode(GLUT_RGB);

	glutCreateWindow("Assignment 1");
	gluOrtho2D(0, 800, 0, 800);
	glClearColor(1,1,1,0.0);
	glutDisplayFunc(Draw);
	glutMainLoop();
	return 0;
}