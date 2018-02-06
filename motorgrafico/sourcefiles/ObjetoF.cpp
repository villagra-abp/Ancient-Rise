
#include "../headerfiles/ObjetoF.h"

using namespace std;

ObjetoF::ObjetoF(path s){
	grafico = Motorgrafico::getInstance();
	escena = grafico->getScene();

	mesh = escena->getMesh(s);
	animatedNode = escena->addAnimatedMeshSceneNode(mesh);
}

ObjetoF::ObjetoF(int t){
	grafico = Motorgrafico::getInstance();
	escena = grafico->getScene();

	if(t == 0)
		node = escena->addCubeSceneNode();
	else if( t == 1)
		node = escena->addSphereSceneNode();

}

ObjetoF::~ObjetoF(){

}

Vector3D ObjetoF::getPosicion(){
	core::vector3df v;
	if(node)
		v = node->getPosition();
	else if(animatedNode)
		v = animatedNode->getPosition();
	Vector3D pos(v.X,v.Y,v.Z);

	return pos;
}
Vector3D ObjetoF::getRotacion(){
	core::vector3df v;
	if(node)
		v = node->getRotation();
	else if(animatedNode)
		v = animatedNode->getRotation();
	Vector3D rot(v.X,v.Y,v.Z);

	return rot;
}

void ObjetoF::setAnimation(string s){
	animatedNode->setMD2Animation(scene::EMAT_STAND);
}
void ObjetoF::setLuz(bool flag){
	if(node)
		node->setMaterialFlag(video::EMF_LIGHTING, flag);
	else if(animatedNode)
		animatedNode->setMaterialFlag(video::EMF_LIGHTING, flag);
}
void ObjetoF::setMaterial(path s){
	if(node)
		node->setMaterialTexture(0,grafico->getDriver()->getTexture(s));
	else if(animatedNode)
		animatedNode->setMaterialTexture(0,grafico->getDriver()->getTexture(s));

}
void ObjetoF::setPosicion(Vector3D pos){
	if(node)
		node->setPosition(core::vector3df(pos.X,pos.Y,pos.Z));
	else if(animatedNode)
		animatedNode->setPosition(core::vector3df(pos.X,pos.Y,pos.Z));
}
void ObjetoF::setRotacion(Vector3D rot){
	if(node)
		node->setRotation(core::vector3df(rot.X,rot.Y,rot.Z));
	else if(animatedNode)
		animatedNode->setRotation(core::vector3df(rot.X,rot.Y,rot.Z));
}

