#ifndef FCAMARA_H
#define FCAMARA_H

#include "FEntidad.h"
#include "vec3.h"

class FCamara : public FEntidad{

public:

	FCamara();
	virtual ~FCamara();

	void Rotar(vec3 rot, float ang) override;
	void Mover(vec3 pos) override;

	void Activar();

	void setPosicion(vec3 pos) override;
	void setRotacion(vec3 rot, float ang) override;

	

	void Unir(FEntidad* nPadre) override;

	bool getActive() override;
	TNodo* getNodo() override;
	TNodo* getTraslacion() override;
	TNodo* getRotacion() override;
	vec3 getPosicion();

private:

	bool active;
	TNodo *padre;
	TNodo *nodo, *rotacion, *traslacion;

	void isActive(bool flag) override;

};



#endif