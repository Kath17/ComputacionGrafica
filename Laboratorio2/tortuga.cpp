#include <GL/glut.h>
#include <math.h>
#include <iostream>

using namespace std;

//Dibuja circulo dado radio y num de lados
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

//Dibuja la tortuga
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

void reshape(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat)height / (GLfloat)width, 1.0, 128.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(-5.0, -20.0, 100.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}


//Traslaciones
void keyboard(unsigned char key, int x, int y)
{
	switch (key){
	case 'a':
		glRotatef(1.0, 0.0, 0.0, 1.0);
		break;
	case 's':
		glRotatef(1.0, 0.0, 0.0, -1.0);
		break;
	case 'd':
		glRotatef(1.0, 0.0, 1.0, 0.0);
		break;
	case 'f':
		glRotatef(1.0, 0., -1.0, 0.0);
		break;
  case 'g':
		glRotatef(1.0, 1.0, 0.0, 0.0);
		break;
  case 'h':
		glRotatef(1.0, -1.0, 0.0, 0.0);
		break;
	case 'j':
    glTranslatef(0.1, 0.0, 0.0);
		break;
	case 'k':
		glTranslatef(-0.1, 0., 0.0);
		break;
	case 'l':
		glTranslatef(0.0, -0.1, 0.0);
		break;
	case 'ñ':
    glTranslatef(0.0, 0.1, 0.0);
		break;
	case 'e':
		exit(0);
		break;
	}
	glutPostRedisplay();
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(400, 400);

    glutCreateWindow("Turtle");

    glutDisplayFunc(Turtle);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);

    glutMainLoop();
    return 0;
}
