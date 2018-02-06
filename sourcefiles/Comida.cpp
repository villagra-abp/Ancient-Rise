#include "../headerfiles/Comida.h"



Comida::Comida(ISceneManager* smgr, Posicion pos):Objeto()
{

	objeto = smgr->addCubeSceneNode();

	if (objeto)
	{
		objeto ->setPosition(core::vector3df(pos.getPosX(),pos.getPosY(),pos.getPosZ()));
		objeto ->setScale(core::vector3df(0.5f,0.5f,0.5f));
	}
}



scene::ISceneNode* Comida::getNode()
{
    return objeto;
}

