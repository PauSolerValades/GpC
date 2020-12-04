#include <stdio.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "display.h"
#include "io.h"
#include "definitions.h"

/** GLOBAL VARIABLES **/

GLdouble _window_ratio;                     /*Control of window's proportions */
GLdouble _ortho_x_min,_ortho_x_max;         /*Variables for the control of the orthographic projection*/
GLdouble _ortho_y_min ,_ortho_y_max;        /*Variables for the control of the orthographic projection*/
GLdouble _ortho_z_min,_ortho_z_max;         /*Variables for the control of the orthographic projection*/

object3d * _first_object= 0;                /*List of objects*/
object3d * _selected_object = 0;            /*Object currently selected*/

camera * _first_camera = 0;
camera * _selected_camera = 0;

elem_matrix * _actual_matrix = 0;

int mode; //0: objeto, 1: camara, 2: luces cuando toque.
int transformacion;
int referencia;

int camara_interna;

/** GENERAL INITIALIZATION **/
void initialization (){

    mode = 0; //por defecto a objeto.
    transformacion = 0; //translación por defecto
    referencia = 0; //por defecto a objeto.
    camara_interna = 0;

    /*Initialization of all the variables with the default values*/
    //definimos puntos maximos y minimos de lo que vamos a poder visualizar.
    //zona tridimensional donde se van a tener que ver en pantalla.
    

    _window_ratio = (GLdouble) KG_WINDOW_WIDTH / (GLdouble) KG_WINDOW_HEIGHT;

    /*Definition of the background color*/
    glClearColor(KG_COL_BACK_R, KG_COL_BACK_G, KG_COL_BACK_B, KG_COL_BACK_A);

    /*Definition of the method to draw the objects*/
    //dibujamos plígonos mediante líneas, nada de rellenarlos.
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}


/** MAIN FUNCTION **/
int main(int argc, char** argv) {

    /*First of all, print the help information*/
    print_help();

    /* glut initializations */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB|GLUT_DEPTH|GLUT_DOUBLE); //evita la superposición de polígonos.
    glutInitWindowSize(KG_WINDOW_WIDTH, KG_WINDOW_HEIGHT);
    glutInitWindowPosition(KG_WINDOW_X, KG_WINDOW_Y);
    glutCreateWindow(KG_WINDOW_TITLE);

    /* Activamos los polígonos. */
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //esto ahora no va a hacer lineas, va a rellenar el polígono. Això ho controlarem després a display
    glEnable(GL_DEPTH_TEST|GL_LIGHTING);

    if (flat_smooth) glShadeModel(GL_SMOOTH);
    else flShadeModel(GL_FLAT);

    /* set the callback functions */
    glutDisplayFunc(display); //donde se hace "la foto". el observador que ve
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard); //evento de llamada por teclado.
    glutSpecialFunc(special); //gestor teclas especiales

    /* z-buffer: dibujas sólo los puntos más cercanos al observador. Tenemos que
     dibujar sólo lo que se ve, nada de lo que no se ve. En plan, si un cubo te 
     tapa la una casa que hay detrás, solo dibujas el cubo y punto. 
     
     guardamos la información en un buffer. De una imagen 1000x1000, el buffer 
     tendrá 1000x1000 elementos, con 4 valores por elemento.

      Tendremos que inicializar el buffer a la profundidad máxima. No tenemos que 
      sólo borrar todo el dibujo, sinó que tenemos que reeinicializar el buffer de
      profundidad.  
    */

    /* this initialization has to be AFTER the creation of the window */
    initialization();

    /* start the main loop */
    glutMainLoop();
    return 0;
}
