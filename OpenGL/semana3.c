
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
GLboolean modo = false; //Variable de control para seleccionar la parte del brazo de manera predeterminada se moverá todo el brazo, 
                            //Si se pulsa el 1 se pasará a mover solo el "cubo" del extremo y si se pulsa el 0 se volverá al modo predeterminado

void init()
{
    glClearColor(0.0f,0.0f,0.0f,0.0f);  //Elegimos el color del fondo
}

void display(){ 

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Borramos todo el frame buffer para el posterior pintado 

    glLoadIdentity();  //Cargamos la matriz identidad para aplicar las transformaciones

    glTranslatef(0.0f, 0.0f, -5.0f);
    glutWireSphere(0.5f, 8, 8);

    glLoadIdentity();  //Volvemos a cargar la matriz identidad para que las anteriores transformaciones no se apliquen

    glRotatef(angulos[0][0], 1.0f, 0.0f, 0.0f);
    glRotatef(angulos[0][1], 0.0f, 1.0f, 0.0f);
    glRotatef(angulos[0][2], 0.0f, 0.0f, 1.0f);

    glTranslatef(0.0, -1.0, 0.0f);

    glutWireCube(1.0f);

    glTranslatef(0.0f,-1.0f,0.0f);
    glutWireSphere(0.5f,8,8);

    glRotatef(angulos[1][0], 1.0f, 0.0f, 0.0f);
    glRotatef(angulos[1][1], 0.0f, 1.0f, 0.0f);
    glRotatef(angulos[1][2], 0.0f, 0.0f, 1.0f);

    glTranslatef(0.0f,-1.0f,0.0f);
    glutWireCube(1.0f);

    glutSwapBuffers();
 
}

void idle(){ //Función para llamar al display dentro del bucle
    display();
}

void keyboardHandler(unsigned char key, int x, int y ){ //Función para controlar el brazo por teclado

    if(key == '1'){  //Pulsando la tecla 1 cambiamos el modo para pasar a mover solo el cubo del extremo
        modo = true;
    }

    if(key == '0'){ //Pulsando la tecla 0 volvemos al modo predeterminado que es mover todo el brazo
        modo = false;
    }

    if(modo==false){
        switch(key){   //Con este switch controlamos la rotación en las distintas coordenadas de todo el brazo
            case 'q':
                angulos[0][0]+=1;
                break;
            case 'a':
                angulos[0][0]-=1;
                break;
            case 'w':
                angulos[0][1]+=1;
                break;
            case 's':
                angulos[0][1]-=1;
                break;
            case 'e':
                angulos[0][2]+=1;
                break;
            case 'd':
                angulos[0][2]-=1;
                break;
            default:
                break;
        }
    }

    if(modo == true){
        switch(key){    //Con este switch controlamos la rotación para cada coordenada exclusivamente de la mano
            case 'q':
                angulos[1][0]+=1;
                break;
            case 'a':
                angulos[1][0]-=1;
                break;
            case 'w':
                angulos[1][1]+=1;
                break;
            case 's':
                angulos[1][1]-=1;
                break;
            case 'e':
                angulos[1][2]+=1;
                break;
            case 'd':
                angulos[1][2]-=1;
                break;
            default:
                break;
        }
    }
}

void reshape(int w, int h) //Función para seleccionar el tamaño de la ventana,el lugar en el que vamos a poder dibujar y el volumen de vista
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-8.0, 8.0, -8.0, 8.0, -8.0, 8.0); 
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
    glutMainLoop();
    return 0;
}
