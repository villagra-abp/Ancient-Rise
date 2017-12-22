#include "../headerfiles/Bebida.h"



Bebida::Bebida(ISceneManager* smgr, Posicion pos):Objeto()
{

	bebida = smgr->addCubeSceneNode();

	if (bebida)
	{
		bebida ->setPosition(core::vector3df(pos.getPosX(),pos.getPosY(),pos.getPosZ()));
		bebida ->setScale(core::vector3df(0.5f,1.5f,0.5f));
	}
}



scene::ISceneNode* Bebida::getNode()
{
    return bebida;
}

