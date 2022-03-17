#include <iostream>
#include <GL/glut.h>
using namespace std;
/*
 * Name: Krishanu Saini
 * Roll: 190001029
 * Ques: Problem 1b) Boundary Fill 8
 * Date: 10/02/22
 */ 

float colorFill[3] = {0, 0, 1}; // fill blue color
float boundFill[3] = {0, 0, 0}; // boundary is black

void DrawBoundary() {
    glLineWidth(10);
    glPointSize(4);
    glBegin(GL_LINE_LOOP);

    /*-------- Square --------*/
    glVertex2i(100, 100);
    glVertex2i(300, 100);
    glVertex2i(300, 300);
    glVertex2i(100, 300);

    /*-------- Triangle --------*/
    // glVertex2i(100, 100);
    // glVertex2i(300, 200);
    // glVertex2i(300, 600);

    glEnd();
}

void BoundaryFill(int x, int y, bool visited[1000][1000]) {
    if(x < 0 || x > 800 || y < 0 || y > 800) return; // out of bounds
    if(visited[x][y] == true) return;
    // else
    float pixel[3];
    glReadPixels(x,y,1.0,1.0,GL_RGB,GL_FLOAT,pixel);
    if(pixel[0] == boundFill[0] && pixel[1] == boundFill[1] &&  pixel[2] == boundFill[2]) {
        // boundary number
        return;
    }
    if(pixel[0] == colorFill[0] && pixel[1] == colorFill[1] &&  pixel[2] == colorFill[2]) {
        // filled color
        return;
    }
    // else
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    visited[x][y] = true;
    glEnd();
    glFlush();
    BoundaryFill(x-3, y-3, visited);
    BoundaryFill(x, y-3, visited);
    BoundaryFill(x+3, y-3, visited);
    BoundaryFill(x-3, y, visited);
    BoundaryFill(x+3, y, visited);
    BoundaryFill(x-3, y+3, visited);
    BoundaryFill(x, y+3, visited);
    BoundaryFill(x+3, y+3, visited);
}

void Draw() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    /*-------- boundary --------*/
    glPointSize(4);
    glColor3f(boundFill[0], boundFill[1], boundFill[2]);
    DrawBoundary();

    /*-------- b-fill --------*/
    bool visited[1000][1000];
    for(int i=0;i<1000;i++) {
        for(int j=0;j<1000;j++){
            visited[i][j] = false;
        }
    }
    glPointSize(4);
    glColor3f(colorFill[0], colorFill[1], colorFill[2]);
    BoundaryFill(200, 200, visited);


    glFlush();
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 800);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);

    glutCreateWindow("");
    gluOrtho2D(0, 800, 0, 800);
    glClearColor(1,1,1,0.0);
    glutDisplayFunc(Draw);
    glutMainLoop();
    return 0;
}