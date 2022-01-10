#include<GL/glut.h>
#include<GL/glu.h>
#include<stdio.h>

void Draw()
{
glClear(GL_COLOR_BUFFER_BIT);
glPointSize(10);
glColor3f(1,0,0);
glBegin(GL_TRIANGLES);
glVertex2f(0,0);
glVertex2f(1,1);
glVertex2f(1,0);
glEnd();

// second shape
glColor3f(0,1,0);
glBegin(GL_TRIANGLES);

glVertex2f(0,0);
glVertex2f(-1,0);
glVertex2f(-1,-1);
glEnd();
/*
//third shape
glColor3f(1,0,0);
glBegin(GL_TRIANGLES);

glVertex2f(0,0);
glVertex2f(-1,0);
glVertex2f(-1,-1);
glEnd();
*/

glFlush();
}


int main(int C, char *V[])
{
glutInit(&C,V);
glutInitWindowPosition(300,300);
glutInitWindowSize(800,800);
glutInitDisplayMode(GLUT_RGB  | GLUT_SINGLE);
glutCreateWindow("Sample1");
glClearColor(1,1,1,0);
glutDisplayFunc(Draw);
glutMainLoop();
return 0;
}
