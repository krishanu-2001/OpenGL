#include <bits/stdc++.h>
#include <iostream>
#include <math.h>
#include <GL/glut.h>
using namespace std;
/*
 * Name: Krishanu Saini
 * Roll: 190001029
 * Ques: Problem 2) Scanline Fill Algorithm
 * Date: 10/02/22
 */
int inputSize;
int inputX[1000];
int inputY[1000];

// Start from lower left corner
struct edgeTuple
{
    // simplified version of [ymax, xatymin, delx, dely]
    int ymax; 
    float xofymin;
    float slopeinverse;
};

struct edgeTableList
{
    int countEdge; // no. of items
    edgeTuple buckets[12345];
};

edgeTableList edgetable[800], activeEdgeList;

void insertsort(edgeTableList *);
void setupEdges(int, int, int, int);
void saveEdgeTuple(edgeTableList *, int, int, float);
void removeymax(edgeTableList *, int);
void updatexval(edgeTableList *);
void Scanfill();

void DrawBoundary();
void Draw();

void Draw()
{
    glClear(GL_COLOR_BUFFER_BIT);
    // initialize table
    activeEdgeList.countEdge = 0;
    for (int i = 0; i < 800; i++)
    {
        edgetable[i].countEdge = 0;
    }

    DrawBoundary();
    // polygon filling using scanline
    Scanfill();
    glFlush();
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

void DrawBoundary()
{
    glColor3f(0, 0, 1);
    glBegin(GL_LINE_LOOP);
    int n = inputSize;
    for (int i = 0; i < n; i++)
    {
        cin >> inputX[i] >> inputY[i];
        glVertex2i(inputX[i], inputY[i]);
    }
    for (int i = 1; i < n; i++)
    {
        int x1 = inputX[i - 1];
        int y1 = inputY[i - 1];
        int x2 = inputX[i];
        int y2 = inputY[i];
        setupEdges(x1, y1, x2, y2);
    }
    glFlush();
    glEnd();
}

/*-------- Edge table utility ------*/
void saveEdgeTuple(edgeTableList *eb, int ymax, int xatymin, float slopeinverse)
{
    int n = eb->countEdge;
    eb->buckets[n] = {ymax, (float)xatymin, slopeinverse};
    /* sort it */
    insertsort(eb);
    eb->countEdge += 1;
}

/*-------- Create Edge Table --------*/
void setupEdges(int x1, int y1, int x2, int y2)
{
    int ymax, xatymin, y_scan;
    float slopeinverse;
    if (y2 == y1)
    {
        return;
    }
    slopeinverse = 0;
    if (x2 != x1)
    {
        slopeinverse = ((float)(x2 - x1)) / ((float)(y2 - y1));
    }

    y_scan = y1;
    ymax = y2;
    xatymin = x1;

    if (y1 > y2)
    {
        y_scan = y2;
        ymax = y1;
        xatymin = x2;
    }
    saveEdgeTuple(&edgetable[y_scan], ymax, xatymin, slopeinverse);
}

/* Insertion sort utility function O(n^2) */
void insertsort(edgeTableList *lst)
{
    int n = lst->countEdge;
    edgeTuple temp;
    for (int i = 1; i < n; i++)
    {
        temp = lst->buckets[i];
        int j = i - 1;
        while (j >= 0 && lst->buckets[j].xofymin > temp.xofymin)
        {
            lst->buckets[j + 1] = lst->buckets[j];
            j--;
        }
        lst->buckets[j + 1] = temp;
    }
}

/*-------- Edge table utility - remove from scanline if ymax O(n) --------*/
void removeymax(edgeTableList *Lst, int scanline)
{
    int n = Lst->countEdge;
    for (int i = 0; i < n; i++)
    {
        if (Lst->buckets[i].ymax == scanline)
        {
            int j = i;
            // shift left after deletion
            while (j < n - 1)
            {
                Lst->buckets[j] = Lst->buckets[j + 1];
                j++;
            }
            Lst->countEdge--;
            i--;
        }
    }
}

/*-------- Edge table utility - update x to x+1/m--------*/
void updatexval(edgeTableList *Lst)
{
    int n = Lst->countEdge;
    for (int i = 0; i < n; i++)
    {
        float minv = Lst->buckets[i].slopeinverse;
        Lst->buckets[i].xofymin = Lst->buckets[i].xofymin + minv;
    }
}

void Scanfill()
{
    /*
     * 1. Vectices at local extremum are counted twice
     * 2. otherwise once in pair
     */

    for (int i = 0; i < 800; i++)
    {
        // insert scanline into active edge list
        for (int j = 0; j < edgetable[i].countEdge; j++)
        {
            saveEdgeTuple(&activeEdgeList,
                          edgetable[i].buckets[j].ymax,
                          edgetable[i].buckets[j].xofymin,
                          edgetable[i].buckets[j].slopeinverse);
        }

        // Remove edges where ymax is reached
        removeymax(&activeEdgeList, i);

        // sort Active edge list
        insertsort(&activeEdgeList); // O(n^2)

        // pairing x coords
        int j = 0;
        int FillFlag = 0;
        int coordCount = 0;
        int x1 = 0, x2 = 0;
        int ymax1 = 0, ymax2 = 0;
        int n = activeEdgeList.countEdge;
        while (j < n)
        {
            if (coordCount % 2 == 0)
            {
                x1 = activeEdgeList.buckets[j].xofymin;
                ymax1 = activeEdgeList.buckets[j].ymax;
                if (x1 == x2)
                {
                    /* three cases can arrive-
                        1. lines are towards top of the intersection
                        2. lines are towards bottom
                        3. one line is towards top and other is towards bottom
                    */
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
                x2 = activeEdgeList.buckets[j].xofymin;
                ymax2 = activeEdgeList.buckets[j].ymax;
                FillFlag = 0;
                if (x1 == x2)
                {
                    /*three cases can arrive-
                        1. lines are towards top of the intersection
                        2. lines are towards bottom
                        3. one line is towards top and other is towards bottom
                    */
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
                    // drawing actual lines...
                    glColor3f(0.5, 0.5, 0.5);

                    glBegin(GL_LINES);
                    glVertex2i(x1, i);
                    glVertex2i(x2, i);
                    glEnd();
                    glFlush();

                    // printf("\nLine drawn from %d,%d to %d,%d",x1,i,x2,i);
                }
            }

            j++;
        }
        // get intersection points for next scanline
        updatexval(&activeEdgeList);
    }
}
