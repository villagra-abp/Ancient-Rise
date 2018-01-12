#include "../headerfiles/Alarma.h"



Alarma::Alarma(IrrlichtDevice *dev, ISceneManager* smgr, Posicion pos):Objeto()
{
	objeto = smgr->addCubeSceneNode();

	if (objeto)
	{
		driver = dev->getVideoDriver();
		objeto ->setPosition(core::vector3df(pos.getPosX(),pos.getPosY(),pos.getPosZ()));
		objeto ->setScale(core::vector3df(1.f,6.f,1.f));
		objeto ->setMaterialFlag(video::EMF_LIGHTING, false);
		objeto ->setMaterialTexture(0,driver->getTexture("resources/desactivada.jpeg"));

	}

	contador = 0;
}


void Alarma::update()
{
	
	this->checkActivada();
	
}

/*
FUNCION PARA COMPROBAR SI LA ALARMA HA SIDO ACTIVADA Y DESACTIVARLA CUANDO HAYA PASADO UN TIEMPO DETERMINADO
*/
void Alarma::checkActivada()
{
	if( activado == true)
	{
		objeto ->setMaterialFlag(video::EMF_LIGHTING, false);
		objeto ->setMaterialTexture(0,driver->getTexture("resources/activada.jpeg"));

		this->startClock();

		int time = reloj.getElapsedTime().asSeconds();  // OBTENEMOS SU DURACION EN SEGUNDOS

		if(time>35) 		// DURACION ALARMA ACTIVADA
		{
			activado = false;
			objeto ->setMaterialFlag(video::EMF_LIGHTING, false);
			objeto ->setMaterialTexture(0,driver->getTexture("resources/desactivada.jpeg"));
			contador = 0; 		// Reseteo reloj
		}
	}
}

void Alarma::startClock()
{
    if(contador==0)
    {
        reloj.restart();
        contador = contador +1;
    }
}

Alarma::~Alarma()
{

}