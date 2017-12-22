#include "../headerfiles/Trampa.h"



Trampa::Trampa(ISceneManager* smgr, Posicion pos):Objeto()
{

	trampa = smgr->addCubeSceneNode();

	if (trampa)
	{
		trampa ->setPosition(core::vector3df(pos.getPosX(),pos.getPosY(),pos.getPosZ()));
		trampa ->setScale(core::vector3df(2.5f,1.5f,2.5f));
	}
}



scene::ISceneNode* Trampa::getNode()
{
    return trampa;
}

