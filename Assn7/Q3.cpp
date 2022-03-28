#include <bits/stdc++.h>
#include <GL/glut.h>
#include "imageio.h"

using namespace std;


double rotate_x = 0, rotate_y = 0, zoom = 1;

int width, height;

int texImageWidth;
int texImageHeight;

GLubyte *makeTexImage(char *file)
{
	int width, height;
	GLubyte *texImage;
	texImage = loadImageRGBA((char *)file, &width, &height);
	texImageWidth = width;
	texImageHeight = height;
	return texImage;
}

void Display_Stroke(GLfloat x, GLfloat y, GLfloat z, GLfloat s, GLfloat pointSize, GLfloat rotate, string text)
{
	string buffer = text;
	glPushMatrix();
	glTranslatef(x, y, z);
	glPointSize(pointSize);
	glLineWidth(pointSize);
	glRotatef(rotate, 0.0, 1.0, 0.0);
	glScalef(s, s, s);
	for (auto ch : buffer)
		glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, ch);
	glPopMatrix();
}

// Positions of lights
GLfloat front_left_light_position[] = {-1.0, 0.0, 1.0, 0.0};
GLfloat front_right_light_position[] = {1.0, 0.0, 1.0, 0.0};
GLfloat back_left_light_position[] = {-1.0, 0.0, -1.0, 0.0};
GLfloat back_right_light_position[] = {1.0, 0.0, -1.0, 0.0};

// Material properties
GLfloat yellow_ambient[] = {0.35, 0.26, 0.05, 1.0},
		yellow_diffuse[] = {0.80, 0.60, 0.15, 1.0},
		yellow_specular[] = {0.99, 0.94, 0.85, 1.0},
		yellow_shininess = 28.8;


float diffuse_intensity = 0.5;
int select_Menu = 0;

void material()
{
	
	glMaterialfv(GL_FRONT, GL_AMBIENT, yellow_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, yellow_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, yellow_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, yellow_shininess);

}

void display(void)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	material(); 

	GLfloat light_diffuse[] = {diffuse_intensity, diffuse_intensity, diffuse_intensity, 1.0}; // Diffuse light intersity

	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, light_diffuse);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	glEnable(GL_LIGHT3);

	glLoadIdentity();

	glRotatef(rotate_y, 0.0, 1.0, 0.0);
	glRotatef(rotate_x, 1.0, 0.0, 0.0);
	glScalef(zoom, zoom, zoom);

	// Printing at front face
	Display_Stroke(-0.35, 0.25, -0.5, 0.0009, 4, 0, "created");
	Display_Stroke(-0.1, 0.0, -0.5, 0.0009, 4, 0, "by");
	Display_Stroke(-0.45, -0.25, -0.5, 0.0012, 7.5, 0, "Kuldeep");

	// Printing at back face
	Display_Stroke(0.35, 0.25, 0.5, 0.0009, 4, 180, "created");
	Display_Stroke(0.1, 0.0, 0.5, 0.0009, 4, 180, "by");
	Display_Stroke(0.45, -0.25, 0.5, 0.0012, 7.5, 180, "Kuldeep");

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

	glBegin(GL_QUADS);
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(0.5, 0.5, -0.5);
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(-0.5, -0.5, -0.5);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(-0.5, 0.5, 0.5);
	glVertex3f(-0.5, -0.5, 0.5);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(0.5, -0.5, -0.5);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(0.5, 0.5, -0.5);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.5, 0.5, 0.5);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(0.5, -0.5, 0.5);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-0.5, -0.5, 0.5);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(-0.5, 0.5, 0.5);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(-0.5, 0.5, -0.5);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-0.5, -0.5, -0.5);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(0.5, 0.5, 0.5);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(0.5, 0.5, -0.5);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(-0.5, 0.5, -0.5);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-0.5, 0.5, 0.5);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(0.5, -0.5, -0.5);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(0.5, -0.5, 0.5);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(-0.5, -0.5, 0.5);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-0.5, -0.5, -0.5);
	glEnd();

	glPopMatrix();

	glFlush();
	glutSwapBuffers();
}

