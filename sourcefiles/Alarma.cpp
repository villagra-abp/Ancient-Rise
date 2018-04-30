#include "../headerfiles/Alarma.h"


Alarma::Alarma(Posicion* pos):Objeto(pos)
{
	GameObject::setTipo(ALARMA);
    Fachada* fachada=fachada->getInstance();
	objeto = fachada->addMalla(pos->getPosX(),pos->getPosY(),pos->getPosZ(),"resources/alarma.obj");

	if (objeto)
	{
        Posicion escala(0.3f,0.3f,0.3f);
		fachada->setScala(objeto,&escala);
	}

	contador = 0;

	//GESTION SONIDO
   	sonido = GestorSonido::getInstance();
   	alarmaSound = sonido->create2DSound(sonido->SOUND_TRAP_ALARM);
}


void Alarma::update()
{
	checkActivada();
}

/*
FUNCION PARA COMPROBAR SI LA ALARMA HA SIDO ACTIVADA Y DESACTIVARLA CUANDO HAYA PASADO UN TIEMPO DETERMINADO
*/
void Alarma::checkActivada()
{
    Fachada* fachada=fachada->getInstance();
	if( activado == true)
	{
		fachada->setMaterialFlag(objeto , false);
		fachada->setMaterial(objeto ,"resources/activada.jpeg");

		//SONIDO DE ALARMA
        sonido->playSound(alarmaSound);

		startClock();

		int time = reloj.getElapsedTime().asSeconds();  // OBTENEMOS SU DURACION EN SEGUNDOS

		if(time>20) 		// DURACION ALARMA ACTIVADA
		{
			activado = false;
			fachada->setMaterialFlag(objeto , false);
			fachada->setMaterial(objeto ,"resources/desactivada.jpeg");
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
