#ifndef ENTIDAD_H
#define ENTIDAD_H

#include "PilaMat.h"

class TEntidad{
public:
	TEntidad();
	virtual ~TEntidad();
	virtual void beginDraw()=0;
	virtual void endDraw()=0;


protected:
	static PilaMat* pila; 		// Pila de matrices OpenGL
	static glm::mat4 mmodelo;	// Matriz Modelo (Mallas), Matriz Camara (Camara), Matriz Luz (Luz)
} ;


#endif //ENTIDAD_H
