#include <math.h>
#include <GL/glut.h>
#include <iostream>
#include <cassert>
#define debug(x,y) cout << #x << " " << x << " " << #y << " " << y << "\n";

using namespace std;

/*
 * Name: Krishanu Saini
 * Roll: 190001029
 * Ques: Problem 2) DDA Method
 * Date: 17/01/22
 */ 

float xcord1,ycord1;
float xcord2,ycord2;

void DDA(float x1, float y1, float x2, float y2) {
    glColor3f(0,0,0);

    float xi = x1;
    float yi = y1;
    
    float delx = (x2 - x1);
    float dely = (y2 -y1);

    int totalSteps = 0;

    totalSteps = delx;
    if(abs(delx) < abs(dely)) {
        totalSteps = dely;
    }

    float dx = delx / totalSteps;
    float dy = dely / totalSteps;

    glBegin(GL_POINTS);
    glVertex2i((int)xi, (int)yi);

    for(int i=1;i<=totalSteps;i++) {
        xi = xi + dx;
        yi = yi + dy;
        glVertex2i((int)round(xi), (int)round(yi));
    }

    glEnd();
}

void Draw() {
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(1);

    DDA(xcord1,ycord1,xcord2,ycord2);
    
    glFlush();
}

int main(int argc, char *argv[]) {
    printf("enter point(1): ");
    cin >> xcord1 >> ycord1;
    printf("enter point(2): ");
    cin >> xcord2 >> ycord2;
    if(xcord1 > xcord2) swap(xcord1, xcord2), swap(ycord1, ycord2);
    glutInit(&argc, argv);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 800);
    glutInitDisplayMode(GLUT_RGB);

    glutCreateWindow("DDA Model");
    gluOrtho2D(0, 800, 0, 800);
    glClearColor(1,1,1,0.0);
    glutDisplayFunc(Draw);
    glutMainLoop();
    return 0;
}