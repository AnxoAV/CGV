
//Autor: Anxo Abuelo Veira

#include <stdio.h>
#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdbool.h>

GLint ancho=700;
GLint alto=700;

int hazPerspectiva = 0;


GLfloat angulos[2][3]; //Matriz para controlar los ángulos de rotación de los cubos
GLfloat angulosp[2][3];
GLboolean modo = false; //Variable de control para seleccionar la parte del brazo de manera predeterminada se moverá todo el brazo, 
                            //Si se pulsa el 1 se pasará a mover solo el "cubo" del extremo y si se pulsa el 0 se volverá al modo predeterminado
GLboolean girar = true; 
GLboolean cambio = false; 
GLint64 i = 0;
GLint64 j = 0;
GLfloat red = 0.0f;
GLfloat green = 1.0f;
GLfloat blue = 0.0f;

GLint64 velocidad = 0;


void init()
{
    glClearColor(0.0f,0.0f,0.0f,0.0f);  //Elegimos el color del fondo
}


void triangulo(float tx,float ty,float tz){

    glTranslatef(tx,ty,tz);
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

void base(){

    glRotatef(90,1.0,.0,0.0);

    glColor3f(0.5f,0.5f,0.5f);
    circulo();
    glTranslatef(0.0f,-0.0f,2.0f);
    circulo();
    anillo();
}

void brazo(float tx,float ty,float tz){

    glTranslatef(tx,ty,tz);

    glRotatef(90,1.0,0.0,0.0);
    glRotatef(angulos[0][1],0.0,1.0,0.0);

    glPushMatrix();

    glTranslatef(2.5,0.0,0.35);


    glScalef(5.0,1.0,1.0);
    glColor3f(1.0f,0.7f,0.2f);
    glutSolidCube(1.0f);

    glLoadIdentity();

    glPopMatrix();

    glTranslatef(5.0,2.5,1.0);

    glRotatef(angulos[1][0],0.0,1.0,0.0);

    glPushMatrix();

    glColor3f(1.0f,0.0f,1.0f);
    //glTranslatef(5.0,2.5,1.0);
    glScalef(3.5,4.0,2.0);
    glutSolidCube(1.0f);

    glLoadIdentity();

    glPopMatrix();
    glColor3f(red,green,blue);
    glTranslatef(-0.7,-1.0,-1.5);
    glutSolidCube(1.0f);

    glTranslatef(1.5,0.0,0.0);
    glutSolidCube(1.0f);

    glTranslatef(0.0,2.0,0.0);
    glutSolidCube(1.0f);

    glTranslatef(-1.5,0.0,0.0);
    glutSolidCube(1.0f);

    if(girar == true){
        if(cambio == true){
            angulos[0][1]-=1;
            angulos[1][0]+=1;
        }else{
            angulos[0][1] +=1;
            angulos[1][0] -=1; 
        }
    }


}

void display(){     
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    glTranslatef(0.0f,0.0f,-20.0f);

    if(modo == true){
        glRotatef(90,1.0,0.0,0.0);
    }else{
        glRotatef(0,1.0,0.0,0.0);
    }

    glPushMatrix();

    glLoadIdentity();

    glPopMatrix();
    glPushMatrix();


    glScalef(8.0,1.0,3.0);
    base();

    glLoadIdentity();

    glPopMatrix();
    glPushMatrix();

    glRotatef(-90,1.0,0.0,0.0);
    glScalef(4,1.0,3.0);
    triangulo(0.0,0.0,-1.1);

    glLoadIdentity();

    glPopMatrix();

    brazo(0.0,7,1.0);

    glutSwapBuffers();
}

void idle(){ //Función para llamar al display dentro del bucle
    display();
}



void reshape(int w, int h) //Función para seleccionar el tamaño de la ventana,el lugar en el que vamos a poder dibujar y el volumen de vista
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if(hazPerspectiva){
        gluPerspective(90.0f, (GLfloat)w/(GLfloat)h, 1.0f, 20.0f);
    }
    else{
        glOrtho(-20.0, 20.0, -22.0, 22.0, -21.0, 21.0); 
    }
    glMatrixMode(GL_MODELVIEW);

    ancho=w;
    alto=h;
}

void keyboardHandler(unsigned char key, int x, int y ){ //Función para controlar el brazo por teclado
    if(key == '1'){  //Pulsando la tecla 1 cambiamos el modo para pasar a mover solo el cubo del extremo
        //i = 1;
        //j = 1;
        modo = true;
    }

    if(key == '0'){ //Pulsando la tecla 0 volvemos al modo predeterminado que es mover todo el brazo
        i = 0;
        j = 0;
        modo = false;
    }

        switch(key){   //Con este switch controlamos la rotación en las distintas coordenadas de todo el brazo 
            case 's':
                girar = false;
                break;
            case 'r':
                cambio = true;
                break;   
            case 'f':
                girar = true;
                cambio = false;
                break;     
            case 'a':
                angulos[i][1]+=1;
                angulos[1][0]-=1;
                break;
            case 'q':
                angulos[i][1]-=1;
                angulos[1][0]+=1;
                break;
            case 'p':
            case 'P':
                hazPerspectiva=1;
                reshape(ancho,alto);
            break;
 
            case 'o':
            case 'O':
                hazPerspectiva=0;
                reshape(ancho,alto);
                break;
            default:
                break;
        }
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
        break;
    default:
        break;
    }
}

void menu_3(int id){
    
    switch (id)
    {
    case 0: 
        red = 0.0f;
        green = 1.0f;
        blue =  0.0f;
        break;
    case 1:
        red = 0.f;
        green = 0.0f;
        blue = 1.0f;
        break;
    case 2:
        red = 0.1f;
        green = 0.0f;   
        blue = 0.1f;
        break; 
    case 3:
        red = 0.0f;
        green = 0.5f;
        blue =  0.5f;
        break;
    default:
        break;
    }
}

void menu(){
    int submenu;
    int submenu2;

    submenu = glutCreateMenu(menu_2);
    glutAddMenuEntry("Rapido", 0);
    glutAddMenuEntry("Medio", 1);
    glutAddMenuEntry("Lento",2);
    glutAddMenuEntry("Parar",3);

    submenu2 = glutCreateMenu(menu_3);
    glutAddMenuEntry("Verde", 0);
    glutAddMenuEntry("Azul", 1);
    glutAddMenuEntry("Lila oscuro",2);
    glutAddMenuEntry("Azul-verdoso",3);

    glutCreateMenu(menu_1);
    glutAddSubMenu("Velocidades", submenu);
    glutAddSubMenu("Colores",submenu2);

    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB| GLUT_DEPTH);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(ancho, alto);
    glutCreateWindow("Examen");
    glEnable(GL_DEPTH_TEST); //Función para activar el Z-Buffer
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);
    glutKeyboardFunc(keyboardHandler);
    menu();
    glutMainLoop();
    return 0;
}