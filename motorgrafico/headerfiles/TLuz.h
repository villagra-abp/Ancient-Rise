#ifndef LUZ_H
#define LUZ_H

#include <glm/glm.hpp>

#include "TEntidad.h"

using namespace std;

class TLuz : public TEntidad{
public:
	TLuz();
	TLuz(glm::vec4 color); 																	//COnstructor para luz puntual estandar de color dado
	TLuz(glm::vec4 color, float linear, float quadratic);									//Constructor para luz puntual
	TLuz(glm::vec4 color, glm::vec3 direction);												//Constructor para luz direccional
	TLuz(glm::vec4 color, glm::vec3 direction, float cutOff, float outerCutOff);			//Constructor para luz dirigida
	TLuz(glm::vec4 color, glm::vec3 direction, float cutOff, float outerCutOff, 			//Constructor para luz dirigida
			float linear, float quadratic);			
//	TLuz(float intensidad, glm::vec4 color);
	virtual ~TLuz();

	virtual void beginDraw(TDatosEntidad *datos) override{ /*vacia*/};
	virtual void endDraw() override{/*vacia*/};
	
	virtual tEnt getTipo() override{ return luz; }
	int getType();
	glm::vec4 getColor();
	glm::vec3 getDireccion();
	float getLineal();
	float getCuadratico();
	vector<float> getPuntualParametros();
	float getCorte();
	float getCorteExterno();
	vector<float> getCortes();
//	float getIntensidad();

	virtual void setActive(bool flag);
//	void setIntensidad(float intensidad);
	void setColor(glm::vec4 color);
	void setDireccion(glm::vec3 direction);
	void setLineal(float linear);
	void setCuadratico(float cuadratico);
	void setPuntualParametros(vector<float> parametros);
	void setCorte(float cutOff);
	void setCorteExterno(float outerCutOff);
	void setCortes(vector<float> cortes);


private:	

	//TColor intensidad;
	int tipo;
	bool active;
	glm::vec4 color;
//	float intensidad;
	glm::vec3 direccion;
	float lineal, cuadratico, corte, corteExterno;


} ;


#endif //LUZ_H
