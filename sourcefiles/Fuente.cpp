#include "../headerfiles/Fuente.h"


/**
CONSTRUCTOR DE OBJETO para inicializar los valores comunes de todos los objetos consumibles
**/
Fuente::Fuente(ISceneManager* smgr, Posicion pos):Objeto()
{

	objeto = smgr->addCubeSceneNode();

	if (objeto)
	{
		objeto->setPosition(core::vector3df(pos.getPosX(),pos.getPosY(),pos.getPosZ()));
		objeto ->setScale(core::vector3df(3.f,1.f,1.f));
		objeto->setMaterialFlag(video::EMF_LIGHTING, true);
	}
}
