#include <iostream>
#include <math.h>
#include <GL/glut.h>
using namespace std;

int inputSize;
typedef struct edgebucket
{
	int ymax;
	float xofymin;
	float slopeinverse;
} EdgeBucket;

typedef struct edgetabletup
{
	int countEdgeBucket;
	EdgeBucket buckets[10000];
} EdgeTableTuple;

EdgeTableTuple EdgeTable[800], ActiveEdgeTuple;

// Scanline Function
void init();
void insertionSort(EdgeTableTuple *);
void storeEdge(EdgeTableTuple *receiver, int ym, int xm, float slopInv);
void storeEdgeInTable(int x1, int y1, int x2, int y2);
void removeEdgeByYmax(EdgeTableTuple *Tup, int yy);

void removeEdgeByYmax(EdgeTableTuple *Tup, int yy)
{
	int i, j;
	for (i = 0; i < Tup->countEdgeBucket; i++)
	{
		if (Tup->buckets[i].ymax == yy)
		{
			for (j = i; j < Tup->countEdgeBucket - 1; j++)
			{
				Tup->buckets[j].ymax = Tup->buckets[j + 1].ymax;
				Tup->buckets[j].xofymin = Tup->buckets[j + 1].xofymin;
				Tup->buckets[j].slopeinverse = Tup->buckets[j + 1].slopeinverse;
			}
			Tup->countEdgeBucket--;
			i--;
		}
	}
}

void updatexbyslopeinv(EdgeTableTuple *Tup)
{
	int i;

	for (i = 0; i < Tup->countEdgeBucket; i++)
	{
		(Tup->buckets[i]).xofymin = (Tup->buckets[i]).xofymin + (Tup->buckets[i]).slopeinverse;
	}
}

void scanlineFill()
{
	int i, j, x1, ymax1, x2, ymax2, FillFlag = 0, coordCount;
	for (i = 0; i < 800; i++)
	{
		for (j = 0; j < EdgeTable[i].countEdgeBucket; j++)
		{
			storeEdge(&ActiveEdgeTuple, EdgeTable[i].buckets[j].ymax, EdgeTable[i].buckets[j].xofymin,
					  EdgeTable[i].buckets[j].slopeinverse);
		}
		removeEdgeByYmax(&ActiveEdgeTuple, i);
		insertionSort(&ActiveEdgeTuple);
		j = 0;
		FillFlag = 0;
		coordCount = 0;
		x1 = 0;
		x2 = 0;
		ymax1 = 0;
		ymax2 = 0;
		while (j < ActiveEdgeTuple.countEdgeBucket)
		{
			if (coordCount % 2 == 0)
			{
				x1 = (int)(ActiveEdgeTuple.buckets[j].xofymin);
				ymax1 = ActiveEdgeTuple.buckets[j].ymax;
				if (x1 == x2)
				{
					if (((x1 == ymax1) && (x2 != ymax2)) || ((x1 != ymax1) && (x2 == ymax2)))
					{
						x2 = x1;
						ymax2 = ymax1;
					}

					else
					{
						coordCount++;
					}
				}

				else
				{
					coordCount++;
				}
			}
			else
			{
				x2 = (int)ActiveEdgeTuple.buckets[j].xofymin;
				ymax2 = ActiveEdgeTuple.buckets[j].ymax;
				FillFlag = 0;
				if (x1 == x2)
				{
					if (((x1 == ymax1) && (x2 != ymax2)) || ((x1 != ymax1) && (x2 == ymax2)))
					{
						x1 = x2;
						ymax1 = ymax2;
					}
					else
					{
						coordCount++;
						FillFlag = 1;
					}
				}
				else
				{
					coordCount++;
					FillFlag = 1;
				}

				if (FillFlag)
				{
					glColor3f(0.0f, 0.7f, 0.0f);
					glBegin(GL_LINES);
					glVertex2i(x1, i);
					glVertex2i(x2, i);
					glEnd();
					glFlush();
				}
			}

			j++;
		}
		updatexbyslopeinv(&ActiveEdgeTuple);
	}
}

