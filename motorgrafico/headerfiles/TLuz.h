#ifndef LUZ_H
#define LUZ_H

#include <glm/glm.hpp>

#include "TEntidad.h"

using namespace std;

class TLuz : public TEntidad{
public:
	TLuz();
	TLuz(glm::vec4 color);
	TLuz(float intensidad, glm::vec4 color);
	virtual ~TLuz();

	virtual void beginDraw(glm::mat4 view, glm::mat4 projection, vector<float> intensidad, vector<glm::vec4> color, vector<glm::vec3> luzPosicion,
			 glm::vec3 camaraPosicion) override{ /*vacia*/};
	virtual void endDraw() override{/*vacia*/};
	
	virtual tEnt getTipo() override{ return luz; }
	glm::vec4 getColor();
	float getIntensidad();

	virtual void setActive(bool flag);
	void setIntensidad(float intensidad);
	void setColor(glm::vec4 color);


private:	

	//TColor intensidad;
	bool active;
	glm::vec4 color;
	float intensidad;

} ;


#endif //LUZ_H
