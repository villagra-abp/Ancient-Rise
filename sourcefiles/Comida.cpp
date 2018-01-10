#include "../headerfiles/Comida.h"



Comida::Comida(IrrlichtDevice *dev, ISceneManager* smgr, Posicion pos):Objeto()
{

	objeto = smgr->addSphereSceneNode();

	if (objeto)
	{
		driver = dev->getVideoDriver();
		objeto ->setPosition(core::vector3df(pos.getPosX(),pos.getPosY(),pos.getPosZ()));
		objeto ->setScale(core::vector3df(1.25f,1.25f,1.25f));
		objeto ->setMaterialFlag(video::EMF_LIGHTING, false);
		objeto ->setMaterialTexture(0,driver->getTexture("../resources/elon.jpeg"));

	}
}



scene::ISceneNode* Comida::getNode()
{
    return objeto;
}

