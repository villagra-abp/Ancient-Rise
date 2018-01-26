#include "../headerfiles/OrdenAtaque.h"

Status OrdenAtaque::run(Enemigo *e)
{   
   e->setCombate(false);

   enemBActual = board->getEnemBActual();

   if(enemBActual->getCombate()!=true)  // SI el enemigo no esta atacandole ya, entonces le manda atacar
   {
      enemBActual->setOrden(1);
   }

   return BH_SUCCESS;
}

void OrdenAtaque::onInitialize(Blackboard *b)
{
	  board = b;
	  enemBActual = nullptr;
}

OrdenAtaque::~OrdenAtaque()
{
    board = nullptr;
}