#include "stdlib.h"
#include "stdio.h"
#include <GL/glut.h>
#include <ctype.h>
#include <math.h>
#include "objetos.h"
#include "vertex.h"

//Variables para el cambio de objeto y visualizacion;
char modo;
char tipo;
//Las figuras son objetod globales para que no se
//tengan que construir continuamente
Cubo cubo(3);
Piramide piramide(3,4);
ObjetoPLY objply;
Revolucion revolucion;

// tamaño de los ejes
const int AXIS_SIZE=5000;

// variables que definen la posicion de la camara en coordenadas polares
GLfloat Observer_distance;
GLfloat Observer_angle_x;
GLfloat Observer_angle_y;

// variables que controlan la ventana y la transformacion de perspectiva
GLfloat Window_width,Window_height,Front_plane,Back_plane;

// variables que determninan la posicion y tamaño de la ventana X
int UI_window_pos_x=50,UI_window_pos_y=50,UI_window_width=500,UI_window_height=500;

//**************************************************************************
//
//***************************************************************************

void clear_window(){
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}

//**************************************************************************
// Funcion para definir la transformación de proyeccion
//***************************************************************************

void change_projection(){

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  // formato(x_minimo,x_maximo, y_minimo, y_maximo,Front_plane, plano_traser)
  //  Front_plane>0  Back_plane>PlanoDelantero)
  glFrustum(-Window_width,Window_width,-Window_height,Window_height,Front_plane,Back_plane);
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void change_observer(){
  // posicion del observador
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(0,0,-Observer_distance);
  glRotatef(Observer_angle_x,1,0,0);
  glRotatef(Observer_angle_y,0,1,0);
}

//**************************************************************************
// Funcion que dibuja los ejes utilizando la primitiva grafica de lineas
//***************************************************************************

void draw_axis(){
  glBegin(GL_LINES);
  // eje X, color rojo
  glColor3f(1,0,0);
  glVertex3f(-AXIS_SIZE,0,0);
  glVertex3f(AXIS_SIZE,0,0);
  // eje Y, color verde
  glColor3f(0,1,0);
  glVertex3f(0,-AXIS_SIZE,0);
  glVertex3f(0,AXIS_SIZE,0);
  // eje Z, color azul
  glColor3f(0,0,1);
  glVertex3f(0,0,-AXIS_SIZE);
  glVertex3f(0,0,AXIS_SIZE);
  glEnd();
}

//**************************************************************************
// Funcion que dibuja los objetos
//***************************************************************************

void draw_objects(){
//TODO: Añadir menu para cambiar entre visualizaciones
modo = toupper(modo);
tipo = toupper(tipo);

if(tipo == 'C'){
  switch (modo) {
    case  '1':
      cubo.draw_solido_ajedrez(0,0,1,1,0,0);
      break;
    case '2':
      cubo.draw_solido(0,1,0);
      break;
    case '3':
      cubo.draw_aristas(1,0,0,1);
      break;
    case '4':
      cubo.draw_ConjuntoPuntos(1,0,0,2);
      break;
    default:
      cubo.draw_solido_ajedrez(0,0,1,1,0,0);
  }
} else if(tipo == 'P') {
  switch (modo) {
    case  '1':
      piramide.draw_solido_ajedrez(0,0,1,1,0,0);
      break;
    case '2':
      piramide.draw_solido(0,1,0);
      break;
    case '3':
      piramide.draw_aristas(1,0,0,1);
      break;
    case '4':
      piramide.draw_ConjuntoPuntos(1,0,0,2);
      break;
    default:
      piramide.draw_solido_ajedrez(0,0,1,1,0,0);
    }
} else if(tipo == 'O') {
  switch (modo) {
    case  '1':
      objply.draw_solido_ajedrez(0,0,1,1,0,0);
      break;
    case '2':
      objply.draw_solido(0,1,0);
      break;
    case '3':
      objply.draw_aristas(1,0,0,1);
      break;
    case '4':
      objply.draw_ConjuntoPuntos(1,0,0,2);
      break;
    default:
      objply.draw_solido_ajedrez(0,0,1,1,0,0);
    }
} else if(tipo == 'R') {
  switch (modo) {
    case  '1':
      revolucion.draw_solido_ajedrez(0,0,1,1,0,0);
      break;
    case '2':
      revolucion.draw_solido(0,1,0);
      break;
    case '3':
      revolucion.draw_aristas(1,0,0,1);
      break;
    case '4':
      revolucion.draw_ConjuntoPuntos(1,0,0,2);
      break;
    default:
      revolucion.draw_solido_ajedrez(0,0,1,1,0,0);
    }
}
glutPostRedisplay();
}

//**************************************************************************
//
//***************************************************************************

void draw_scene(void){
  clear_window();
  change_observer();
  draw_axis();
  draw_objects();
  glutSwapBuffers();
}

//***************************************************************************
// Funcion llamada cuando se produce un cambio en el tamaño de la ventana
//
// el evento manda a la funcion:
// nuevo ancho
// nuevo alto
//***************************************************************************

void change_window_size(int Ancho1,int Alto1){
  change_projection();
  glViewport(0,0,Ancho1,Alto1);
  glutPostRedisplay();
}

//***************************************************************************
// Funcion llamada cuando se produce aprieta una tecla normal
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton
//***************************************************************************

void normal_keys(unsigned char Tecla1,int x,int y){
  Tecla1 = toupper(Tecla1);

  if (Tecla1=='Q') exit(0);
  else{
    if(Tecla1 == 'P' || Tecla1 == 'C' || Tecla1 == 'O' || Tecla1 == 'R')
      tipo =Tecla1;
    else
      modo = Tecla1;
  }
}

//***************************************************************************
// Funcion llamada cuando se produce aprieta una tecla especial
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton

//***************************************************************************

void special_keys(int Tecla1,int x,int y){
  switch (Tecla1){
    case GLUT_KEY_LEFT:Observer_angle_y--;break;
    case GLUT_KEY_RIGHT:Observer_angle_y++;break;
    case GLUT_KEY_UP:Observer_angle_x--;break;
    case GLUT_KEY_DOWN:Observer_angle_x++;break;
    case GLUT_KEY_PAGE_UP:Observer_distance*=1.2;break;
    case GLUT_KEY_PAGE_DOWN:Observer_distance/=1.2;break;
  }
  glutPostRedisplay();
}

//***************************************************************************
// Funcion de incializacion
//***************************************************************************

void initialize(void){
  // se inicalizan la ventana y los planos de corte
  Window_width=5;
  Window_height=5;
  Front_plane=10;
  Back_plane=1000;

  // se inicia la posicion del observador, en el eje z
  Observer_distance=2*Front_plane;
  Observer_angle_x=0;
  Observer_angle_y=0;

  // se indica cual sera el color para limpiar la ventana  (r,v,a,al)
  // blanco=(1,1,1,1) rojo=(1,0,0,1), ...
  glClearColor(1,1,1,1);

  // se habilita el z-bufer
  glEnable(GL_DEPTH_TEST);
  //
  change_projection();
  //
  glViewport(0,0,UI_window_width,UI_window_height);
}


//***************************************************************************
// Programa principal
//
// Se encarga de iniciar la ventana, asignar las funciones e comenzar el
// bucle de eventos
//***************************************************************************

int main(int argc, char **argv){

  if (argc != 3){
      cerr << "ERROR: número de arguementos incorrecto" << endl;
      cerr << "Uso: ./practica2 data/objeto.ply tapas( 0 o 1 )" << endl;

      return (-1);
  }

  //Si se le pasa un 1 se ponen tapas
   bool con_tapas = (atoi(argv[2]) == 1);

  objply.crearObjetoPly(argv[1]);
  revolucion.crearObjetoRev(argv[1], 50,con_tapas);

  if(con_tapas)
    cout << "Se va a pintar CON tapas" << endl;
  else
    cout << "Se va a pintar SIN tapas" << endl;
  cout << "\n----------Objeto PLY -------------" << endl;
  cout << "Leidas " << objply.getNumCaras() << " caras." << endl;
  cout << "Formadas por " << objply.getNumVertices() << " vertices." << endl;

  cout << "--------Objeto Revolución-----------" << endl;
  cout << revolucion.getNumCaras() << " caras." << endl;
  cout << "Formadas por " << revolucion.getNumVertices() << " vertices." << endl;
  cout << "------------------------------------" << endl;
  cout << endl;

  cout << "\t\t****** TECLAS *******" << endl;
  cout << "\t\t**  P = Pirámide   **" << endl;
  cout << "\t\t**  C = Cubo       **" << endl;
  cout << "\t\t**  O = Objeto PLY **" << endl;
  cout << "\t\t**  R = Revolución **" << endl;
  cout << "\t\t**-----------------**" << endl;
  cout << "\t\t**  1 = Ajedrez    **" << endl;
  cout << "\t\t**  2 = Sólido    **" << endl;
  cout << "\t\t**  3 = Aristas     **" << endl;
  cout << "\t\t**  4 = Puntos     **" << endl;
  cout << "\t\t*********************" << endl;
  // se llama a la inicialización de glut
  glutInit(&argc, argv);

  // se indica las caracteristicas que se desean para la visualización con OpenGL
  // Las posibilidades son:
  // GLUT_SIMPLE -> memoria de imagen simple
  // GLUT_DOUBLE -> memoria de imagen doble
  // GLUT_INDEX -> memoria de imagen con color indizado
  // GLUT_RGB -> memoria de imagen con componentes rojo, verde y azul para cada pixel
  // GLUT_RGBA -> memoria de imagen con componentes rojo, verde, azul y alfa para cada pixel
  // GLUT_DEPTH -> memoria de profundidad o z-bufer
  // GLUT_STENCIL -> memoria de estarcido
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

  // posicion de la esquina inferior izquierdad de la ventana
  glutInitWindowPosition(UI_window_pos_x,UI_window_pos_y);

  // tamaño de la ventana (ancho y alto)
  glutInitWindowSize(UI_window_width,UI_window_height);

  // llamada para crear la ventana, indicando el titulo (no se visualiza hasta que se llama
  // al bucle de eventos)
  glutCreateWindow("Practica 2");

  // asignación de la funcion llamada "dibujar" al evento de dibujo
  glutDisplayFunc(draw_scene);
  // asignación de la funcion llamada "cambiar_tamanio_ventana" al evento correspondiente
  glutReshapeFunc(change_window_size);
  // asignación de la funcion llamada "tecla_normal" al evento correspondiente
  glutKeyboardFunc(normal_keys);
  // asignación de la funcion llamada "tecla_Especial" al evento correspondiente
  glutSpecialFunc(special_keys);

  // funcion de inicialización
  initialize();

  // inicio del bucle de eventos
  glutMainLoop();
  return 0;
}
