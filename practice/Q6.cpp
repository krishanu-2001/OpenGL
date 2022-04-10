#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#include <bits/stdc++.h>
#include <unistd.h>
#include "imageio.h"
#endif

using namespace std;

void changeSize(int w, int h)
{

    // Prevent a divide by zero, when window is too short
    // (you cant make a window of zero width).
    if (h == 0)
        h = 1;

    float ratio = w * 1.0 / h;

    // Use the Projection Matrix
    glMatrixMode(GL_PROJECTION);

    // Reset Matrix
    glLoadIdentity();

    // Set the viewport to be the entire window
    glViewport(0, 0, w, h);

    // Set the correct perspective.
    gluPerspective(45.0f, ratio, 0.1f, 100.0f);

    // Get Back to the Modelview
    glMatrixMode(GL_MODELVIEW);
}

void Strokes(GLfloat x, GLfloat y, char *text)
{
    glPushMatrix();
    glTranslatef(x, y, 0);
    glScalef(1 / 200.0, 1 / 200.0, 1 / 200.0);
    for (char *p = text; *p; p++)
    {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, *p);
    }
    glPopMatrix();
}

GLuint texture[2];
void init_texture(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);

    // The following two lines enable semi transparent
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    int width, height;
    int width1, height1;
    bool hasAlpha;
    char filename[] = "car.png";
    char filename1[] = "car.png";
    // bool success = loadPngImage(filename, width, height, hasAlpha, &textureImage);
    unsigned char *ibuffer = loadImageRGBA(filename, &width, &height);
    std::cout << "Image loaded " << width << " " << height << " alpha " << hasAlpha << std::endl;
    std::cout << "Image loaded " << width1 << " " << height1 << " alpha " << hasAlpha << std::endl;
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glGenTextures(2, texture);
    cout << texture[0] << " " << texture[1] << endl;
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, 2, width,
                 height, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                 ibuffer);

    ibuffer = loadImageRGBA(filename1, &width, &height);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glBindTexture(GL_TEXTURE_2D, texture[1]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, 2, width,
                 height, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                 ibuffer);

    glEnable(GL_TEXTURE_2D);
    glShadeModel(GL_SMOOTH);
}

float anglex = 0.0f, angley = 0.0f;
float deltax = 0, deltay = 0, deltaz = 0;

void pressKey(int key, int xx, int yy)
{

    switch (key)
    {
    case GLUT_KEY_LEFT:
        deltay -= 0.1;
        break;
    case GLUT_KEY_RIGHT:
        deltay = 0.1;
        break;
    case GLUT_KEY_UP:
        deltax += 0.1;
        break;
    case GLUT_KEY_DOWN:
        deltax -= 0.1;
        break;
    }
}

void releaseKey(int key, int x, int y)
{

    switch (key)
    {
    case GLUT_KEY_LEFT:
    case GLUT_KEY_RIGHT:
        deltay = 0;
        break;
    case GLUT_KEY_UP:
    case GLUT_KEY_DOWN:
        deltax = 0;
        break;
    }
}

float xOrigin = -1;
float yOrigin = -1;

void mouseMove(int x, int y)
{

    // this will only be true when the left button is down
    if (xOrigin >= 0)
    {
        // update angleX
        deltay = (x - xOrigin) * 0.001f;
    }
    if (yOrigin >= 0)
    {
        // update angleX
        deltax = (y - yOrigin) * 0.001f;
    }
}

void mouseButton(int button, int state, int x, int y)
{

    // only start motion if the left button is pressed
    if (button == GLUT_LEFT_BUTTON)
    {

        // when the button is released
        if (state == GLUT_UP)
        {
            deltax = 0;
            deltay = 0;
            xOrigin = -1;
            yOrigin = -1;
        }
        else
        {
            // state = GLUT_DOWN
            xOrigin = x; // set xOrigin as the current x
            yOrigin = y;
        }
    }
}

void updateFunction()
{
    anglex += deltax;
    angley += deltay;
    glutPostRedisplay();
}

void Circle(float cx, float cy, float r, int num_segments)
{
    glBegin(GL_LINE_LOOP);
    for (int ii = 0; ii < num_segments; ii++)
    {
        float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments); // get the current angle
        float x = r * cosf(theta);                                         // calculate the x component
        float y = r * sinf(theta);                                         // calculate the y component
        glVertex2f(x + cx, y + cy);                                        // output vertex
    }
    glEnd();
}

