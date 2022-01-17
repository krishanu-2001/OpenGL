#include <GL/glut.h>

/*
 * Name: Krishanu Saini
 * Roll: 190001029
 * Ques: Problem 1) Tree
 * Date: 13/01/22
 */ 

void Draw() {
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(10);
	
	/*-------- corners --------*/
	glColor3f(0,0,0);
	glBegin(GL_POINTS);
	glVertex2i(0,0);
	glVertex2i(0,800);
	glVertex2i(800,800);
	glVertex2i(800,0);
	glEnd();

	/*-------- Leaves --------*/
	glColor3f(0.1,0.8,0.1);
	glBegin(GL_POLYGON);
	glVertex2i(400, 450);
	glVertex2i(220, 250);
	glVertex2i(580, 250);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2i(400, 550);
	glVertex2i(240, 350);
	glVertex2i(560, 350);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2i(400, 650);
	glVertex2i(260, 450);
	glVertex2i(540, 450);
	glEnd();

	/*-------- wood --------*/
	glColor3f(0.6,0.3,0);
	glBegin(GL_POLYGON);
	glVertex2i(350, 100);
	glVertex2i(350, 250);
	glVertex2i(450, 250);
	glVertex2i(450, 100);
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