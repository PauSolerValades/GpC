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

elem_matrix * _actual_matrix = 0;

int mode;
int referencia;

/** GENERAL INITIALIZATION **/
void initialization (){

    mode = -1; //ninguna por defecro.
    referencia = 0; //por defecto a objeto.

    /*Initialization of all the variables with the default values*/
    //definimos puntos maximos y minimos de lo que vamos a poder visualizar.
    //zona tridimensional donde se van a tener que ver en pantalla.
    _ortho_x_min = KG_ORTHO_X_MIN_INIT;
    _ortho_x_max = KG_ORTHO_X_MAX_INIT;
    _ortho_y_min = KG_ORTHO_Y_MIN_INIT;
    _ortho_y_max = KG_ORTHO_Y_MAX_INIT;
    _ortho_z_min = KG_ORTHO_Z_MIN_INIT;
    _ortho_z_max = KG_ORTHO_Z_MAX_INIT;

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
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(KG_WINDOW_WIDTH, KG_WINDOW_HEIGHT);
    glutInitWindowPosition(KG_WINDOW_X, KG_WINDOW_Y);
    glutCreateWindow(KG_WINDOW_TITLE);

    /* set the callback functions */
    glutDisplayFunc(display); //donde se hace "la foto". el observador que ve
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard); //evento de llamada por teclado.
    glutSpecialFunc(special); //gestor teclas especiales

    /* this initialization has to be AFTER the creation of the window */
    initialization();

    /* start the main loop */
    glutMainLoop();
    return 0;
}
