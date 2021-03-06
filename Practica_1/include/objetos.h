//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************
#include "stdlib.h"
#include "stdio.h"
#include <ctype.h>
#include <vector>
#include <GL/glut.h>
#include "vertex.h"
#include <stdlib.h>

using namespace std;

//const float AXIS_SIZE=5000;

//*************************************************************************
// clase Punto
//*************************************************************************

class ConjuntoPuntos3D {
  public:
	ConjuntoPuntos3D(){};
  /*Esta funcion pinta los puntos
   * con el color y el grosor indicado */
	void draw_ConjuntoPuntos(float r, float g, float b, int grosor);

	vector<_vertex3f> vertices; //Guarda un vector con todos los vertices ej: [(x0,y0,z0),(x1,y1,z1),...,(xn,yn,zn)]
};


//*************************************************************************
// clase triángulo
//*************************************************************************

class ConjuntoTriangulos3D: public ConjuntoPuntos3D {
  public:
	ConjuntoTriangulos3D(){};
	void draw_aristas(float r, float g, float b, int grosor);
	void draw_solido(float r, float g, float b);
	void draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2);

	vector<_vertex3i> caras; //Guarda todas las caras ej: [(v0,v0,v0),(v1,v1,v1),...,(vn,vn,vn)]
};


//*************************************************************************
// clase Cubo
//*************************************************************************

class Cubo: public ConjuntoTriangulos3D {
  public:
	Cubo(float tam=0.5);
};


//*************************************************************************
// clase Piramide
//*************************************************************************

class Piramide: public ConjuntoTriangulos3D {
  public:
	Piramide(float tam=0.5, float al=0.75);
};

class Monigote {
public:
  Monigote();
  void Circle (GLfloat radio, GLfloat cx, GLfloat cy,GLfloat cz, GLint n, GLenum modo);
  void draw_monigote();
};
