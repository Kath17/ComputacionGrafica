#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include <vector>
#include <iostream>

using namespace std;

vector<int> vector_x;
vector<int> vector_y;
float x=-700, y=-700, x2 = -700, y2=-700;
int first_x, first_y;
int n_points=0;

const int maxHt = 600;
const int maxWd = 600;
const int maxVer = 10000;

void myInit(void)
{
	glClearColor(1.0,1.0,1.0,0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glColor3f(1,0,0);
	gluOrtho2D(0,maxHt,0,maxWd);
	glPointSize(3);
}

typedef struct edgebucket
{
		int ymax;
		float xofymin;
		float slopeinverse;
} EdgeBucket;

typedef struct edgetabletup
{
		int countEdgeBucket;
		EdgeBucket buckets[maxVer];
} EdgeTableTuple;

EdgeTableTuple EdgeTable[maxHt], ActiveEdgeTuple;

void initEdgeTable()
{
		int i;
		for (i=0; i<maxHt; i++){
			EdgeTable[i].countEdgeBucket = 0;
		}
		ActiveEdgeTuple.countEdgeBucket = 0;
}

void insertionSort(EdgeTableTuple *ett)
{
		int i,j;
		EdgeBucket temp;

		for (i = 1; i < ett->countEdgeBucket; i++)
		{
				temp.ymax = ett->buckets[i].ymax;
				temp.xofymin = ett->buckets[i].xofymin;
				temp.slopeinverse = ett->buckets[i].slopeinverse;
				j = i - 1;

				while ((temp.xofymin < ett->buckets[j].xofymin) && (j >= 0)){
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

void storeEdgeInTuple (EdgeTableTuple *receiver,int ym,int xm,float slopInv)
{
		(receiver->buckets[(receiver)->countEdgeBucket]).ymax = ym;
		(receiver->buckets[(receiver)->countEdgeBucket]).xofymin = (float)xm;
		(receiver->buckets[(receiver)->countEdgeBucket]).slopeinverse = slopInv;
		insertionSort(receiver);
		(receiver->countEdgeBucket)++;
}

void storeEdgeInTable (int x1,int y1, int x2, int y2)
{
		float m,minv;
		int ymaxTS,xwithyminTS, scanline;
		if (x2==x1){
			minv=0.000000;
		}
		else{
			m = ((float)(y2-y1))/((float)(x2-x1));
			if (y2==y1)
				return;
			minv = (float)1.0/m;
		}
		if (y1>y2){
			scanline=y2;
			ymaxTS=y1;
			xwithyminTS=x2;
		}
		else{
			scanline=y1;
			ymaxTS=y2;
			xwithyminTS=x1;
		}
		storeEdgeInTuple(&EdgeTable[scanline],ymaxTS,xwithyminTS,minv);
}

void removeEdgeByYmax(EdgeTableTuple *Tup,int yy)
{
		int i,j;
		for (i=0; i< Tup->countEdgeBucket; i++){
				if (Tup->buckets[i].ymax == yy){
							for ( j = i ; j < Tup->countEdgeBucket -1 ; j++ ){
									Tup->buckets[j].ymax =Tup->buckets[j+1].ymax;
									Tup->buckets[j].xofymin =Tup->buckets[j+1].xofymin;
									Tup->buckets[j].slopeinverse = Tup->buckets[j+1].slopeinverse;
							}
						Tup->countEdgeBucket--;
					i--;
				}
		}
}

void updatexbyslopeinv(EdgeTableTuple *Tup)
{
	int i;
	for (i=0; i<Tup->countEdgeBucket; i++){
			(Tup->buckets[i]).xofymin =(Tup->buckets[i]).xofymin + (Tup->buckets[i]).slopeinverse;
	}
}

void ScanlineFill()
{
	int i, j, x1, ymax1, x2, ymax2, FillFlag = 0, coordCount;

	for (i=0; i<maxHt; i++){
		for (j=0; j<EdgeTable[i].countEdgeBucket; j++){
			storeEdgeInTuple(&ActiveEdgeTuple,EdgeTable[i].buckets[j].
					ymax,EdgeTable[i].buckets[j].xofymin,
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

		while (j<ActiveEdgeTuple.countEdgeBucket){
			if (coordCount%2==0){
				x1 = (int)(ActiveEdgeTuple.buckets[j].xofymin);
				ymax1 = ActiveEdgeTuple.buckets[j].ymax;
				if (x1==x2){
					if (((x1==ymax1)&&(x2!=ymax2))||((x1!=ymax1)&&(x2==ymax2))){
						x2 = x1;
						ymax2 = ymax1;
					}
					else{
						coordCount++;
					}
				}
				else{
						coordCount++;
				}
			}
			else{
				x2 = (int)ActiveEdgeTuple.buckets[j].xofymin;
				ymax2 = ActiveEdgeTuple.buckets[j].ymax;

				FillFlag = 0;
				if (x1==x2){
					if (((x1==ymax1)&&(x2!=ymax2))||((x1!=ymax1)&&(x2==ymax2))){
						x1 = x2;
						ymax1 = ymax2;
					}
					else{
						coordCount++;
						FillFlag = 1;
					}
				}
				else{
						coordCount++;
						FillFlag = 1;
				}

				if(FillFlag){
					glColor3f(1.0f,0.0f,0.0f);
					glBegin(GL_LINES);
					glVertex2i(x1,i);
					glVertex2i(x2,i);
					glEnd();
					glFlush();
				}
			}
			j++;
		}
		updatexbyslopeinv(&ActiveEdgeTuple);
	}
}

void draw_line(int x1, int y1, int x2, int y2)
{
  glBegin(GL_POINTS);

	int dx, dy, i, e;
  int incx, incy, inc1, inc2;
  int x,y;

  dx = x2-x1;
  dy = y2-y1;

  if (dx < 0) dx = -dx;
  if (dy < 0) dy = -dy;
  incx = 1;
  if (x2 < x1) incx = -1;
  incy = 1;
  if (y2 < y1) incy = -1;
  x = x1;
	y = y1;
  if (dx > dy) {
    glVertex2f(x,y);
    cout<<"Dibujar: x= "<<x <<", y= "<<y<<endl;
    e = 2 * dy-dx;
    inc1 = 2*(dy-dx);
    inc2 = 2*dy;
    for (i=0; i<dx; i++) {
      if (e >= 0) {
        y += incy;
        e += inc1;
      }
      else
        e += inc2;
      x += incx;
      glVertex2f(x,y);
      cout<<"Dibujar: x= "<<x <<", y= "<<y<<endl;
    }

  }
	else {
    glVertex2f(x,y);
    cout<<"Dibujar: x= "<<x <<", y= "<<y<<endl;
    e = 2*dx-dy;
    inc1 = 2*(dx-dy);
    inc2 = 2*dx;
    for (i=0; i<dy; i++) {
      if (e >= 0) {
        x += incx;
        e += inc1;
      }
      else
        e += inc2;
      y += incy;
      glVertex2f(x,y);
      cout<<"Dibujar: x= "<<x <<", y= "<<y<<endl;
    }
  }

  glEnd();
  glFlush();
}

//Dibuja circulo dado radio y num de lados
void Draw_Circle( float lados, float radio)
{
	float x=300;
	float y=300;
  GLfloat DosPi = 2.0f * M_PI;
  glBegin(GL_LINES);

  for(int i = 0; i <=lados; i++) {
      glVertex2f(
          x+ (radio * cos(i *  DosPi / lados)),
          y+ (radio* sin(i * DosPi / lados))
      );
      glVertex2f(
          x+ (radio * cos((i+1) *  DosPi / lados)),
          y+ (radio* sin((i+1) * DosPi / lados))
      );
			vector_x.push_back(x+ (radio * cos(i *  DosPi / lados)));
			vector_y.push_back(y+ (radio* sin(i * DosPi / lados)));
  }
  glEnd();
  glFlush();
}

void draw_polygon(void)
{
  for(int i = 0; i < vector_x.size()-1; i++){
    draw_line(vector_x.at(i), vector_y.at(i),vector_x.at(i+1), vector_y.at(i+1));
  }
}

void FillPolygon()
{
	glColor3f(1.0f,0.0f,0.0f);
	int count = 0,x1,y1,x2,y2;

	for(int i=0; i< vector_x.size();i++)
	{
		count++;
		if (count>2){
			x1 = x2;
			y1 = y2;
			count=2;
		}
		if (count==1){
			x1 = vector_x[i];
			y1 = vector_y[i];
		}
		else{
			x2 = vector_x[i];
			y2 = vector_y[i];

			glBegin(GL_LINES);
				glVertex2i( x1, y1);
				glVertex2i( x2, y2);
			glEnd();
			storeEdgeInTable(x1, y1, x2, y2);
			glFlush();
		}
	}
	ScanlineFill();
}

void Mouse_Event(int button, int state, int mouse_x, int mouse_y)
{
  mouse_y = glutGet(GLUT_WINDOW_HEIGHT) - mouse_y;
  cout<<"Punto: x="<<mouse_x <<", y="<<mouse_y<<endl;

  if(button == GLUT_LEFT_BUTTON && state== GLUT_DOWN)
  {
    if(x ==-700 && y==-700){
      first_x = mouse_x;
      first_y = mouse_y;
      x = mouse_x;
      y = mouse_y;
      x2 = mouse_x;
      y2 = mouse_y;
      vector_x.push_back(x);
      vector_y.push_back(y);
    }
    else{
      x = x2;
      y = y2;
      x2 = mouse_x;
      y2 = mouse_y;
      vector_x.push_back(x2);
      vector_y.push_back(y2);
    }

    n_points++;
    cout<<"Punto: x= "<<x <<", y= "<<y<<endl;
    cout<<"Punto: x2= "<<x2 <<", y2= "<<y2<<endl;

		if(n_points > 1){
			draw_line(x,y,x2,y2);
		}
  }

  else if(button == GLUT_RIGHT_BUTTON && state== GLUT_DOWN)
  {
		draw_line(first_x,first_y,x2,y2);
    vector_x.push_back(first_x);
    vector_y.push_back(first_y);
    draw_polygon();
  }

	else if(button == GLUT_MIDDLE_BUTTON && state== GLUT_DOWN)
	{
		int lados;
		cout<<"Ingresar numero de lados: "<<endl;
		cin>>lados;
		Draw_Circle(lados,100);
		draw_polygon();
	}
}

void Polygon(void)
{
	glClearColor(1, 1, 1, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	initEdgeTable();
	FillPolygon();
	glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key){
  case 'z':
    glRotatef(10.0, 0.0, 0.0, 10.0);
    break;
  case 'x':
    glRotatef(10.0, 0.0, 0.0, -10.0);
    break;
  case 'd':
    glTranslatef(2.0, 0.0, 0.0);
    break;
  case 'a':
    glTranslatef(-2.0, 0., 0.0);
    break;
  case 's':
    glTranslatef(0.0, -2.0, 0.0);
    break;
  case 'w':
    glTranslatef(0.0, 2.0, 0.0);
    break;
  case 'q':
    glScalef(0.9,0.9,0.9);
    break;
  case 'e':
    glScalef(1.1,1.1,1.1);
    break;
	case 'f':
		Polygon();
		break;
  case 't':
    exit(0);
    break;
  }
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowPosition(1000, 150);
	glutInitWindowSize(maxHt,maxWd);

	glutCreateWindow("Trabajo");

	myInit();
	glutDisplayFunc(Polygon);
	glutMouseFunc(Mouse_Event);
	glutKeyboardFunc(keyboard);

	glutMainLoop();
  return 0;
}
