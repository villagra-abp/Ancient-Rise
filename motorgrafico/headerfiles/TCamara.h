#ifndef CAMARA_H
#define CAMARA_H

<<<<<<< HEAD
#include <iostream>
#include <vector>
#include <math.h>
#include "../headerfiles/TEntidad.h"

using namespace std;
=======
#include "TEntidad.h"
>>>>>>> 89a4e0e937ec5c5d2e6bf07d446473ff8dc14279

class TCamara: public TEntidad{
public:
	TCamara();
	virtual ~TCamara();
<<<<<<< HEAD
	void setPerspectiva();
	void setParalela();
	virtual void beginDraw() override;
	virtual void endDraw() override;

=======
	void setPerspectiva(float fovy, float aspect, float near, float far);
	void setParalela(float left, float right, float bottom, float top, float near, float far);
	
	virtual void beginDraw() override;
	virtual void endDraw() override;
	virtual tEnt getTipo() override{ return camara; }
	glm::mat4 getProyectionMatrix();
>>>>>>> 89a4e0e937ec5c5d2e6bf07d446473ff8dc14279


private:	

	bool esPerspectiva;
	float cercano;
	float lejano;
<<<<<<< HEAD
=======
	glm::mat4 mProyeccion;
>>>>>>> 89a4e0e937ec5c5d2e6bf07d446473ff8dc14279

} ;


#endif //CAMARA_H
