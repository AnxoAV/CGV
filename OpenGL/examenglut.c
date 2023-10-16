//Autor: Anxo Abuelo Veira

#include <stdio.h>
#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdbool.h>

#define ancho 500
#define alto 500


GLfloat angulos[2][3]; //Matriz para controlar los ángulos de rotación de los cubos
GLfloat angulosp[2][3];
GLboolean modo = false; //Variable de control para seleccionar la parte del brazo de manera predeterminada se moverá todo el brazo, 
                            //Si se pulsa el 1 se pasará a mover solo el "cubo" del extremo y si se pulsa el 0 se volverá al modo predeterminado
GLboolean mover = true;
GLint64 i = 0;
GLint64 j = 0;

GLint64 velocidad = 0;


void init()
{
    glClearColor(0.0f,0.0f,0.0f,0.0f);  //Elegimos el color del fondo
}


void triangulo(){
    glColor3f(0.5f,1.0f,1.0f);
    glBegin(GL_TRIANGLES);
        glVertex3f(-1.8, -0.5, 0.1);
        glVertex3f(1.8, -0.5, 0.1);
        glVertex3f(0, -0.5, 3.5);
    glEnd();
    glBegin(GL_TRIANGLES);
        glVertex3f(-1.8, 0.5, 0.1);
        glVertex3f(1.8, 0.5, 0.1);
        glVertex3f(0, 0.5, 3.5);
    glEnd();
    glBegin(GL_QUADS);
        glVertex3f(-1.8, -0.5, 0.1);
        glVertex3f(0, -0.5, 3.5);
        glVertex3f(0, 0.5, 3.5);
        glVertex3f(-1.8, 0.5, 0.1);
    glEnd();
    glBegin(GL_QUADS);
        glVertex3f(1.8, -0.5, 0.1);
        glVertex3f(0, -0.5, 3.5);
        glVertex3f(0, 0.5, 3.5);
        glVertex3f(1.8, 0.5, 0.1);
    glEnd();
}

void circulo(){
    int i;
    float radius = 1.0f;
    float ang = 0.0f;
    glBegin(GL_POLYGON);
    for (i = 0; i <360; i = i+3){
        ang = i * M_PI / 180.0f;
            
        glVertex3f(cos(ang)*radius, sin(ang)*radius, 0.0); 
    }
    glEnd();

}

void anillo(){
    int i;
    float radius = 1.0f;
    float ang = 0.0f;

    glBegin(GL_POLYGON_BIT);

    for (i = 0; i <360; i = i+3){
        ang = i * M_PI / 180.0f;
        glVertex3f(cos(ang)*radius, sin(ang)*radius, 0.0); 
        glVertex3f(cos(ang)*radius, sin(ang)*radius, 1.0); 
    }
    glEnd();

}

void cilindro(){
    GLUquadric* qobj;
    qobj = gluNewQuadric();
    
    // Final de la pila
    glLoadIdentity();

    // Trasladamos todo en el ángulo Z
    glRotatef(45,1.0,0.0,0.0);
    glColor3f(0.5,0.5,0.5);
    gluCylinder(qobj, 2.0f, 2.0f, 1.0f, 10, 5);
}

void display(){ 

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //triangulo();
    glutSwapBuffers();
}

void timerRotation(int value){
    angulosp[0][1]+= value;
    angulosp[0][1] = ((int)angulosp[0][1])%360;
    glutTimerFunc(velocidad,timerRotation,5);
}

void prisma(float radio, float altura, float lados, float particiones) {
    glPushMatrix();
    glRotatef(-90, 1, 0, 0);

    GLUquadricObj* quadratic;
    quadratic = gluNewQuadric();
    gluCylinder(quadratic, radio, radio, altura, lados, particiones);

    quadratic = gluNewQuadric();
    gluDisk(quadratic, 0, radio, lados, particiones);
    glTranslatef(0, 0, altura);
    quadratic = gluNewQuadric();
    gluDisk(quadratic, 0, radio, lados, particiones);
    glPopMatrix();
}

void idle(){ //Función para llamar al display dentro del bucle
    display();
}


void menu_1(int id){
    switch (id)
    {
    case 0:
        modo = true;
        break;
    case 1:
        modo = false;
        break;
    default:
        break;
    }
}

void menu_2(int id){
    
    switch (id)
    {
    case 0: 
        velocidad = 1;
        break;
    case 1:
        velocidad = 200;
        break;
    case 2:
        velocidad = 500;
        break; 
    case 3:
        mover = false;
        break;
    default:
        break;
    }
}

void menu(){
    int submenu;
    submenu = glutCreateMenu(menu_2);
    glutAddMenuEntry("Rapido", 0);
    glutAddMenuEntry("Medio", 1);
    glutAddMenuEntry("Lento",2);
    glutAddMenuEntry("Parar",3);

    glutCreateMenu(menu_1);
    glutAddSubMenu("Velocidades", submenu);
    glutAddMenuEntry("Solid", 0);
    glutAddMenuEntry("Wire", 1);

    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void keyboardHandler(unsigned char key, int x, int y ){ //Función para controlar el brazo por teclado
    if(key == '1'){  //Pulsando la tecla 1 cambiamos el modo para pasar a mover solo el cubo del extremo
        i = 1;
        j = 1;
    }

    if(key == '0'){ //Pulsando la tecla 0 volvemos al modo predeterminado que es mover todo el brazo
        i = 0;
        j = 0;
    }

        switch(key){   //Con este switch controlamos la rotación en las distintas coordenadas de todo el brazo
            case 'q':
                angulos[i][0]+=1;
                break;
            case 'a':
                angulos[i][0]-=1;
                break;
            case 'w':
                angulos[i][1]+=1;
                break;
            case 's':
                angulos[i][1]-=1;
                break;
            case 'e':
                angulos[i][2]+=1;
                break;
            case 'd':
                angulos[i][2]-=1;
                break;
            case 'u':
                angulosp[j][0]+=1;
                break;
            case 'j':
                angulosp[j][0]-=1;
                break;
            case 'i':
                angulosp[j][1]+=1;
                break;
            case 'k':
                angulosp[j][1]-=1;
                break;
            case 'o':
                angulosp[j][2]+=1;
                break;
            case 'l':
                angulosp[j][2]-=1;
                break;

            default:
                break;
        }
}

void reshape(int w, int h) //Función para seleccionar el tamaño de la ventana,el lugar en el que vamos a poder dibujar y el volumen de vista
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-7.0, 7.0, -7.0, 7.0, -10.0, 10.0); 
    glMatrixMode(GL_MODELVIEW);

}


int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB| GLUT_DEPTH);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(ancho, alto);
    glutCreateWindow("Brazo");
    glEnable(GL_DEPTH_TEST); //Función para activar el Z-Buffer
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    //glutIdleFunc(idle);
    glutKeyboardFunc(keyboardHandler);
    menu();
    glutMainLoop();
    return 0;
}