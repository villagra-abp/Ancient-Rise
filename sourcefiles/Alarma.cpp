#include "../headerfiles/Alarma.h"


Alarma::Alarma(IrrlichtDevice *dev, ISceneManager* smgr, Posicion* pos):Objeto(pos)
{
	GameObject::setTipo(ALARMA);
    Fachada* fachada=fachada->getInstance();
	objeto = fachada->addCube(pos->getPosX(),pos->getPosY(),pos->getPosZ(),false);
    //std::cout<<pos.getPosX()<<endl;
	if (objeto)
	{
        
        Posicion escala(1.f,6.f,1.f);
		fachada->setScala(objeto,&escala);
		
        fachada->setMaterial(objeto,"resources/desactivada.jpeg");
	}

	contador = 0;
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

		startClock();

		int time = reloj.getElapsedTime().asSeconds();  // OBTENEMOS SU DURACION EN SEGUNDOS

		if(time>35) 		// DURACION ALARMA ACTIVADA
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
