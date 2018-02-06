#include "../headerfiles/Atacar.h"
#include <ctime>

Status Atacar::run(Enemigo *e)
{   
   
	float posProta = board->getProta();

	// DATOS ENEMIGO
	enemigoNode = e->getNode();
    core::vector3df EnemigoPosition = enemigoNode->getPosition(); 
    float enemigoX=EnemigoPosition.X;

    int distanciaProta = posProta - enemigoX;  // Calculamos la distancia hasta la fuente

    frameDeltaTime = board->getTime();

    e->setVelocidad(25.f);

    // Comprobamos el tipo de arma que utiliza
    if(e->getTipo()==1)     // Cuerpo a cuerpo, cerca
    {
        separacionAtaque = 15;
    }
    else  // A distancia, ataque desde mas lejos
    {
        separacionAtaque = 60;
    }

    if(abs(distanciaProta)>separacionAtaque)        // Comprobamos la distancia a la que tiene que estar para atacar
    {
        if (distanciaProta<0) // AVANZAMOS HACIA LA IZQUIERDA
         {

                    EnemigoPosition.X-= e->getVelocidad() * frameDeltaTime*4;

                    e->setPosition(EnemigoPosition); 

                    e->setLastFacedDir(false);   
         }
         else{
                if(distanciaProta>0) // AVANZAMOS HACIA LA DERECHA
                {

                    EnemigoPosition.X+= e->getVelocidad() * frameDeltaTime*4;

                    e->setPosition(EnemigoPosition);

                    e->setLastFacedDir(true);   
                }
            }
    }
    else        // ATACANDO
    {
        
    }

    
    return BH_SUCCESS;
    
}


void Atacar::onInitialize(Blackboard *b)
{
	board = b;

    separacionAtaque = 10;
}

Atacar::~Atacar()
{
    board = nullptr;
    enemigoNode = nullptr;

    //delete board;
}