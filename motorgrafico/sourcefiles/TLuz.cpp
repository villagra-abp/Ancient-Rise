#include "../headerfiles/TLuz.h"

//Clase para la gestion de los datos de los distintos tipos de luces. Original.

TLuz::TLuz(){
	//intensidad = 1;
	color = glm::vec4(1,1,1,1);
	tipo = 0;
}

TLuz::TLuz(glm::vec4 colo){
	color = colo;
	tipo = 0;
	lineal = 0.0045;
	cuadratico = 0.00075;
}

TLuz::TLuz(glm::vec4 colo, float linear, float quadratic){
	color = colo;

	lineal = linear;
	cuadratico = quadratic;
	tipo = 0;
}


TLuz::TLuz(glm::vec4 colo, glm::vec3 direction){
	color = colo;
	direccion = direction;
	tipo = 2;
}


TLuz::TLuz(glm::vec4 colo, glm::vec3 direction, float cutOff, float outerCutOff){
	color = colo;
	direccion = direction;
	lineal = 0.0045;
	cuadratico = 0.00075;
	corte = cutOff;
	corteExterno = outerCutOff;
	tipo = 1;
}

TLuz::TLuz(glm::vec4 colo, glm::vec3 direction, float cutOff, float outerCutOff, float linear, float quadratic){
	color = colo;
	direccion = direction;
	lineal = linear;
	cuadratico = quadratic;
	corte = cutOff;
	corteExterno = outerCutOff;
	tipo = 1;
}

/*
TLuz::TLuz(float inten, glm::vec4 colo){
	intensidad = inten;
	color = colo;
}
*/

TLuz::~TLuz(){

}

int TLuz::getType(){
	return tipo;
}

glm::vec4 TLuz::getColor(){
	return color;
}


glm::vec3 TLuz::getDireccion(){
	return direccion;
}


float TLuz::getLineal(){
	return lineal;
}


float TLuz::getCuadratico(){
	return cuadratico;
}


//Devuelve los parametros de luz puntual en forma de vector
vector<float> TLuz::getPuntualParametros(){
	vector<float> parametros;
	parametros.push_back(lineal);
	parametros.push_back(cuadratico);

	return parametros;
}


float TLuz::getCorte(){
	return corte;
}


float TLuz::getCorteExterno(){
	return corteExterno;
}

//Devuelve los parametros de corte en forma de vector
vector<float> TLuz::getCortes(){
	vector<float> cortes;
	cortes.push_back(corte);
	cortes.push_back(corteExterno);

	return cortes;
}



/*
float TLuz::getIntensidad(){
	return intensidad;
}
*/

void TLuz::setActive(bool flag){
	active = flag;
}


/*
void TLuz::setIntensidad(float inten){
	intensidad = inten;
}	
*/

void TLuz::setColor(glm::vec4 colo){
	color = colo;
}


void TLuz::setDireccion(glm::vec3 direction){
	direccion = direction;
}


void TLuz::setLineal(float linear){
	lineal = linear;
}


void TLuz::setCuadratico(float quadratic){
	cuadratico = quadratic;
}


void TLuz::setPuntualParametros(vector<float> parametros){
	lineal = parametros[0];
	cuadratico = parametros[1];
}


void TLuz::setCorte(float cutOff){
	corte = cutOff;
}


void TLuz::setCorteExterno(float outerCutOff){
	corteExterno = outerCutOff;
}


void TLuz::setCortes(vector<float> cortes){
	corte = cortes[0];
	corteExterno = cortes[1];
}