void myInit(void)
{

	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();
	gluOrtho2D(0, 800, 0, 600);
	glClear(GL_COLOR_BUFFER_BIT);
}

void drawboundary()
{

	glColor3f(1.0f, 0.0f, 0.0f);
	int count = 0, x1, y1, x2, y2;
	int i = 0;
	while (i < inputSize)
	{
		i++;
		count++;
		if (count > 2)
		{
			x1 = x2;
			y1 = y2;
			count = 2;
		}
		if (count == 1)
		{
			cin >> x1 >> y1;
		}
		else
		{
			cin >> x2 >> y2;
			glBegin(GL_LINES);
			glVertex2i(x1, y1);
			glVertex2i(x2, y2);
			glEnd();
			storeEdgeInTable(x1, y1, x2, y2);

			glFlush();
		}
	}
}

void Draw(void)
{
	init();
	drawboundary();
	printf("\nTable");
	scanlineFill(); // actual calling of scanline filling..
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 800);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	cin >> inputSize;
	glutCreateWindow("");
	gluOrtho2D(0, 800, 0, 800);
	glClearColor(1, 1, 1, 0.0);
	glutDisplayFunc(Draw);
	glutMainLoop();
	return 0;
}

void init()
{
	int i;
	for (i = 0; i < 800; i++)
	{
		EdgeTable[i].countEdgeBucket = 0;
	}

	ActiveEdgeTuple.countEdgeBucket = 0;
}

void insertionSort(EdgeTableTuple *ett)
{
	int i, j;
	EdgeBucket temp;

	for (i = 1; i < ett->countEdgeBucket; i++)
	{
		temp.ymax = ett->buckets[i].ymax;
		temp.xofymin = ett->buckets[i].xofymin;
		temp.slopeinverse = ett->buckets[i].slopeinverse;
		j = i - 1;

		while ((temp.xofymin < ett->buckets[j].xofymin) && (j >= 0))
		{
			ett->buckets[j + 1].ymax = ett->buckets[j].ymax;
			ett->buckets[j + 1].xofymin = ett->buckets[j].xofymin;
			ett->buckets[j + 1].slopeinverse = ett->buckets[j].slopeinverse;
			j = j - 1;
		}
		ett->buckets[j + 1].ymax = temp.ymax;
		ett->buckets[j + 1].xofymin = temp.xofymin;
		ett->buckets[j + 1].slopeinverse = temp.slopeinverse;
	}
}

void storeEdge(EdgeTableTuple *receiver, int ym, int xm, float slopInv)
{
	// both used for edgetable and active edge table..
	// The edge tuple sorted in increasing ymax and x of the lower end.
	(receiver->buckets[(receiver)->countEdgeBucket]).ymax = ym;
	(receiver->buckets[(receiver)->countEdgeBucket]).xofymin = (float)xm;
	(receiver->buckets[(receiver)->countEdgeBucket]).slopeinverse = slopInv;

	// sort the buckets
	insertionSort(receiver);

	(receiver->countEdgeBucket)++;
}

void storeEdgeInTable(int x1, int y1, int x2, int y2)
{
	float m, minv;
	int ymaxTS, xwithyminTS, scanline; // ts stands for to store

	if (x2 == x1)
	{
		minv = 0.000000;
	}
	else
	{
		m = ((float)(y2 - y1)) / ((float)(x2 - x1));

		// horizontal lines are not stored in edge table
		if (y2 == y1)
			return;

		minv = (float)1.0 / m;
		printf("\nSlope string for %d %d & %d %d: %f", x1, y1, x2, y2, minv);
	}

	if (y1 > y2)
	{
		scanline = y2;
		ymaxTS = y1;
		xwithyminTS = x2;
	}
	else
	{
		scanline = y1;
		ymaxTS = y2;
		xwithyminTS = x1;
	}
	storeEdge(&EdgeTable[scanline], ymaxTS, xwithyminTS, minv);
}
