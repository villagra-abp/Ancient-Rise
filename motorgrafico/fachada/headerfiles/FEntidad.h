#ifndef FENTIDAD_H
#define FENTIDAD_H

#include "TMotorTAG.h"
#include "vec3.h"

class FEntidad{
public:

	virtual ~FEntidad() = default;
	virtual void Rotar(vec3 rot, float ang) = 0;
	virtual void Mover(vec3 pos) = 0;

	virtual void setPosicion(vec3 pos) = 0;
	virtual void setRotacion(vec3 rot, float ang) = 0;

	virtual void isActive(bool flag) = 0;
	virtual void Unir(FEntidad* padre) = 0;
	//virtual void draw() = 0;

	virtual bool getActive() = 0;

	virtual TNodo* getNodo() = 0;

private:
	bool active;
	TNodo* padre;
	TNodo* nodo, rotacion, traslacion;
};


#endif //FENTIDAD_H