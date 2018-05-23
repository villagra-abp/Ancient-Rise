#include "../headerfiles/FLuz.h"

//ORiginal

FLuz::FLuz(): direccion(0,0,0){																//Luz puntual
	TLuz* luz = new TLuz();
	crearNodos(luz);

	isActive(true);
	type = 0;
}

FLuz::FLuz(FColor* colorin): direccion(0,0,0){												//Luz puntual
	glm::vec4 colorr = colorin->getColor();

	TLuz* luz = new TLuz(colorr);
	crearNodos(luz);

	active = true;
	isActive(true);

	color = colorin;
	type = 0;
}

FLuz::FLuz(FColor* colorin, float linear, float quadratic): direccion(0,0,0){				//Luz puntual
	glm::vec4 colorr = colorin->getColor();

	TLuz* luz = new TLuz(colorr, linear, quadratic);
	crearNodos(luz);

	active = true;
	isActive(true);

	color = colorin;
	lineal = linear;
	cuadratico = quadratic;
	type = 0;
}


FLuz::FLuz(FColor* colorin, vec3 direction): direccion(0,0,0){								//Luz direccional
	glm::vec4 colorr = colorin->getColor();
	glm::vec3 direc(direction.x, direction.y, direction.z);

	TLuz* luz = new TLuz(colorr,direc);
	crearNodos(luz);

	active = true;
	isActive(true);

	color = colorin;
	direccion = direction;
	type = 2;
}


FLuz::FLuz(FColor* colorin, vec3 direction, float cutOff, float outerCutOff): direccion(0,0,0){		//Luz dirigida
	glm::vec4 colorr = colorin->getColor();
	glm::vec3 direc(direction.x, direction.y, direction.z);

	TLuz* luz = new TLuz(colorr, direc, cutOff, outerCutOff);
	crearNodos(luz);

	active = true;
	isActive(true);

	color = colorin;
	direccion = direction;
	corte = cutOff;
	corteExterno  = outerCutOff;
	type = 1;
}


/*
FLuz::FLuz(float inten, FColor* colorin){
	padre = TMotorTAG::getInstance()->getEscena();
	//TNodo* nodo, rotacion, traslacion;

	nodo = new TNodo();
	rotacion = new TNodo();
	traslacion = new TNodo();

	padre->addHijoBack(rotacion);
	rotacion->addHijoBack(traslacion);
	traslacion->addHijoBack(nodo);

	TTransf* rot = new TTransf();
	TTransf* tras = new TTransf(); 

	glm::vec4 colorr = colorin->getColor();

	TLuz* luz = new TLuz(inten, colorr);


	rotacion->setEntidad(rot);
	traslacion->setEntidad(tras);
	nodo->setEntidad(luz);

	TMotorTAG::getInstance()->registrarLuz(nodo);

	active = true;
	isActive(true);

	color = colorin;
	intensidad = inten;
}
*/



FLuz::~FLuz(){
	traslacion->remHijoChange(nodo,padre);
	padre->remHijoAll(rotacion);
}

void FLuz::crearNodos(TLuz* luz){
	padre = TMotorTAG::getInstance()->getEscena();
	//TNodo* nodo, rotacion, traslacion;

	nodo = new TNodo();
	rotacion = new TNodo();
	traslacion = new TNodo();

	padre->addHijoBack(rotacion);
	rotacion->addHijoBack(traslacion);
	traslacion->addHijoBack(nodo);

	TTransf* rot = new TTransf();
	TTransf* tras = new TTransf();

	rotacion->setEntidad(rot);
	traslacion->setEntidad(tras);
	nodo->setEntidad(luz);

	TMotorTAG::getInstance()->registrarLuz(nodo);
}

void FLuz::Rotar(vec3 rot, float ang){
	dynamic_cast<TTransf*>(rotacion->getEntidad())->rotar(rot.x, rot.y, rot.z, ang);

}


void FLuz::Mover(vec3 pos){
	dynamic_cast<TTransf*>(traslacion->getEntidad())->trasladar(pos.x,pos.y, pos.z);

}

void FLuz::Unir(FEntidad* nPadre){
	padre->changePadre(nPadre->getTraslacion(), rotacion);
	padre = nPadre->getNodo();
}


FColor* FLuz::getColor() const{
	return color;

}

bool FLuz::getActive() {
	return active;
}


TNodo* FLuz::getNodo()  {
	return nodo;
}

TNodo* FLuz::getTraslacion(){
	return traslacion;
}

TNodo* FLuz::getRotacion(){
	return rotacion;
}

vec3 FLuz::getPosicion() {
	//vec3 posicion = nodo->getPosicion();
}

vec3 FLuz::getDireccion(){
	return direccion;
}


float FLuz::getLineal(){
	return lineal;
}


float FLuz::getCuadratico(){
	return cuadratico;
}


vector<float> FLuz::getPuntualParametros(){
	vector<float> parametros;
	parametros.push_back(lineal);
	parametros.push_back(cuadratico);

	return parametros;
}


float FLuz::getCorte(){
	return corte;
}


float FLuz::getCorteExterno(){
	return corteExterno;
}


vector<float> FLuz::getCortes(){
	vector<float> cortes;
	cortes.push_back(corte);
	cortes.push_back(corteExterno);

	return cortes;
}



/*
vec3 FLuz::getPosicion(){


}
*/

void FLuz::setPosicion(vec3 pos){
	dynamic_cast<TTransf*>(traslacion->getEntidad())->setPosition(pos.x, pos.y, pos.z);

}


void FLuz::setRotacion(vec3 rot, float ang){
	dynamic_cast<TTransf*>(rotacion->getEntidad())->setRotation(rot.x, rot.y, rot.z, ang);

}


void FLuz::isActive(bool flag){
	dynamic_cast<TLuz*>(nodo->getEntidad())->setActive(flag);
	active = flag;
}

void FLuz::setColor(FColor* colorin){
	color = colorin;
	dynamic_cast<TLuz*>(nodo->getEntidad())->setColor(colorin->getColor());

}

void FLuz::setDireccion(vec3 direction){
	direccion = direction;
}


void FLuz::setLineal(float linear){
	lineal = linear;
}


void FLuz::setCuadratico(float quadratic){
	cuadratico = quadratic;
}


void FLuz::setPuntualParametros(vector<float> parametros){
	lineal = parametros[0];
	cuadratico = parametros[1];

}


void FLuz::setCorte(float cutOff){
	corte = cutOff;
}


void FLuz::setCorteExterno(float outerCutOff){
	corteExterno = outerCutOff;
}


void FLuz::setCortes(vector<float> cortes){
	corte = cortes[0];
	corteExterno = cortes[1];
}



/*
void FLuz::setIntensity(float inte){
	intensidad = inte;

}
*/

void FLuz::setType(int tipo){
	type = tipo;

}

