#include <math.h>
#include <GL/glut.h>
#include <iostream>
#include <cassert>
#define debug(x,y) cout << #x << " " << x << " " << #y << " " << y << "\n";

using namespace std;

/*
 * Name: Krishanu Saini
 * Roll: 190001029
 * Ques: Problem 1) Bresenham circle 
 * Date: 2/02/22
 */ 

int xcord1,ycord1;
int r;

void BresenhamCircle(int x1, int y1, int r) {
    glColor3f(0,0,0);

    int p = 3 - 2*r;
    int xi = 0, yi = r;
    // innitialize parameters
    // if d > 0 then d = d + 4 * (x - y) + 10; and go down
    // else d < 0 then d = d + 4 * x + 6; and stay
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
        xi = xi+1;
        if(p > 0) {
            // go down
            p = p+4*(xi-yi)+10;
            yi=yi-1;
        } else if(p <= 0) {
            // stay
            p = p+4*xi+6;
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

    BresenhamCircle(xcord1,ycord1,r);
    
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

    glutCreateWindow("Bresenham Circle");
    gluOrtho2D(0, 800, 0, 800);
    glClearColor(1,1,1,0.0);
    glutDisplayFunc(Draw);
    glutMainLoop();
    return 0;
}