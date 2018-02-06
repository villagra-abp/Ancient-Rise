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

float Camara::getFOV(){
	float fov = node->getFOV();

	return fov;
}

//Devuelve el puntero al primer miembro de un array de posicion
Vector3D Camara::getPosicion(){
	core::vector3df position = node->getPosition();
	Vector3D pepe(position.X, position.Y, position.Z);

	return pepe;
}

Vector3D Camara::getRotation(){
	core::vector3df rot = node->getRotation();
	Vector3D pepote(rot.X, rot.Y, rot.Z);

	return pepote;
}

void Camara::setFOV(float fov){
	node->setFOV(fov);
}

void Camara::setRotation(Vector3D rot){
	node->setRotation(core::vector3df(rot.X,rot.Y,rot.Z));
}



void Camara::setPosicion(Vector3D pos){
	node->setPosition(core::vector3df(pos.X,pos.Y,pos.Z));
}