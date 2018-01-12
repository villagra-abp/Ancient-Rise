#include "../headerfiles/Atacar.h"
#include <ctime>
#include <stdlib.h> 

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
        separacionAtaque = 25;
    }
    else  // A distancia, ataque desde mas lejos
    {
        //separacionAtaque = 60;
        separacionAtaque = 25;
    }

    if(abs(distanciaProta)>separacionAtaque)        // Comprobamos la distancia a la que tiene que estar para atacar
    {
        e->setCombate(false);

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
        e->setCombate(true);    // COMBATIENDO

        int pos_combate = rand() % 3 + 1;

         /* RELOJ POS COMBATE */
        this->startClock();                             // INICIAMOS EL RELOJ (O RESEATEAMOS)

        int time = reloj.getElapsedTime().asSeconds();  // OBTENEMOS SU DURACION EN SEGUNDOS

        if(time>2)
        {
            e->setPosCombate(pos_combate);
            contador = 0;
        }

    }
    return BH_SUCCESS;
    
}

void Atacar::startClock()
{
    if(contador==0)
    {
        reloj.restart();
        contador = contador +1;
    }
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