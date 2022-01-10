#include<GL/glut.h>
#include<GL/gl.h>

void Draw() {
	glClear(GL_COLOR_BUFFER_BIT); // set as background
	glColor3f(1,0,0); // color of objects
	glPointSize(10);
	glBegin(GL_POLYGON);
	// GL_POLYGON
	// GL_LINE_LOOP
	// GL_POINTS

	glVertex2f(0.5, 0.5); // 2-dimentioPn, f-float, d-decimal
	glVertex2f(-0.5, 0.5);
	glVertex2f(0.5, -0.5);
	glVertex2f(-0.5, -0.5);

	glEnd();
	glFlush(); // flush buffer
}

int main(int argc, char *argv[]) {
	glutInit(&argc, argv);
	glutInitWindowPosition(300, 300);
	glutInitWindowSize(600, 600);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE); // GLUT_SINGLE - 2d image
	
	// gl library for color
	glClearColor(0,0,0,1); // set background color (rgba)

	glutCreateWindow("First Program");
	glutDisplayFunc(Draw);
	glutMainLoop(); // keep window from closing like python
	return 0;
}
