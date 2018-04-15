#ifndef FLUZ_H	
#define FLUZ_H

#include "vec3.h"
#include "FColor.h"
#include "FEntidad.h"

class FLuz : public FEntidad {
public:
	FLuz();
	FLuz(FColor* colorin);																//COnstructor para luz puntual estandar de color dado
	FLuz(FColor* colorin, float linear, float quadratic);								//Constructor para luz puntual
	FLuz(FColor* colorin, vec3 direction);												//Constructor para luz direccional
	FLuz(FColor* colorin, vec3 direction, float cutOff, float outerCutOff);				//Constructor para luz dirigida
//	FLuz(float intensidad, FColor* colorin);
	virtual ~FLuz();

	void crearNodos(TLuz* luz);

	void Rotar(vec3 rot, float ang)  override;
	void Mover(vec3 pos) override;

	void Unir(FEntidad* padre) override;

	
//	vec3 getPosicion();
	bool getActive()  override;
	TNodo* getNodo()  override;
	TNodo* getTraslacion() override;
	TNodo* getRotacion() override;
	vec3 getPosicion() override;

	//Getters de parametros
	FColor* getColor() const;
	vec3 getDireccion();
	float getLineal();
	float getCuadratico();
	vector<float> getPuntualParametros();
	float getCorte();
	float getCorteExterno();
	vector<float> getCortes();

	void setPosicion(vec3 pos) override;
	void setRotacion(vec3 rot, float ang) override;

	void isActive(bool flag);
	void setColor(FColor* colorin);
	void setDireccion(vec3 direction);
	void setLineal(float linear);
	void setCuadratico(float cuadratico);
	void setPuntualParametros(vector<float> parametros);
	void setCorte(float cutOff);
	void setCorteExterno(float outerCutOff);
	void setCortes(vector<float> cortes);

//	void setIntensity(float inte);
	void setType(int tipo);  //0-> Puntual, 1->Dirigida 2->Direccional

private:

	bool active;
	TNodo *padre;
	TNodo *nodo, *rotacion, *traslacion;
	int type;				//0-> Puntual, 1->Dirigida, 2-> Direccional
//	float intensidad;
	FColor* color;
	vec3 direccion;
	float corte, corteExterno, lineal, cuadratico;
};

#endif //FLUZ_H

