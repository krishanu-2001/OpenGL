#include <math.h>
#include <GL/glut.h>
#include <iostream>
#include <cassert>
#define debug(x,y) cout << #x << " " << x << " " << #y << " " << y << "\n";

using namespace std;

/*
 * Name: Krishanu Saini
 * Roll: 190001029
 * Ques: Problem 2) Mid Point circle 
 * Date: 2/02/22
 */ 

float xcord1,ycord1;
float r;

void MidCircle(float x1, float y1, float r) {
    glColor3f(0,0,0);

    int xi = 0, yi = r;
    int p = 1-r;

    glBegin(GL_POINTS);
    
    /*-------- draw all 8 octants --------*/
    glVertex2i(x1+xi, y1+yi);
    glVertex2i(x1-xi, y1+yi);
    glVertex2i(x1+xi, y1-yi);
    glVertex2i(x1-xi, y1-yi);
    glVertex2i(x1+yi, y1+xi);
    glVertex2i(x1-yi, y1+xi);
    glVertex2i(x1+yi, y1-xi);
    glVertex2i(x1-yi, y1-xi);

    while(xi <= yi) {
        xi++;
        // increment x normally
        if(p < 0) {
            // point lies inside circle - stay at level
            p = p + 2*xi + 1;
        } else {
            // go down
            yi--;
            p = p - 2*yi + 2*xi + 1;
        }
        /*-------- draw all 8 octants --------*/
        glVertex2i(x1+xi, y1+yi);
        glVertex2i(x1-xi, y1+yi);
        glVertex2i(x1+xi, y1-yi);
        glVertex2i(x1-xi, y1-yi);
        glVertex2i(x1+yi, y1+xi);
        glVertex2i(x1-yi, y1+xi);
        glVertex2i(x1+yi, y1-xi);
        glVertex2i(x1-yi, y1-xi);
    }

    glEnd();
}

void Draw() {
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(1);

    MidCircle(xcord1,ycord1,r);
    
    glFlush();
}

int main(int argc, char *argv[]) {
    printf("enter center: ");
    cin >> xcord1 >> ycord1;
    printf("enter radius: ");
    cin >> r;
    glutInit(&argc, argv);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 800);
    glutInitDisplayMode(GLUT_RGB);

    glutCreateWindow("Mid Point Circle");
    gluOrtho2D(0, 800, 0, 800);
    glClearColor(1,1,1,0.0);
    glutDisplayFunc(Draw);
    glutMainLoop();
    return 0;
}