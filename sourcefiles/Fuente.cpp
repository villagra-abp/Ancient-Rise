#include "../headerfiles/Fuente.h"


/**
CONSTRUCTOR DE OBJETO para inicializar los valores comunes de todos los objetos consumibles
**/
Fuente::Fuente(IrrlichtDevice *dev, ISceneManager* smgr, Posicion pos):Objeto()
{

	objeto = smgr->addCubeSceneNode();

	if (objeto)
	{
		driver = dev->getVideoDriver();
		objeto->setPosition(core::vector3df(pos.getPosX(),pos.getPosY(),pos.getPosZ()));
		objeto ->setScale(core::vector3df(2.5f,1.f,1.f));
		objeto ->setMaterialFlag(video::EMF_LIGHTING, false);
		objeto ->setMaterialTexture(0,driver->getTexture("../resources/gota.jpg"));

	}
}
