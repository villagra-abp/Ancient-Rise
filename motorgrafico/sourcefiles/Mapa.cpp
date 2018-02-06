#include "../headerfiles/Mapa.h"


Mapa::Mapa(io::path s){
	grafico = Motorgrafico::getInstance();
	escena = grafico->getScene();

	grafico->getDevice()->getFileSystem()->addFileArchive(s);

	mesh = escena->getMesh("20kdm2.bsp");
	node = 0;

	node = escena->addOctreeSceneNode(mesh->getMesh(0), 0, -1, 1024);

}

Mapa::~Mapa(){

}

void Mapa::setPosicion(int x, int y, int z){
	node->setPosition(core::vector3df(x,y,z));
}