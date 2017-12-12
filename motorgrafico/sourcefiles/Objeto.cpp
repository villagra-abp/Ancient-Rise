#include "../headerfiles/Objeto.h"

using namespace std;

Objeto::Objeto(path s){
	grafico = Motorgrafico::getInstance();
	escena = grafico->getScene();

	mesh = escena->getMesh(s);
	node = escena->addAnimatedMeshSceneNode(mesh);
}

Objeto::~Objeto(){

}


void Objeto::setLuz(bool flag){
	node->setMaterialFlag(video::EMF_LIGHTING, flag);
}
void Objeto::setMaterial(path s){
	node->setMaterialTexture(0,grafico->getDriver()->getTexture(s));
}
void Objeto::setAnimation(string s){
	node->setMD2Animation(scene::EMAT_STAND);
}
