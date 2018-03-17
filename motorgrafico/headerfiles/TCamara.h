#ifndef CAMARA_H
#define CAMARA_H


#include "TEntidad.h"

class TCamara: public TEntidad{
public:
	TCamara();
	virtual ~TCamara();

	void setPerspectiva(float fovy, float aspect, float near, float far);
	void setParalela(float left, float right, float bottom, float top, float near, float far);
	
	virtual void beginDraw(glm::mat4 view, glm::mat4 projection) override;
	virtual void endDraw() override;
	virtual tEnt getTipo() override{ return camara; }
	bool getActive();
	glm::mat4 getProyectionMatrix();
	void setActive(bool flag);

private:	

	bool esPerspectiva;
	bool active;
	float cercano;
	float lejano;
	glm::mat4 mProyeccion;

} ;


#endif //CAMARA_H
