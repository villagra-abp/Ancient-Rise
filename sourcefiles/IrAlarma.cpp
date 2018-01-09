#include "../headerfiles/IrAlarma.h"

Status IrAlarma::run(Enemigo *e)
{   
	// Datos Alarma
	 a = board->getAlarma();
   core::vector3df alarmaPosition = a->getVector3df(); 
   float alarmaX=alarmaPosition.X;

   	// DATOS  ENEMIGO
   scene::ISceneNode* enemigoNode = e->getNode();
   core::vector3df EnemigoPosition = enemigoNode->getPosition(); 
   float enemigoX=EnemigoPosition.X;


   int distanciaAlarma = alarmaX - enemigoX;


  frameDeltaTime = board->getTime();

   e->setVelocidad(25.f);

   if (distanciaAlarma<0) // AVANZAMOS HACIA LA IZQUIERDA
    {

        EnemigoPosition.X-= e->getVelocidad() * frameDeltaTime;

        e->setPosition(EnemigoPosition);
    }
    else{
           if(distanciaAlarma>0) // AVANZAMOS HACIA LA DERECHA
           {

               EnemigoPosition.X+= e->getVelocidad() * frameDeltaTime;

               e->setPosition(EnemigoPosition);
           }
          
       }

    if(distanciaAlarma==0)
    {
      return BH_SUCCESS;
    }
    else
    {
      return BH_FAILURE;
    }

}


void IrAlarma::onInitialize(Blackboard *b)
{
	board = b;
}

IrAlarma::~IrAlarma()
{
    board = nullptr;
    a = nullptr;

    delete board;
    delete a;
}