#ifndef TDATOSENTIDAD_H
#define TDATOSENTIDAD_H

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4

#include <iostream>

using namespace std;

struct TDatosEntidad{
	
	glm::mat4 view, projection;
	glm::vec3 camaraPosicion;

	vector<glm::vec4> colorPuntual;
	vector<glm::vec3> posicionPuntual;
	vector<vector<float>> atenuacionPuntual;
	
	glm::vec3 colorDir, directionDir;

	glm::vec3 positionFlash, directionFlash, colorFlash;
 	vector<float> atenuacionFlash, corteFlash;

 	bool bounding;
  	
};

#endif //TDATOSENTIDAD_H