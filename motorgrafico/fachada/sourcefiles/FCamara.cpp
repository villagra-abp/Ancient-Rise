#include "../headerfiles/FCamara.h"

//Original

FCamara::FCamara(){
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
	TCamara* camara = new TCamara();


	rotacion->setEntidad(rot);
	traslacion->setEntidad(tras);
	nodo->setEntidad(camara);
	
	camara->setPerspectiva(0.9, 0.8, 0.1, 2000);

	//TMotorTAG::getInstance()->registrarCamara(camara);

	active = true;

}
FCamara::~FCamara(){
	traslacion->remHijoChange(nodo,padre);
	padre->remHijoAll(rotacion);
}
void FCamara::Rotar(vec3 rot, float ang){
	dynamic_cast<TTransf*>(rotacion->getEntidad())->rotar(rot.x, rot.y, rot.z, ang);

}



void FCamara::Mover(vec3 pos){
	dynamic_cast<TTransf*>(traslacion->getEntidad())->trasladar(pos.x,pos.y, pos.z);

}


void FCamara::Activar(){
	isActive(true);
	TMotorTAG::getInstance()->activarCamara(nodo);
}

void FCamara::setPosicion(vec3 pos){
	dynamic_cast<TTransf*>(traslacion->getEntidad())->setPosition(pos.x, pos.y, pos.z);

}


void FCamara::setRotacion(vec3 rot, float ang){
	dynamic_cast<TTransf*>(rotacion->getEntidad())->setRotation(rot.x, rot.y, rot.z, ang);

}


void FCamara::isActive(bool flag){
	dynamic_cast<TCamara*>(nodo->getEntidad())->setActive(flag);

}


bool FCamara::getActive(){
	return active;
}

TNodo* FCamara::getNodo(){
	return nodo;
}

TNodo* FCamara::getTraslacion(){
	return traslacion;
}

TNodo* FCamara::getRotacion(){
	return rotacion;
}

vec3 FCamara::getPosicion(){
	
}


void FCamara::Unir(FEntidad* nPadre){
	padre->changePadre(nPadre->getTraslacion(), rotacion);
	padre = nPadre->getNodo();

}

