#ifndef ENTIDAD_H
#define ENTIDAD_H

#include <iostream>
#include <vector>
#include <math.h>

#include <GL/glut.h>
#include "../glm/vec3.hpp" // glm::vec3
#include "../glm/vec4.hpp" // glm::vec4
#include "../glm/mat4x4.hpp"// glm::mat4
#include "../glm/gtc/matrix_transform.hpp" // glm::translate, glm::rotate, glm::scale, glm::perspective

using namespace std;

class TEntidad{
public:
	TEntidad();
	virtual ~TEntidad();
	virtual void beginDraw()=0;
	virtual void endDraw()=0;


private:	

	

} ;


#endif //ENTIDAD_H
