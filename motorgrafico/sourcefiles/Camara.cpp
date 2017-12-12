#include "../headerfiles/Camara.h"

Camara::Camara(int type){
	grafico = Motorgrafico::getInstance();
	escena = grafico->getScene();

	switch (type){
		case 0:
			node = escena->addCameraSceneNodeFPS();
		case 1:
			node = escena->addCameraSceneNodeMaya();
		default:
			node = escena->addCameraSceneNodeFPS();
	}
}

Camara::~Camara(){
	
}

//Devuelve el puntero al primer miembro de un array de posicion
float* Camara::getPosicion(){
	core::vector3df position = node->getPosition();
	float posicion[3] = {position.X, position.Y, position.Z};
	float* pepe = &posicion[0];

	return pepe;
}

void Camara::setPosicion(float x, float y, float z){
	node->setPosition(core::vector3df(x,y,z));
}