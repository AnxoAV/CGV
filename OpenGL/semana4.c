
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

void brazos(float translatex,float translatey,float translatez){
    glLoadIdentity();  //Cargamos la matriz identidad para aplicar las transformaciones

    glTranslatef(translatex,translatey,translatez);

    if(modo == false){
        glutWireSphere(0.5f, 8, 8);
    }
    else{
        glutSolidSphere(0.5f, 8, 8);
    }

    glRotatef(angulos[0][0], 1.0f, 0.0f, 0.0f);
    glRotatef(angulos[0][1], 0.0f, 1.0f, 0.0f);
    glRotatef(angulos[0][2], 0.0f, 0.0f, 1.0f);

    glPushMatrix();

    glTranslatef(0.0, -1.5, 0.0f);
    glScalef(1.0f,2.0f,1.0f);

    if(modo == false){
        glutWireCube(1.0f);
    }else{
        glutSolidCube(1.0f);
    }

    glLoadIdentity();

    glPopMatrix();

    glTranslatef(0.0f,-3.0f,0.0f);

    if(modo == false){
        glutWireSphere(0.5f,8,8);
    }else{
        glutSolidSphere(0.5f,8,8);
    }

    glRotatef(angulos[1][0], 1.0f, 0.0f, 0.0f);
    glRotatef(angulos[1][1], 0.0f, 1.0f, 0.0f);
    glRotatef(angulos[1][2], 0.0f, 0.0f, 1.0f);

    glPushMatrix();

    glTranslatef(0.0f,-1.5f,0.0f);
    glScalef(1.0f,2.0f,1.0f);

    if(modo == false){
        glutWireCube(1.0f);
    }else{
        glutSolidCube(1.0f);
    }

    glLoadIdentity();

    glPopMatrix();

    glTranslatef(0.0f,-3.0f,0.0f);
    if(modo == false){
        glutWireSphere(0.4,8,8);
    }else{
        glutSolidSphere(0.4,8,8);
    }


}

void piernas(float translatex,float translatey,float translatez){
     glLoadIdentity();  //Cargamos la matriz identidad para aplicar las transformaciones

    glTranslatef(translatex,translatey,translatez);

    if(modo == false){
        glutWireSphere(0.5f,8,8);
    }else{
        glutSolidSphere(0.5f,8,8);
    }

    glRotatef(angulosp[0][0], 1.0f, 0.0f, 0.0f);
    glRotatef(angulosp[0][1], 0.0f, 1.0f, 0.0f);
    glRotatef(angulosp[0][2], 0.0f, 0.0f, 1.0f);

    glPushMatrix();

    glTranslatef(0.0, -1.5, 0.0f);
    glScalef(1.0f,2.0f,1.0f);

    if(modo == false){
        glutWireCube(1.0f);
    }else{
        glutSolidCube(1.0f);
    }

    glLoadIdentity();

    glPopMatrix();

    glTranslatef(0.0f,-3.0f,0.0f);

    if(modo == false){
        glutWireSphere(0.5f,8,8);
    }else{
        glutSolidSphere(0.5f,8,8);
    }

    glRotatef(angulosp[1][0], 1.0f, 0.0f, 0.0f);
    glRotatef(angulosp[1][1], 0.0f, 1.0f, 0.0f);
    glRotatef(angulosp[1][2], 0.0f, 0.0f, 1.0f);

    glPushMatrix();

    glTranslatef(0.0f,-1.5f,0.0f);
    glScalef(1.0f,2.0f,1.0f);

    if(modo == false){
        glutWireCube(1.0f);
    }else{
        glutSolidCube(1.0f);
    }

    glLoadIdentity();

    glPopMatrix();

    glTranslatef(0.0f,-3.0f,0.0f);
    
    if(modo == false){
        glutWireCube(0.7f);
    }else{
        glutSolidCube(0.7f);
    }

}

void cabezaycuerpo(){
    glLoadIdentity();

    glTranslatef(-1.0f,2.0f,0.0f);
    
    if(modo == false){
        glutWireSphere(1.0f,8,8);
    }else{
        glutSolidSphere(1.0f,8,8);
    }

    glTranslatef(0.0f,-1.0f,0.0f);

    if(modo == false){
        glutWireCube(1.0f);
    }else{
        glutSolidCube(1.0f);
    }

    glLoadIdentity();
    glScalef(3.0,8.0,2.0f);
    glTranslatef(-0.35f,-0.4f,0.0f);
    
    if(modo == false){
        glutWireCube(1.0f);
    }else{
        glutSolidCube(1.0f);
    }
}


void display(){ 

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Borramos todo el frame buffer para el posterior pintado 
    brazos(0.5f,0.5f,0.0f);
    brazos(-2.5f,0.5f,0.0f);
    cabezaycuerpo();
    piernas(0.0f,-7.0f,0.0f);
    piernas(-2.1f,-7.0f,0.0f);
    glutSwapBuffers();
}

void timerRotation(int value){
    angulosp[0][1]+= value;
    angulosp[0][1] = ((int)angulosp[0][1])%360;
    glutTimerFunc(velocidad,timerRotation,5);
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
    glOrtho(-10.0, 10.0, -14.0, 14.0, -14.0, 14.0); 
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
    glutIdleFunc(idle);
    glutKeyboardFunc(keyboardHandler);
    menu();
    glutMainLoop();
    return 0;
}