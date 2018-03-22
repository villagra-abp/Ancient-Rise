#ifndef FLUZ_H	
#define FLUZ_H

#include "vec3.h"
#include "FColor.h"
#include "FEntidad.h"

class FLuz : public FEntidad {
public:
	FLuz();
	FLuz(FColor* colorin);
	FLuz(float intensidad, FColor* colorin);
	virtual ~FLuz();

	void Rotar(vec3 rot, float ang)  override;
	void Mover(vec3 pos) override;

	void Unir(FEntidad* padre) override;

	FColor* getColor() const;
//	vec3 getPosicion();
	bool getActive()  override;
	TNodo* getNodo()  override;
	TNodo* getTraslacion() override;
	TNodo* getRotacion() override;
	vec3 getPosicion() override;

	void setPosicion(vec3 pos) override;
	void setRotacion(vec3 rot, float ang) override;

	void isActive(bool flag);
	void setColor(FColor* colorin);
	void setIntensity(float inte);
	void setType(int tipo);  //0-> Puntual, 1->Dirigida

private:

	bool active;
	TNodo *padre;
	TNodo *nodo, *rotacion, *traslacion;
	int type;				//0-> Puntual, 1->Dirigida
	float intensidad;
	FColor* color;
};

#endif //FLUZ_H

