#include "../headerfiles/IrAlarma.h"

Status IrAlarma::run(Enemigo *e)
{   
	// Datos Alarma
	 a = board->getAlarma();
   core::vector3df alarmaPosition = a->getVector3df(); 
   float alarmaX=alarmaPosition.X;

   	// DATOS  ENEMIGO
   enemigoNode = e->getNode();
   core::vector3df EnemigoPosition = enemigoNode->getPosition(); 
   float enemigoX=EnemigoPosition.X;


   int distanciaAlarma = alarmaX - enemigoX;


  frameDeltaTime = board->getTime();

   e->setVelocidad(25.f);
   e->setCombate(false);

   if (distanciaAlarma<0) // AVANZAMOS HACIA LA IZQUIERDA
    {

        EnemigoPosition.X-= e->getVelocidad() * frameDeltaTime*2;

        e->setPosition(EnemigoPosition);

        e->setLastFacedDir(false);                                    // INDICAMOS QUE EL ENEMIGO ESTA MIRANDO A LA IZQUIERDA 
    }
    else{
           if(distanciaAlarma>0) // AVANZAMOS HACIA LA DERECHA
           {

               EnemigoPosition.X+= e->getVelocidad() * frameDeltaTime*2;

               e->setPosition(EnemigoPosition);

                e->setLastFacedDir(true);                                // INDICAMOS QUE EL ENEMIGO ESTA MIRANDO A LA DERECHA
           }
          
       }

    if(distanciaAlarma==0)
    {
    }
    
return BH_SUCCESS;

}


void IrAlarma::onInitialize(Blackboard *b)
{
	board = b;
}

IrAlarma::~IrAlarma()
{
    board = nullptr;
    a = nullptr;
    enemigoNode = nullptr;

    //delete board;
    //delete a;
}