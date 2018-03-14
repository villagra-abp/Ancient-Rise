#ifndef CAMARA_H
#define CAMARA_H


#include "TEntidad.h"

class TCamara: public TEntidad{
public:
	TCamara();
	virtual ~TCamara();

	void setPerspectiva(float fovy, float aspect, float near, float far);
	void setParalela(float left, float right, float bottom, float top, float near, float far);
	
	virtual void beginDraw() override;
	virtual void endDraw() override;
	virtual tEnt getTipo() override{ return camara; }
	glm::mat4 getProyectionMatrix();


private:	

	bool esPerspectiva;
	float cercano;
	float lejano;
	glm::mat4 mProyeccion;

} ;


#endif //CAMARA_H
