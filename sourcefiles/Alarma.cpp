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
		objeto->setMaterialFlag(video::EMF_LIGHTING, true);

		this->startClock();

		int time = reloj.getElapsedTime().asSeconds();  // OBTENEMOS SU DURACION EN SEGUNDOS

		if(time>8) 		// DURACION ALARMA ACTIVADA
		{
			activado = false;
			objeto->setMaterialFlag(video::EMF_LIGHTING, false);
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