int axis_x = 0, axis_y = 0;

void SpecialKeys(unsigned char key, int x, int y)
{
	if (key == 'r' or key == 'R')// Reset
	{ 
		rotate_x = 0;
		rotate_y = 0;
	}
	if (key == 'z')// change intensity
	{ 
		diffuse_intensity += 0.01;
	}
	if (key == 'x')
	{
		diffuse_intensity -= 0.01;
	}
	if (key == 'a' or key == 'A')// Zoom in/out
	{ 
		zoom *= 1.021897148;
	}
	if (key == 's' or key == 'S')
	{
		zoom /= 1.021897148;
	}
	diffuse_intensity = min(diffuse_intensity, (float)1.0);
	diffuse_intensity = max(diffuse_intensity, (float)0.0);
	glutPostRedisplay();
}


// Rotate the cube 
void keyboardRotate(int key, int x, int y)
{
	if (key == GLUT_KEY_LEFT)
	{
		rotate_y += 5;
		axis_y = 0;
	}
	if (key == GLUT_KEY_RIGHT)
	{
		rotate_y -= 5;
		axis_y = 1;
	}
	if (key == GLUT_KEY_DOWN)
	{
		rotate_x -= 5;
		axis_x = 1;
	}
	if (key == GLUT_KEY_UP)
	{
		rotate_x += 5;
		axis_x = 0;
	}
	glutPostRedisplay();
}

int last_x = 0, last_y = 0;

// Rotate the cube 
void mouseRotate(int x, int y)
{
	if (x > 600 or y > 600 or x < 0 or y < 0)
		return;
	if (abs(x - last_x) > 25 or abs(y - last_y) > 25)
	{
		last_x = x;
		last_y = y;
		return;
	}
	rotate_x += (last_y - y + 0.0) * 0.5;
	rotate_y += (last_x - x + 0.0) * 0.5;
	if ((last_y - y) > 0)
		axis_x = 0;
	if ((last_y - y) < 0)
		axis_x = 1;
	if ((last_x - x) > 0)
		axis_y = 0;
	if ((last_x - x) < 0)
		axis_y = 1;
	last_x = x;
	last_y = y;

	glutPostRedisplay();
}

void mouseZoom(int btn, int state, int x, int y)
{
	if (state == GLUT_DOWN)
	{
		if (btn == 3)
		{
			zoom *= 1.021897148;
		}
		if (btn == 4)
		{
			zoom /= 1.021897148;
		}
	}
	glutPostRedisplay();
}

void load_texture()
{
	unsigned int texture;
	glGenTextures(1, &texture);
	GLubyte *texImage = makeTexImage((char *)"logo.png");
	if (!texImage)
	{
		printf("\nError in reading image \n");
		return;
	}
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texImageWidth, texImageWidth, 0, GL_RGBA, GL_UNSIGNED_BYTE, texImage);
	delete texImage;
}


void myInit()
{

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);

	glLightfv(GL_LIGHT0, GL_POSITION, front_left_light_position);
	glLightfv(GL_LIGHT1, GL_POSITION, front_right_light_position);
	glLightfv(GL_LIGHT1, GL_POSITION, back_left_light_position);
	glLightfv(GL_LIGHT1, GL_POSITION, back_right_light_position);

	glEnable(GL_LIGHTING);

}

int main(int argc, char **argv)
{
	 printf("Arrows/Mouse to move cube, z/x for intensity, a/s for zoom.\n");

	glutInit(&argc, argv);
	glutInitWindowPosition(700, 0); // set window position
	glutInitWindowSize(600, 600);	// set window size
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("3D - CUBE"); // set window title

	load_texture();

	myInit();
	glutDisplayFunc(display);

	glutKeyboardFunc(SpecialKeys);
	glutSpecialFunc(keyboardRotate);

	glutMouseFunc(mouseZoom);
	glutMotionFunc(mouseRotate);

	glutMainLoop();
	return 0;
}