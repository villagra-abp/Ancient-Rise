#ifndef ENTIDAD_H
#define ENTIDAD_H


#include <iostream>
#include <vector>
#include <math.h>

//#include <GL/glut.h>

/*
#include "../glm/vec3.hpp"// glm::vec3
#include "../glm/vec4.hpp" // glm::vec4
#include "../glm/mat4x4.hpp" // glm::mat4
#include "../glm/gtc/matrix_transform.hpp" // glm::translate, glm::rotate, glm::scale, glm::perspective
#include "../glm/gtc/type_ptr.hpp"
#include "../glm/gtc/matrix_inverse.hpp" //glm::affineInverse
#include "../glm/gtx/string_cast.hpp"
*/

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_inverse.hpp> //glm::affineInverse
#include <glm/gtx/string_cast.hpp>


#include "PilaMat.h"


using namespace std;


class TEntidad{
public:
	enum tEnt { transf, malla, luz, camara };

	TEntidad();
	virtual ~TEntidad();
	virtual void beginDraw()=0;
	virtual void endDraw()=0;
	virtual string getTipo()=0;


protected:
	static PilaMat* pila; 		// Pila de matrices OpenGL
	static glm::mat4 mmodelo;	// Matriz Modelo (Mallas), Matriz Camara (Camara), Matriz Luz (Luz)
} ;


#endif //ENTIDAD_H
