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
PARA COMPROBAR EN QUE COMPORTAMIENTO ESTA EL ENEMIGO
**/
void EnemigoBasico::Update(scene::ISceneNode *alarma)
{

    if(this->getEstadoPatrulla()==false) // NO ESTA PATRULLANDO
    {
        if(this->getEstadoAvistadoProta()==true)  // PROTA AVISTADO
        {
            this->AvistadoProta(); // CAMBIAMOS AL COMPORTAMIENTO DE AVISTADO PROTA 
        }

        if (this->getEstadoAlarma()==true) // ALARMA SONANDO 
        {
            this->AlarmaSonando(alarma); // CAMBIAMOS AL COMPORTAMIENTO DE ALARMA SONANDO 
        }
    
    }

}


/**
FUNCION PARA VER QUE HACE EL ENEMIGO BASICO CUANDO VE AL PROTAGONISTA
**/
void EnemigoBasico::AvistadoProta()
{
    

}


/**
FUNCION PARA VER QUE HACE EL ENEMIGO BASICO CUANDO SUENA LA ALARMA
**/
void EnemigoBasico::AlarmaSonando(scene::ISceneNode *alarma)
{

   

}


EnemigoBasico::~EnemigoBasico()
{
    //dtor
}
