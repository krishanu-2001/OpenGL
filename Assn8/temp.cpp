#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#if defined __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

#define BLACK 0, 0, 0

//make a global variable -- for tracking the anglular position of camera
double cameraAngle;			//in radian
double cameraAngleDelta;

double cameraHeight;	
double cameraRadius;

double rectAngle;	//in degree

bool canDrawGrid;
GLUquadric *quad;


void swap(int &a,int &b)
{
	int t=a;
	a=b;
	b=t;
}





void chair(double x,double y,int r1,int r2,int r3,int r4)
{

	double equ[4];

	//z=1 er niche shob bad
	equ[0] = 0;	//0.x
	equ[1] = 0;	//0.y
	equ[2] = 1;//1.z
	equ[3] = -16;//0
	
	
	
	glClipPlane(GL_CLIP_PLANE0,equ);

	//now we enable the clip plane

	glEnable(GL_CLIP_PLANE0);
	{	
		glColor3f(1, 0, 0);
		glPushMatrix();
		{
			glTranslatef(x,y,10);
			glutSolidCube(20);
		}glPopMatrix();
		
	}glDisable(GL_CLIP_PLANE0);



	int j,i;
	int dx[4]={1,1,-1,-1};
	int dy[4]={-1,1,-1,1};
	int rise[4]={r1,r2,r3,r4};
	
	


	for(i=0;i<4;i++)
	{
		for(j=14;j>=2;j-=4)
		{
			glColor3f(0, 1, 1);
			glPushMatrix();
			{
				glTranslatef(x+7*dx[i],y+7*dy[i],j);
				glutSolidCube(4);
			}glPopMatrix();
		}

		
		if(rise[i])
		for(j=38;j>=14;j-=4)
		{
			glColor3f(0, 1, 1);
			glPushMatrix();
			{
				glTranslatef(x+7*dx[i],y+7*dy[i],j);
				glutSolidCube(4);
			}glPopMatrix();
			
		}
	}	
	
	
	int x1,x2;
	int y1,y2;
	for(i=0;i<4;i++)
	for(j=i+1;j<4;j++)
	{
		if(rise[i]  && rise[j])
		{
			x1=x+7*dx[i];
			x2=x+7*dx[j];
			

			y1=y+7*dy[i];
			y2=y+7*dy[j];

			goto last;
		}
	}
	last:
	
	if(x1>x2) swap(x1,x2);
	if(y1>y2) swap(y1,y2);
	
	
	
	for(j=38;j>=15;j-=7)
	{
		for(x=x1;x<=x2;x+=3)
		for(y=y1;y<=y2;y+=3)
		{
			glColor3f(1, 0, 1);
			glPushMatrix();
			{
				glTranslatef(x,y,j);
				glutSolidCube(3);
			}glPopMatrix();
		}
	}
	



}


void shelf()
{
	
	int i,j;
	double equ[4];

	//z=1 er niche shob bad
	equ[0] = 0;	//0.x
	equ[1] = 0;	//0.y
	equ[2] = 1;//1.z
	
		

	//base
	for(i=-40;i<=40;i+=20)
	{
		glColor3f(1, 0, 0);
		glPushMatrix();
		{
			glTranslatef(90,i,10);
			glutSolidCube(20);
		}glPopMatrix();
	
		
		for(j=30;j<=70;j+=20)
		{
			equ[3]=-j-7;

			glClipPlane(GL_CLIP_PLANE0,equ);

			//now we enable the clip plane

			glEnable(GL_CLIP_PLANE0);
			{
				glColor3f(0,0.3,0.8);	//blue
				glPushMatrix();
				{
					glTranslatef(90,i,j);
					glutSolidCube(20);
				}
				glPopMatrix();
			}
			glDisable(GL_CLIP_PLANE0);
		}
	}
		


	
	equ[0] = 1;
	equ[1] = 0;
	equ[2] = 0;
	equ[3]=-100;
	
	glClipPlane(GL_CLIP_PLANE0,equ);
	glEnable(GL_CLIP_PLANE0);
	{
		glColor3f(0,0.7,0.8);	//blue
		glPushMatrix();
		{
			glTranslatef(52,0,50);
			glutSolidCube(100);
		}
		glPopMatrix();
	}
	glDisable(GL_CLIP_PLANE0);

	

	for(i=20;i<=80;i+=3)
	{
		glColor3f(0,0.7,0.8);	//blue
		glPushMatrix();
		{
			glTranslatef(82,-48,i);
			glutSolidCube(3);
		}
		glPopMatrix();

		glPushMatrix();
		{
			glTranslatef(82,48,i);
			glutSolidCube(3);
		}
		glPopMatrix();
	}

}




