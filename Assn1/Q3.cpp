#include <math.h>
#include <GL/glut.h>

void DrawCircle(float cx, float cy, float r, float num_segments) {
    glBegin(GL_LINE_LOOP);
    for (int ii = 0; ii < num_segments; ii++)   {
        float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle 
        float x = r * cosf(theta);//calculate the x component 
        float y = r * sinf(theta);//calculate the y component 
        glVertex2f(x + cx, y + cy);//output vertex 
    }
    glEnd();
}

void Draw() {
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(10);
    
    /*-------- bars --------*/
    glColor3f(0.1,0.1,0.8);
    glLineWidth(2);
    glBegin(GL_LINE_LOOP);
    glVertex2i(200, 300);
    glVertex2i(400, 600);
    glVertex2i(600, 600);
    glVertex2i(400, 300);
    glVertex2i(200, 300);
    glEnd();

    glBegin(GL_LINES);
    glVertex2i(400, 300);
    glVertex2i(400, 600);
    glEnd();

    glBegin(GL_LINES);
    glVertex2i(600, 600);
    glVertex2i(600, 300);
    glEnd();

    /*-------- seat --------*/
    glColor3f(0.5,0.2,0);
    glLineWidth(4);
    glBegin(GL_POLYGON);
    glVertex2i(380, 600);
    glVertex2i(450, 600);
    glVertex2i(450, 630);
    glVertex2i(380, 620);
    glEnd();

    /*-------- handle --------*/
    glBegin(GL_LINES);
    glColor3f(0.4,0.4,0.4);
    glLineWidth(4);
    glVertex2i(600, 700);
    glVertex2i(550, 650);
    glVertex2i(550, 650);
    glVertex2i(650, 550);
    glVertex2i(650, 550);
    glVertex2i(700, 600);
    glEnd();


    /*-------- tires --------*/
    glColor3f(0.2,0.2,0.2);
    glLineWidth(5);
    DrawCircle(200, 300, 120, 100);

    DrawCircle(600, 300, 120, 100);

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