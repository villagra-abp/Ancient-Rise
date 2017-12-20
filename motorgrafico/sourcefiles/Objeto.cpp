#include "../headerfiles/Objeto.h"

using namespace std;

Objeto::Objeto(path s){
	grafico = Motorgrafico::getInstance();
	escena = grafico->getScene();

	mesh = escena->getMesh(s);
	animatedNode = escena->addAnimatedMeshSceneNode(mesh);
}

Objeto::Objeto(int t){
	grafico = Motorgrafico::getInstance();
	escena = grafico->getScene();

	if(t == 0)
		node = escena->addCubeSceneNode();
	else if( t == 1)
		node = escena->addSphereSceneNode();

}

Objeto::~Objeto(){

}

Vector3D Objeto::getPosicion(){
	core::vector3df v;
	if(node)
		v = node->getPosition();
	else if(animatedNode)
		v = animatedNode->getPosition();
	Vector3D pos(v.X,v.Y,v.Z);

	return pos;
}
Vector3D Objeto::getRotacion(){
	core::vector3df v;
	if(node)
		v = node->getRotation();
	else if(animatedNode)
		v = animatedNode->getRotation();
	Vector3D rot(v.X,v.Y,v.Z);

	return rot;
}

void Objeto::setAnimation(string s){
	animatedNode->setMD2Animation(scene::EMAT_STAND);
}
void Objeto::setLuz(bool flag){
	if(node)
		node->setMaterialFlag(video::EMF_LIGHTING, flag);
	else if(animatedNode)
		animatedNode->setMaterialFlag(video::EMF_LIGHTING, flag);
}
void Objeto::setMaterial(path s){
	if(node)
		node->setMaterialTexture(0,grafico->getDriver()->getTexture(s));
	else if(animatedNode)
		animatedNode->setMaterialTexture(0,grafico->getDriver()->getTexture(s));

}
void Objeto::setPosicion(Vector3D pos){
	if(node)
		node->setPosition(core::vector3df(pos.X,pos.Y,pos.Z));
	else if(animatedNode)
		animatedNode->setPosition(core::vector3df(pos.X,pos.Y,pos.Z));
}
void Objeto::setRotacion(Vector3D rot){
	if(node)
		node->setRotation(core::vector3df(rot.X,rot.Y,rot.Z));
	else if(animatedNode)
		animatedNode->setRotation(core::vector3df(rot.X,rot.Y,rot.Z));
}

