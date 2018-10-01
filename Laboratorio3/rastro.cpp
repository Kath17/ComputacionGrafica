#include <GL/glut.h>
#include <math.h>
#include <iostream>
#include <stdio.h>

using namespace std;


int np = 0;
float px[10000];
float py[10000];
float pz[10000];
GLdouble mModel[16];

//Dibuja circulo dado radio y num de lados
void Draw_Circle( float lados, float radio, float x, float y)
{
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
  }

  glEnd();
  glFlush();
}

void displayTrace() {
  int i;
  glColor3f(1.0,0.0,0.0) ;
  glBegin(GL_LINE_STRIP);
    for (i = 0; i < np; i++) {
      glVertex3f (px[i],py[i],pz[i]);
    }
  glEnd();
}

void addPointToTrace(){
  int i;
  GLdouble m[16];
  glGetDoublev(GL_MODELVIEW_MATRIX, m);

  printf("\nMatrix:\n");
  for(i=0; i<4; i++){
    printf("Row %i: %f \t%f \t%f \t%f \n", i+1, m[i+0], m[i+4], m[i+8], m[i+12]);
  }

  if(np==0){
    px[0] = 0;
    py[0] = 0;
    pz[0] = 0;
    np++;
  }
  px[np] = m[0] *px[0] + m[4] *py[0] + m[8] *pz[0] +m[12];
  py[np] = m[1] *px[0] + m[5] *py[0] + m[9] *pz[0] +m[13];
  pz[np] = m[2] *px[0] + m[6] *py[0] + m[10] *pz[0] +m[14];
  printf("Point %i: %f \t%f \t%f \n",np, px[np], py[np], pz[np]);
  np++;
}

//Dibuja la tortuga
void Turtle(void)
{
  glClearColor(1.0, 1.0, 1.0, 0.0);
  glClear(GL_COLOR_BUFFER_BIT);

  glPushMatrix();
	glMultMatrixd(mModel);

  glColor3f(0.0,0.0,1.0);
  Draw_Circle(10, 0.7, 0, -0.35);
  Draw_Circle(8, 0.3, -0.8, 0.1);
  Draw_Circle(8, 0.3, -0.8, -0.8);
  Draw_Circle(8, 0.3, 0.8, 0.1);
  Draw_Circle(8, 0.3, 0.8, -0.8);
  Draw_Circle(16, 0.5, 0, 0.7);

  glPopMatrix();
  displayTrace();

  glutSwapBuffers();

}

void reshape(int width, int height)
{
  glGetDoublev (GL_MODELVIEW_MATRIX, mModel);

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat)height / (GLfloat)width, 1.0, 128.0);
	glMatrixMode(GL_MODELVIEW);
	gluLookAt(0.0, 0.0, 3.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

//Traslaciones
void keyboard(unsigned char key, int x, int y)
{
  glPushMatrix();
  glLoadIdentity();
  glMultMatrixd(mModel);

  switch (key){
  case 'a':
    glRotatef(1.0, 0.0, 0.0, 1.0);
    break;
  case 's':
    glRotatef(1.0, 0.0, 0.0, -1.0);
    break;
  case 'q':
    glRotatef(1.0, 0.0, 1.0, 0.0);
    break;
  case 'w':
    glRotatef(1.0, 0., -1.0, 0.0);
    break;
  case 'z':
    glRotatef(1.0, 1.0, 0.0, 0.0);
    break;
  case 'x':
    glRotatef(1.0, -1.0, 0.0, 0.0);
    break;
  case 'k':
    glTranslatef(0.1, 0.0, 0.0);
    addPointToTrace();
    break;
  case 'h':
    glTranslatef(-0.1, 0., 0.0);
    addPointToTrace();
    break;
  case 'j':
    glTranslatef(0.0, -0.1, 0.0);
    addPointToTrace();
    break;
  case 'u':
    glTranslatef(0.0, 0.1, 0.0);
    addPointToTrace();
    break;
  case 'y':
    glScalef(0.7,0.7,0.7);
    break;
  case 'i':
    glScalef(2.0,2.0,2.0);
    break;
  case 't':
    exit(0);
    break;
  }
  glGetDoublev (GL_MODELVIEW_MATRIX, mModel);
  glPopMatrix();
	glutPostRedisplay();

}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(400, 400);

    glutCreateWindow("Turtle");

    glutDisplayFunc(Turtle);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);

    glutMainLoop();
    return 0;
}
