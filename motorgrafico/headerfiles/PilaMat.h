#ifndef PILAMAT_H
#define PILAMAT_H

#include <iostream>
#include <vector>
#include <math.h>

#include <GL/glut.h>
#include "../inc/glm/vec3.hpp" // glm::vec3
#include "../inc/glm/vec4.hpp" // glm::vec4
#include "../inc/glm/mat4x4.hpp" // glm::mat4
#include "../inc/glm/gtc/matrix_transform.hpp" // glm::translate, glm::rotate, glm::scale, glm::perspective
#include "../inc/glm/gtc/type_ptr.hpp"
#include "../inc/glm/gtc/matrix_inverse.hpp" //glm::affineInverse
#include "../inc/glm/gtx/string_cast.hpp"

#include <stack>

using namespace std;

class PilaMat{
public:
	PilaMat();
	virtual ~PilaMat();
	void apila(glm::mat4 mat);
	glm::mat4 desapila();
	glm::mat4 consulta();


private:	
	std::stack<glm::mat4> mipila;
} ;


#endif //ENTIDAD_H