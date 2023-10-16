#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#define WIDTH 400
#define HEIGTH 400
#define ORIGIN_X 100
#define ORIGIN_Y 100

void init()
{
    glClearColor(0.0,0.0,0.0, 0.0);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT); 
    glLoadIdentity();

    /*Círculo con lineas*/
    /*int i;
    float radius = 1.0f;
    float ang = 0.0f;

    glColor3f( 1.0f, 1.0f, 1.0f);
    for (i = 0; i <360; i = i+3){
        ang = i * M_PI / 180.0f;
        glBegin(GL_LINES);
            glVertex3f(0.0, 0.0, -1.0);
            glVertex3f(cos(ang)*radius, sin(ang)*radius, 0.0); 

        glEnd();
    }*/

    /* Lo que haya que pintar ira aquí*/

    /* Triángulo Blanco */
    // glColor3f( 1.0f, 1.0f, 1.0f);
    // glBegin(GL_TRIANGLES);
    //     glVertex3f(-1.0f, 0.0f, 0.0f); //V1
    //     glVertex3f(1.0f, 0.0f, 0.0f); //V2
    //     glVertex3f(0.0f, 1.0f, 0.0f); //V3
    // glEnd();

    /* Triángulo Azul */
    // glShadeModel(GL_FLAT);
    // glBegin(GL_TRIANGLES);
    //     glColor3f( 1.0f, 0.0f, 0.0f);
    //     glVertex3f(-1.0f, 0.0f, 0.0f); //V1
    //     glColor3f( 0.0f, 1.0f, 0.0f);
    //     glVertex3f(1.0f, 0.0f, 0.0f); //V2
    //     glColor3f( 0.0f, 0.0f, 1.0f);
    //     glVertex3f(0.0f, 1.0f, 0.0f); //V3
    // glEnd();

    /* Triángulo Colores */
    glShadeModel(GL_SMOOTH);
    glBegin(GL_TRIANGLES);
        glColor3f( 1.0f, 0.0f, 0.0f);
        glVertex3f(-1.0f, 0.0f, -1.0f); //V1
        glColor3f( 0.0f, 1.0f, 0.0f);
        glVertex3f(1.0f, 0.0f, -1.0f); //V2
        glColor3f( 0.0f, 0.0f, 1.0f);
        glVertex3f(0.0f, 1.0f, -1.0f); //V3
    glEnd();

    glutSwapBuffers();
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, 0.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv)
{
 glutInit(&argc, argv); 
 glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); 
 glutInitWindowSize(WIDTH, HEIGTH); 
 glutInitWindowPosition(ORIGIN_X, ORIGIN_Y); 
 glutCreateWindow("Hola Mundo"); 
 init();
 glutDisplayFunc(display); 
 glutReshapeFunc(reshape); 
 glutMainLoop(); 
 return 0;
}