void material()
{
    glEnable(GL_COLOR_MATERIAL);

    float m_ambient[4] = {0.3, 0.3, 0.3, 1.0};
    float m_diffuse[4] = {0.4, 0.4, 0.4, 1.0};
    float m_specular[4] = {0.6, 0.6, 0.6, 1.0};
    float m_shininess = 40;

    glMaterialfv(GL_FRONT, GL_AMBIENT, m_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, m_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, m_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, m_shininess);
}

void lighting()
{
    glLoadIdentity();
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    float light_position[4] = {0.3, 0.3, 0.3, 1.0};
    float light_ambient[4] = {0.3, 0.3, 0.3, 1.0};
    float light_diffuse[4] = {0.6, 0.6, 0.6, 1.0};
    float light_specular[4] = {0.6, 0.6, 0.6, 1.0};

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    material();
}

void renderScene(void)
{

    // Clear Color and Depth Buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(1, 1, 1, 1);

    // Reset transformations
    glLoadIdentity();

    // Set the camera
    gluLookAt(0.0f, 0.0f, 10.0f,
              0.0f, 0.0f, 0.0f,
              0.0f, 1.0f, 0.0f);

    // Ground
    glColor3f(0.7, 0.7, 0.7);
    glBegin(GL_POLYGON);
    glVertex3f(-5, -2, -5);
    glVertex3f(5, -2, -5);
    glVertex3f(5, -2, 5);
    glVertex3f(-5, -2, 5);
    glEnd();

    glPushMatrix();
    glRotatef(-angley, 0.0f, 1.0f, 0.0f);
    glRotatef(-anglex, 1.0f, 0.0f, 0.0f);

    glPushMatrix();
    glColor3f(0.5, 0.5, 1.0);
    // front
    glNormal3f(0.0, 0.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex3f(-1, -1, 1);
    glVertex3f(-1, 1, 1);
    glVertex3f(1, 1, 1);
    glVertex3f(1, -1, 1);
    glEnd();

    // back
    glNormal3f(0.0, 0.0, -1.0);
    glBegin(GL_POLYGON);
    glVertex3f(-1, 1, -1);
    glVertex3f(-1, -1, -1);
    glVertex3f(1, -1, -1);
    glVertex3f(1, 1, -1);
    glEnd();

    glColor3f(0.0, 1.0, 0.0);
    // left
    glNormal3f(-1.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-1, -1, 1);
    glVertex3f(-1, 1, 1);
    glVertex3f(-1, 1, -1);
    glVertex3f(-1, -1, -1);
    glEnd();

    // right
    glNormal3f(1.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(1, 1, 1);
    glVertex3f(1, -1, 1);
    glVertex3f(1, -1, -1);
    glVertex3f(1, 1, -1);
    glEnd();

    glColor3f(1.0, 0.0, 0.0);
    // top
    glNormal3f(0.0, 1.0, 0.0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-1, 1, -1);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(-1, 1, 1);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(1, 1, 1);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(1, 1, -1);
    glEnd();

    // down
    glNormal3f(0.0, -1.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-1, -1, -1);
    glVertex3f(-1, -1, 1);
    glVertex3f(1, -1, 1);
    glVertex3f(1, -1, -1);
    glEnd();
    glPopMatrix();

    // part 2 text strokes
    glPushMatrix();
    glTranslatef(0.0, 0.0, 1.05);
    char str[255] = "hello";
    Strokes(-0.5, 0.0, str);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0, 0.0, -1.05);
    glRotatef(180, 0.0, 1.0, 0.0);
    char str2[255] = "Krish";
    Strokes(-0.5, 0.0, str2);
    glPopMatrix();

    glPopMatrix();

    glutSwapBuffers();
}

int main(int argc, char **argv)
{

    // init GLUT and create window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Lighthouse3D- GLUT Tutorial");

    init_texture();
    lighting();
    // register callbacks
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);
    glutIdleFunc(updateFunction);

    // special functions
    glutSpecialFunc(pressKey);
    glutSpecialUpFunc(releaseKey);

    // here are the two new functions
    glutMouseFunc(mouseButton);
    glutMotionFunc(mouseMove);

    glEnable(GL_DEPTH_TEST);

    // enter GLUT event processing cycle
    glutMainLoop();

    return 1;
}