#include "../headerfiles/Alarma.h"



Alarma::Alarma(ISceneManager* smgr, Posicion pos):Objeto()
{
	objeto = smgr->addCubeSceneNode();

	if (objeto)
	{
		objeto ->setPosition(core::vector3df(pos.getPosX(),pos.getPosY(),pos.getPosZ()));
		objeto->setMaterialFlag(video::EMF_LIGHTING, false);
		objeto ->setScale(core::vector3df(1.f,6.f,1.f));
	}
}


Alarma::~Alarma()
{

}