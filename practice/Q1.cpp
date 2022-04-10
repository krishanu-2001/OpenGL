// glut house + flag + road + sun

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <bits/stdc++.h>
#include <unistd.h>
using namespace std;

float theta = 1;

/*
    Special Functions
  1. glutReshapeFunc() -> maintain aspect ratio while resizing window
  2. glutIdleFunc() -> For calling function on regular intervals (animation)
*/

void changeSize(int, int);

void init()
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void Circle()
{
    float x = 50, y = 50, r = 40;

    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 100; i++)
    {
        float theta = 2 * 3.14159 * i / 100;
        float a = x + r * cosf(theta);
        float b = y + r * sinf(theta);
        glVertex2f(a, b);
    }
    glEnd();
}

void loop()
{
    usleep(1000);
    theta += 1;
    glutPostRedisplay();
}

void Draw()
{
    init();
    // Set the background color
    glPointSize(10);

    /*-------- corners --------*/
    glColor3f(0, 0, 0);
    glBegin(GL_POINTS);
    glVertex2i(0, 0);
    glVertex2i(800, 0);
    glVertex2i(10, 800);
    glVertex2i(800, 0);
    glEnd();

    Circle();

    glPushMatrix();
    glTranslatef(50, 50, 0);
    glRotatef(0 + theta, 0, 0, 1.0);
    glColor3f(1, 0.5, 0.3);
    glPointSize(10);
    glBegin(GL_POINTS);
    glVertex2f(0, 40);
    glEnd();
    glPopMatrix();

    glColor3f(0, 0, 0);
    glBegin(GL_POINTS);
    glVertex2f(90, 50);
    glEnd();

    glutSwapBuffers();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 800);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutCreateWindow("flag");
    // init
    glClearColor(1, 1, 1, 0.0);
	gluOrtho2D(0, 800, 0, 800);

    glutDisplayFunc(Draw);

    // special functions
    glutIdleFunc(loop);
    glutReshapeFunc(changeSize);

    glutMainLoop();

    return 0;
}
void changeSize(int w, int h)
{

    // Prevent a divide by zero, when window is too short
    // (you cant make a window of zero width).
    if (h == 0)
        h = 1;

    float ratio = w * 1.0 / h;

    cout << w << " " << h << endl;
    // Use the Projection Matrix
    glMatrixMode(GL_PROJECTION);

    // Reset Matrix
    glLoadIdentity();

    // Set the viewport to be the entire window
    glViewport(0, 0, w, h);

    // Set the correct perspective.
    gluPerspective(45.0f, ratio, 0, 0);

    // Get Back to the Modelview
    glMatrixMode(GL_MODELVIEW);
}
