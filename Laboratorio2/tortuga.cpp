#include <GL/glut.h>
#include <math.h>
#include <iostream>

using namespace std;

void Draw_Circle( float lados, float radio, float x, float y, float z)
{
  GLfloat DosPi = 2.0f * M_PI;
  glBegin(GL_LINES);

  for(int i = 0; i <=lados; i++) {
      glVertex3f(
          x+ (radio * cos(i *  DosPi / lados)),
          y+ (radio* sin(i * DosPi / lados)),
          z
      );
      glVertex3f(
          x+ (radio * cos((i+1) *  DosPi / lados)),
          y+ (radio* sin((i+1) * DosPi / lados)),
          z
      );
  }

  glEnd();
  glFlush();
}

void Turtle(void)
{
  glClearColor(1.0, 1.0, 1.0, 0.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glColor3f(0.0,0.0,1.0);

  Draw_Circle(30, 30, 0, 0, 0.0);
  Draw_Circle(30, 12, -30, 22, 0.0);
  Draw_Circle(30, 12, -30, -22, 0.0);
  Draw_Circle(30, 12, 30, 22, 0.0);
  Draw_Circle(30, 12, 30, -22, 0.0);
  Draw_Circle(30, 20, 0, 43, 0.0);

  glutSwapBuffers();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(400, 400);

    glutCreateWindow("Turtle");
    gluOrtho2D(-100,100,-100,100);

    glutDisplayFunc(Turtle);

    glutMainLoop();
    return 0;
}
