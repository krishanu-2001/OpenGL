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

int xcord1,ycord1;
int xcord2,ycord2;

void MidPoint(int x1, int y1, int x2, int y2) {
    glColor3f(0,0,0);

    int xi = x1;
    int yi = y1;
    
    int delx = (x2 - x1);
    int dely = (y2 -y1);

    int totalSteps = 0;
    int d = 0;

    if(abs(delx) > abs(dely)) {
        totalSteps = delx;
        d = dely - delx / 2;
    } else {
        totalSteps = dely;
        d = delx - dely / 2;
    }

    glBegin(GL_POINTS);
    glVertex2i((int)xi, (int)yi);

    for(int i=1;i<=totalSteps;i++) {
        if(abs(delx) >= abs(dely)) {
            // m < 1, normal direction
            xi += 1;
            // East direction
            if (d < 0) {
                d = d + dely;
            } else { // North East direction
                d += dely - delx;
                yi++;
            }
        } else {
            yi += 1;
            // North direction
            if (d < 0) {
                d = d + delx;
            } else { // North East direction
                d += delx - dely;
                xi++;
            }
        }
        glVertex2i((int)round(xi), (int)round(yi));
    }

    glEnd();
}

void Draw() {
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(1);

    MidPoint(xcord1,ycord1,xcord2,ycord2);
    
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