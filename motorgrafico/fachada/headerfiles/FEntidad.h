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
	//virtual void draw() = 0;

private:
	bool visible;
	TNodo* padre;
	TNodo* nodo, rotacion, traslacion;
	float angulo;
};


#endif //FENTIDAD_H