#include "../headerfiles/Bebida.h"



Bebida::Bebida(IrrlichtDevice *dev, ISceneManager* smgr, Posicion pos):Objeto()
{
	GameObject::setTipo(BEBIDA);
	objeto = smgr->addCubeSceneNode();

	if (objeto)
	{
		driver = dev->getVideoDriver();
		objeto ->setPosition(core::vector3df(pos.getPosX(),pos.getPosY(),pos.getPosZ()));
		objeto ->setScale(core::vector3df(0.5f,1.5f,0.5f));
		objeto ->setMaterialFlag(video::EMF_LIGHTING, false);
		objeto ->setMaterialTexture(0,driver->getTexture("resources/pocion.png"));

	}
}



scene::ISceneNode* Bebida::getNode()
{
    return objeto;
}

