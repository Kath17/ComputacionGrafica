#include <GL/glut.h>
#include <math.h>
 
void displayMe(void)
{
    int lados=20;
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
 
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(400, 300);
    glutInitWindowPosition(100, 100);
    glutDisplayFunc(displayMe);
    glutMainLoop();
    return 0;
}