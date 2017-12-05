#include "../headerfiles/EnemigoBasico.h"


/**
CONSTRUCTOR DE ENEMIGO BASICO
**/
EnemigoBasico::EnemigoBasico(IrrlichtDevice *dev, ISceneManager* smgr, Posicion *posiciones[]):Enemigo(dev, smgr, posiciones)
{

    //ESTADISTICAS ENEMIGO BASICO

    this->setEnergia(100.f);
    this->setHambre(100.f);
    this->setSalud(100.f);
    this->setSed(100.f);
    this->setVelocidad(8.f);
}

/**
PARA COMPROBAR QUE COMPORTAMIENTO REALIZAR
**/
void EnemigoBasico::comprobarComportamiento()
{


    if(this->getEstadoAvistadoProta()==true) // PROTA AVISTADO
    {

    }

    if(this->getEstadoAlarma()==true)  // ALARMA ACTIVADA
    {

    }



}

EnemigoBasico::~EnemigoBasico()
{
    //dtor
}
