#include <GL/glut.h>
#include <math.h>

/*   EJERCICIOS 2.4  */


/*******      1. Dibuja Poligono con lados iguales      ******/
void DibujarPoligono(void)
{
    int lados = 5;
    GLfloat radio = 0.8f; //radius
    GLfloat DosPi = 2.0f*M_PI;

    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINES);

    for(int i = 0; i <=lados; i++) {
        glVertex2f(
            (radio * cos(i *  DosPi / lados)),
            (radio* sin(i * DosPi / lados))
        );
        glVertex2f(
            (radio * cos((i+1) *  DosPi / lados)),
            (radio* sin((i+1) * DosPi / lados))
        );
    }
    glEnd();
    glFlush();
}

/******   2. Dibuja Circulo dado lado y radio  *********/
void DibujarCirculo(void)
{
    int lados = 5;
    GLfloat radio = 0.8f; //radius
    GLfloat DosPi = 2.0f*M_PI;

    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINES);

    for(int i = 0; i <=lados; i++) {
        glVertex2f(
            (radio * cos(i *  DosPi / lados)),
            (radio* sin(i * DosPi / lados))
        );
        glVertex2f(
            (radio * cos((i+1) *  DosPi / lados)),
            (radio* sin((i+1) * DosPi / lados))
        );
    }
    glEnd();
    glFlush();
}

/****** 3.Rutinas que simulen pen_up pen_down locate(dex,dey)  *****/

/*
  void Pen_up()
  {
    lapiz_arriba = true;
  }
  void Pen_down()
  {
    lapiz_arriba = false;
  }
  void locate(int dex, int dey)
  {
    if(Pen_down()){
      DrawTo(dex,dey);
    }
    else if(Pen_up()){
      MoveTo(dex,dey);
    }
  }

*/

/***********  4. Ejercicio 4  **************/

float width = 42; //cm
float heigth = 31; //cm
float ndh = 546;
float ndv = 434;

//Estan en centimetros


float razongrafica( float width, float heigth, float ndh, float ndv)
{
  float Vert = heigth * 10/ ndv;
  float Hori = width * 10/ ndh;

  cout<<"Vertical: "<< Vert;
  cout<<"Horizontal: "<< Hori;

  float razon = Vert/Hori;

  return razon;
}

float razonfisica( float width, float heigth)
{
  float razon = heigth/width;

  return razon;
}

float resolucionVertical( float heigth, float ndv)
{
  float resolucion = ndv / (heigth * 10);
  return resolucion;
}

float resolucionHorizontal( float width, float ndh)
{
  float resolucion = ndh / (width * 10);
  return resolucion;
}

void Ejercicio4()
{
  cout<<razongrafica(width,heigth,ndh,ndv);
  //Respuesta: 0.714

  cout<<razonfisica(width,heigth);
  //Respuesta: 0.769

  cout<<resolucionVertical(heigth,ndv);
  //Respuesta: 1.4

  cout<<resolucionHorizontal(width,ndh);
  //Respuesta: 1.3

}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(400, 300);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Dibujar");
    glutDisplayFunc(DibujarCirculo);
    glutMainLoop();
    return 0;
}
