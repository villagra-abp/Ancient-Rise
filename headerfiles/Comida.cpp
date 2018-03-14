#include "../headerfiles/Comida.h"



Comida::Comida(ISceneManager* smgr, Posicion pos):Objeto()
{

	comida = smgr->addCubeSceneNode();

	if (comida)
	{
		comida ->setPosition(core::vector3df(pos.getPosX(),pos.getPosY(),pos.getPosZ()));
		comida ->setScale(core::vector3df(0.5f,0.5f,0.5f));
	}
}



scene::ISceneNode* Comida::getNode()
{
    return comida;
}

