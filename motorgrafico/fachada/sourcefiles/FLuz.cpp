#include "../headerfiles/FLuz.h"



FLuz::FLuz(){
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
	TLuz* luz = new TLuz();


	rotacion->setEntidad(rot);
	traslacion->setEntidad(tras);
	nodo->setEntidad(luz);

	TMotorTAG::getInstance()->registrarLuz(nodo);

	active = true;

}

FLuz::FLuz(FColor* colorin){
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

	TLuz* luz = new TLuz(1,colorr);


	rotacion->setEntidad(rot);
	traslacion->setEntidad(tras);
	nodo->setEntidad(luz);

	TMotorTAG::getInstance()->registrarLuz(nodo);

	active = true;
	isActive(true);

	color = colorin;
	intensidad = 1.0f;
}

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


FLuz::~FLuz(){
	traslacion->remHijoChange(nodo,padre);
	padre->remHijoAll(rotacion);
}


void FLuz::Rotar(vec3 rot, float ang){
	dynamic_cast<TTransf*>(rotacion->getEntidad())->rotar(rot.x, rot.y, rot.z, ang);

}


void FLuz::Mover(vec3 pos){
	dynamic_cast<TTransf*>(traslacion->getEntidad())->trasladar(pos.x,pos.y, pos.z);

}

void FLuz::Unir(FEntidad* nPadre){
	padre->changePadre(nPadre->getNodo(), rotacion);
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

vec3 FLuz::getPosicion() {
	//vec3 posicion = nodo->getPosicion();
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

}


void FLuz::setIntensity(float inte){
	intensidad = inte;

}


void FLuz::setType(int tipo){
	type = tipo;

}

