#ifndef FLUZ_H	
#define FLUZ_H

#include "vec3.h"
#include "FColor.h"

class FLuz : FEntidad {
public:
	FLuz();
	virtual ~FLuz();

	void Rotar(vec3 pos, float ang) override;
	void Mover(vec3 rot) override;

	void setPosicion(vec3 pos) override;
	void setRotacion(vec3 rot, float ang) override;

	void setIntensity(float inte);
	void setType(int tipo);

private:

	bool active;
	TNodo* padre;
	TNodo* nodo, rotacion, traslacion;
	int type;
	float intensidad;
};

#endif //FLUZ_H