void table()
{
	/*
	//scaling
	glPushMatrix();
	{
		glScaled(3,4,1);
		glTranslatef(0,0,30);
		glutSolidSphere(10, 20, 20);
		
	}
	glPopMatrix();*/
	
		
	//top outer circle
	glColor3f(0,0,0);
	glPushMatrix ();
	{
		glScaled(1.25,1.65,1);
		glTranslatef (0, 0, 30);
		gluDisk (quad, 28, 30, 18, 1);
    }
	glPopMatrix ();
	
	//top inner circle
	glColor3f(1,.5,0);
	glPushMatrix ();
	{
		glScaled(1.25,1.65,1);
		glTranslatef (0, 0, 30);
		gluDisk (quad, 0, 28, 18, 1);
    }
	glPopMatrix ();



	
	//4 sticks of table
	glColor3f(.2,.5,.9);
	int i;
	int dx[4]={20,20,-20,-20};
	int dy[4]={-20,20,-20,20};
	for(i=0;i<4;i++)
	{
		glPushMatrix ();
		{
			glTranslatef (dx[i],dy[i], 0);
			gluCylinder (quad, 4,4, 30, 18, 1);
		}
		glPopMatrix ();
	}	

	//sticks joining sticks of table
	glColor3f(.3,.3,.3);
	for(i=-20;i<=20;i+=4)
	{
		glPushMatrix ();
		{
			glTranslatef (i,20, 20);
			glutSolidCube(4);
		}
		glPopMatrix ();
		
		glPushMatrix ();
		{
			glTranslatef (0,i, 20);
			glutSolidCube(4);
		}
		glPopMatrix ();
		

		glPushMatrix ();
		{
			glTranslatef (i,-20, 20);
			glutSolidCube(4);
		}
		glPopMatrix ();
	}
	
	


}




void chandelier()
{


	glColor3f(1,.5,.2);
	glPushMatrix ();
	{
		glTranslatef (0, 0, 85);
		glScaled(1,1,200);
		gluDisk (quad, 0, 20, 18, 1);
    }
	glPopMatrix ();
	
	
	
	glColor3f(1,.5,.2);
	glPushMatrix ();
	{
		glTranslatef (0, 0, 110);
		glScaled(1,1,200);
		gluDisk (quad, 0, 30, 18, 1);
    }
	glPopMatrix ();
	




	glColor3f(.3,.5,.6);
	glPushMatrix ();
	{
		glTranslatef (0, 0, 110);
		gluCylinder (quad, 1,2, 30, 18, 1);
    }
	glPopMatrix ();

	
	
	glColor3f(.2,.5,.9);
	int i,j;
	
	int dx[4]={2,2,-2,-2};
	int dy[4]={-2,2,-2,2};

	int dx1[8]={0,0,10,10,-10,-10,18,-18};
	int dy1[8]={18,-18,-13,13,13,-13,0,0};
	
	for(i=0;i<4;i++)
	{
		glPushMatrix ();
		{
			glTranslatef(dx[i],dy[i], 85);
			gluCylinder(quad, 2,2, 30, 18, 1);
		}
		glPopMatrix ();
	}
	

	int c[3];
	for(i=0;i<8;i++)
	{
		glColor3f(1,1,1);
		glPushMatrix ();
		{
			glTranslatef(dx1[i],dy1[i], 85);
			gluCylinder(quad, 2,2, 25, 18, 1);
		}
		glPopMatrix ();

		
		glColor3f(.7,.6,.9);
		glPushMatrix ();
		{
			glTranslatef(dx1[i],dy1[i], 110);
			gluCylinder(quad, 2,2, 5, 18, 1);
		}
		glPopMatrix ();



		glColor3f(1,0,0);
		glPushMatrix ();
		{
			glTranslatef(dx1[i],dy1[i], 117);
			glutSolidSphere(2,2,2);
		}
		glPopMatrix ();

		
		c[0]=c[1]=c[2]=0;
		for(j=111;j>=70;j-=4)
		{
			c[(j+1)%3]=1;
			glColor3f(c[0],c[1],c[2]);
			glPushMatrix ();
			{
				glTranslatef(1.6*dx1[i],1.6*dy1[i], j);
				glutSolidSphere(1,4,4);
			}
			glPopMatrix ();
			c[(j+1)%3]=0;
		}
		
	}
	
}





