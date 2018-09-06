#include <GL/glut.h>
#include <math.h>
#include <iostream>

using namespace std;
 
void displayMe(void)
{

    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);

    int X1 = -40;
    int Y1 = -20; 
    int X2 = 100;
    int Y2 = 30;

    // calculate dx & dy
    int dx = X2 - X1;
    int dy = Y2 - Y1;
 
    // initial value of decision parameter d
    int d = dy - (dx/2);
    int x = X1, y = Y1;

    glVertex2f(x,y);
 
    //Recorrer hasta el otro extremo
    while (x < X2)
    {
        x++;
 
        if (d < 0)
            d = d + dy;
 
        else
        {
            d += (dy - dx);
            y++;
        }
 
        cout << x << "," << y << "\n";
        glVertex2f(x,y);
    }
    
    glEnd();
    glFlush();
}
 
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(400, 400);

    glutCreateWindow("Circulo");
    gluOrtho2D(-100,100,-100,100);
    glutDisplayFunc(displayMe);
    glutMainLoop();
    return 0;
}