#include "../headerfiles/Trampa.h"



Trampa::Trampa(IrrlichtDevice *dev, ISceneManager* smgr, Posicion pos):Objeto()
{

	objeto = smgr->addCubeSceneNode();

	if (objeto)
	{

		driver = dev->getVideoDriver();
		objeto ->setPosition(core::vector3df(pos.getPosX(),pos.getPosY(),pos.getPosZ()));
		objeto ->setScale(core::vector3df(2.5f,1.5f,2.5f));
		objeto ->setMaterialFlag(video::EMF_LIGHTING, false);
		objeto ->setMaterialTexture(0,driver->getTexture("resources/pinchos.jpeg"));

	}
}



scene::ISceneNode* Trampa::getNode()
{
    return objeto;
}