void window()
{
	int i,j,z,j1;
	int x[4]={-100,-100,-120,-120};
	int y[4]={30,-30,50,-50};
	
	
	glColor3f(.6,.6,.1);		
	for(i=0;i<4;i++)
	{
		glPushMatrix ();
		{
			glTranslatef(x[i],y[i], 50);
			gluCylinder(quad, 2,2, 50, 18, 1);
		}
		glPopMatrix ();
	}


	for(i=-30;i<=30;i+=4)
	{
		glPushMatrix ();
		{
			glTranslatef(-100,i, 50);
			glutSolidCube(4);
		}
		glPopMatrix ();

		glPushMatrix ();
		{
			glTranslatef(-100,i, 100);
			glutSolidCube(4);
		}
		glPopMatrix ();
	}
	

	glColor3f(1,1,1);
	
	

	for(i=-100,j=30,j1=-30;i>=-120;i-=4,j+=4,j1-=4)
	{
		for(z=50;z<=100;z+=25)
		{
			glPushMatrix ();
			{
				glTranslatef(i,j,z);
				glutSolidCube(4);
			}
			glPopMatrix ();
		}
		for(z=50;z<=100;z+=25)
		{
			glPushMatrix ();
			{
				glTranslatef(i,j1,z);
				glutSolidCube(4);
			}
			glPopMatrix ();
		}
	}
	

	

	//window knobs
	z=75;
	i+=4,j-=5,j1+=5;
	glColor3f(0,0,0);
	glPushMatrix ();
	{
		glTranslatef(i,j,z);
		glutSolidSphere(2,5,5);
	}
	glPopMatrix ();

	glPushMatrix ();
	{
		glTranslatef(i,j1,z);
		glutSolidSphere(2,5,5);
	}
	glPopMatrix ();
	




}


bool st;
double H;
double segs=30;
double min(double a,double b)
{
	if(a<b) return a;
	else return b;
	
}
double max(double a,double b)
{
	if(a>b) return a;
	else return b;
}


void screen()
{
	int i,j;
	


	
	glColor3f(1,1,1);
	for(i=-30;i<=30;i+=4)
	{
		glPushMatrix ();
		{
			glTranslatef(-95,i, 100);
			glutSolidCube(4);
		}
		glPopMatrix ();

	}

	if(st==0) H=min(1.02*H,60);
	else H=max(10,0.98*H);
	

	double h=H/segs;
	

	


	//screen movement
	double now=-30,now1;
	double cl=1;
	double x[4],y[4],z[4];

	z[0]=100;
	z[1]=100;
	z[2]=50;
	z[3]=50;

	for(i=1;i<segs;i++)
	{
		now1=now+h;
		
		if(i%2)
		{
			x[0]=-90;
			y[0]=now;

			x[1]=-100;
			y[1]=now1;

			x[2]=-100;
			y[2]=now1;
		
			x[3]=-90;
			y[3]=now;
	
		}
		else
		{
			x[0]=-100;
			y[0]=now;
	
			x[1]=-90;
			y[1]=now1;
	
			x[2]=-90;
			y[2]=now1;
	
			x[3]=-100;
			y[3]=now;
		}

		
		glColor3f(0, 0, cl);
		glPushMatrix();
		{	//STORE the state
			glBegin(GL_QUADS);
			{
				for(j=0;j<4;j++)
				glVertex3f(x[j],y[j],z[j]);
			}
			glEnd();
		}
		glPopMatrix();
		

		now=now1;		
		cl*=.95;
	}
}









void plate(double X,double Y,double Z,double r1,double r2,double h)
{	
	glColor3f(0,.2,.2);
	glPushMatrix ();
	{
		glTranslatef (X, Y, Z);
		gluCylinder (quad, r1,r1+(r2-r1)/2, h/2, 13, 13);
    }
	glPopMatrix ();
	
	glColor3f(0,0,1);
	glPushMatrix ();
	{
		glTranslatef (X, Y, Z+h/2);
		gluCylinder (quad, r1+(r2-r1)/2,r2+(r2-r1)/2, h/2, 13, 13);
    }
	glPopMatrix ();


	glColor3f(1,1,1);
	glPushMatrix ();
	{
		glScaled(1,1,1);
		glTranslatef (X, Y, Z+.2);
		gluDisk (quad, 0, r1, 18, 1);
    }
	glPopMatrix ();


}



