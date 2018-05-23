#include "../headerfiles/FSkybox.h"

//Original

FSkybox::FSkybox(){
	padre = TMotorTAG::getInstance()->getEscena();
	//TNodo* nodo, rotacion, traslacion;

	nodo = new TNodo();

	padre->addHijoBack(nodo);

	TSkybox* skybox = new TSkybox();

	nodo->setEntidad(skybox);

	TMotorTAG::getInstance()->registrarSkybox(nodo);

	active = true;
}

FSkybox::~FSkybox(){
	padre->remHijoChange(nodo,padre);
	//padre->remHijoAll(nodo);
}

void FSkybox::setSkybox(vector<string> paths){
	dynamic_cast<TSkybox*>(nodo->getEntidad())->cargarSkybox(paths);
}