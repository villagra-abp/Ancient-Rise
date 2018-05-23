#include "../headerfiles/FBillboard.h"

//Original
	
FBillboard::FBillboard(){
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
	TMalla* mesh = new TMalla(true);


	rotacion->setEntidad(rot);
	traslacion->setEntidad(tras);
	nodo->setEntidad(mesh);


	active = true;

}

FBillboard::~FBillboard(){
	traslacion->remHijoChange(nodo,padre);
	padre->remHijoAll(rotacion);
}

void FBillboard::Rotar(vec3 rot, float ang) {

}
void FBillboard::setRotacion(vec3 rot, float ang) {

}

void FBillboard::setMalla(string path){
	TMalla* mesh = new TMalla(true);
	nodo->setEntidad(mesh);
	dynamic_cast<TMalla*>(nodo->getEntidad())->cargarMalla(path);
}