void glass(double X,double Y,double Z,double r1,double r2,double h)
{
	plate(X,Y,Z,r1,r2,h);
	
	glColor3f(1,1,1);
	glPushMatrix ();
	{
		glTranslatef (X, Y, Z+h);
		gluCylinder (quad, r1,r2, 2, 13, 13);
    }
	glPopMatrix ();

}



void bottle(double X,double Y,double Z)
{
	glColor3f(.4,1,.2);
	glPushMatrix ();
	{
		glTranslatef (X, Y, Z);
		gluCylinder (quad, 2,3, 2, 13, 13);
    }
	glPopMatrix ();
	Z+=2;

	
	glColor3f(1,1,.6);
	glPushMatrix ();
	{
		glTranslatef (X, Y, Z);
		gluCylinder (quad, 3,3,4, 13, 13);
    }
	glPopMatrix ();
	Z+=4;
	
	

	glColor3f(.4,.9,.9);
	glPushMatrix ();
	{
		glTranslatef (X, Y, Z);
		gluCylinder (quad, 3,1.2,3, 13, 13);
    }
	glPopMatrix ();
	Z+=3;

	
	glColor3f(.4,1,1);
	glPushMatrix ();
	{
		glTranslatef (X, Y, Z);
		gluCylinder (quad, 1.2,1.2,3, 13, 13);
    }
	glPopMatrix ();
	Z+=3;

	
	glColor3f(0,0,0);
	glPushMatrix ();
	{
		glTranslatef (X, Y, Z);
		gluCylinder (quad, 1.2,1.2,2, 13, 13);
    }
	glPopMatrix ();
}







void display(){

	//clear the display
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(BLACK, 0);	//color black
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/********************
	/ set-up camera here
	********************/
	//load the correct matrix -- MODEL-VIEW matrix
	glMatrixMode(GL_MODELVIEW);

	//initialize the matrix
	glLoadIdentity();

	//now give three info
	//1. where is the camera (viewer)?
	//2. where is the camera is looking?
	//3. Which direction is the camera's UP direction?

	//instead of CONSTANT information, we will define a circular path.
//	gluLookAt(-30,-30,50,	0,0,0,	0,0,1);

	gluLookAt(cameraRadius*cos(cameraAngle), cameraRadius*sin(cameraAngle), cameraHeight,		0,0,0,		0,0,1);
	//NOTE: the camera still CONSTANTLY looks at the center
	// cameraAngle is in RADIAN, since you are using inside COS and SIN
	
	
	//again select MODEL-VIEW
	glMatrixMode(GL_MODELVIEW);





	/****************************
	/ Add your objects from here
	****************************/



	//floor
	glPushMatrix();
	{	//STORE the state
		//a simple rectangles
	
		///lets draw another one in the XY plane --- i.e. Z = 0


		glColor3f(1,1,1);
		glBegin(GL_QUADS);
		{
			glVertex3f(-100,-100,0);
			glVertex3f(-100,100,0);
			glVertex3f(100,100,0);
			glVertex3f(100,-100,0);
		}glEnd();
	}glPopMatrix();		//the effect of rotation is not there now.
	
	
	


	//some gridlines along the field
	int i;

	//WILL draw grid IF the "canDrawGrid" is true:
	glColor3f(0.3, 0.3, 0.3);
	if(canDrawGrid == true)
	{
		glBegin(GL_LINES);
		{
			for(i=-10;i<=10;i++)
			{

				if(i==0)
					continue;	//SKIP the MAIN axes
				
				//lines parallel to Y-axis
				glVertex3f(i*10, -100, 0);
				glVertex3f(i*10,  100, 0);

				//lines parallel to X-axis
				glVertex3f(-100, i*10, 0);
				glVertex3f( 100, i*10, 0);
			}
		}glEnd();
	}
	


	
	// draw the two AXES
	glColor3f(1, 1, 1);	//100% white
	glBegin(GL_LINES);{
		//Y axis
		glVertex3f(0, -150, 0);	// intentionally extended to -150 to 150, no big deal
		glVertex3f(0,  150, 0);

		//X axis
		glVertex3f(-150, 0, 0);
		glVertex3f( 150, 0, 0);
	}glEnd();

	

	
	
	chair(0,60,0,1,0,1);
	chair(0,-60,1,0,1,0);
	
	chair(-45,30,0,0,1,1);
	chair(-45,-30,0,0,1,1);
	
	chair(45,30,1,1,0,0);
	chair(45,-30,1,1,0,0);
	
	

	shelf();
	
	table();
	
	chandelier();
		

	window();
	
	screen();

		
	
	
	//x y z r1 r2 h
	plate(20,20,30,5,10,4);
	plate(-20,20,30,5,10,4);
	plate(-20,-20,30,5,10,4);
	plate(20,-20,30,5,10,4);

	glass(0,0,30,3,3,8);
	glass(6,1,30,3,3,8);

		
	
	bottle(0,40,30);


	

	//////// ------ NOTE ---- ORDER matters. compare last two spheres!

	//ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
	glutSwapBuffers();
}



