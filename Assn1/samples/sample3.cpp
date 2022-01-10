#include <GL/glut.h>

void displayCB(void)	
{
  glClear(GL_COLOR_BUFFER_BIT);	
  glColor3f(1.0,0,0);		
  glBegin(GL_POLYGON);		
  glVertex2i(0,0);			
  glVertex2i(100,375);
  glVertex2i(300,375);
  glEnd();				
  glFlush();		
}
int main(int argc, char *argv[])
{
  int win;
  glutInit(&argc, argv);	
  glutInitDisplayMode(GLUT_RGB);
  glutInitWindowSize(800,800);	
  win = glutCreateWindow("Sample2");	
  glClearColor(1,1,1,0.0);	
  gluOrtho2D(0,800,0,800);		
  glutDisplayFunc(displayCB);		
  glutMainLoop();			
  return 0;
}