void animate(){
	//codes for any changes in Camera

	cameraAngle += cameraAngleDelta;	// camera will rotate at 0.002 radians per frame.	// keep the camera steady NOW!!
	
	//codes for any changes in Models
	
	rectAngle -= 1;

	//MISSING SOMETHING? -- YES: add the following
	glutPostRedisplay();	//this will call the display AGAIN
}

void keyboardListener(unsigned char key, int x,int y){
	switch(key){

		case '1':	//reverse the rotation of camera
			cameraAngleDelta = -cameraAngleDelta;
			break;

		case '2':	//increase rotation of camera by 10%
			cameraAngleDelta *= 1.1;
			break;

		case '3':	//decrease rotation
			cameraAngleDelta /= 1.1;
			break;

		case '8':	//toggle grids
			canDrawGrid =  !canDrawGrid;
			break;
		
		case 'a':	//toggle grids
			st=!st;
			break;

		case 27:	//ESCAPE KEY -- simply exit
			exit(0);
			break;

		default:
			break;
	}
}



void specialKeyListener(int key, int x,int y){
	switch(key){
		case GLUT_KEY_DOWN:		//down arrow key
			cameraRadius += 10;
			break;
		case GLUT_KEY_UP:		// up arrow key
			if(cameraRadius > 10)
				cameraRadius -= 10;
			break;

		case GLUT_KEY_RIGHT:
			break;
		case GLUT_KEY_LEFT:
			break;

		case GLUT_KEY_PAGE_UP:
			cameraHeight += 10;
			break;
		case GLUT_KEY_PAGE_DOWN:
			cameraHeight -= 10;
			break;

		case GLUT_KEY_INSERT:
			break;

		case GLUT_KEY_HOME:
			break;
		case GLUT_KEY_END:
			break;

		default:
			break;
	}
}

void mouseListener(int button, int state, int x, int y){	//x, y is the x-y of the screen (2D)
	switch(button){
		case GLUT_LEFT_BUTTON:
			if(state == GLUT_DOWN){		// 2 times?? in ONE click? -- solution is checking DOWN or UP
				
				cameraAngleDelta = -cameraAngleDelta;	
			}
			break;

		case GLUT_RIGHT_BUTTON:
			//........
			break;

		case GLUT_MIDDLE_BUTTON:
			//........
			break;

		default:
			break;
	}
}


void init(){
	//codes for initialization
	cameraAngle = 0;	//// init the cameraAngle
	cameraAngleDelta = 0.002;
	rectAngle = 0;
	canDrawGrid = true;
	cameraHeight = 150;
	cameraRadius = 150;

	//clear the screen
	glClearColor(BLACK, 0);
	

	quad= gluNewQuadric ();
	

	/************************
	/ set-up projection here
	************************/
	//load the PROJECTION matrix
	glMatrixMode(GL_PROJECTION);
	
	//initialize the matrix
	glLoadIdentity();

	//give PERSPECTIVE parameters
	gluPerspective(70,	1,	0.1,	10000.0);
	//field of view in the Y (vertically)
	//aspect ratio that determines the field of view in the X direction (horizontally)
	//near distance
	//far distance
}

int main(int argc, char **argv){
	glutInit(&argc,argv);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);	//Depth, Double buffer, RGB color

	glutCreateWindow("My OpenGL Program");

	init();
	
	

	glEnable(GL_DEPTH_TEST);	//enable Depth Testing

	glutDisplayFunc(display);	//display callback function
	glutIdleFunc(animate);		//what you want to do in the idle time (when no drawing is occuring)

	//ADD keyboard listeners:
	glutKeyboardFunc(keyboardListener);
	glutSpecialFunc(specialKeyListener);

	//ADD mouse listeners:
	glutMouseFunc(mouseListener);

	glutMainLoop();		//The main loop of OpenGL

	return 0;
}