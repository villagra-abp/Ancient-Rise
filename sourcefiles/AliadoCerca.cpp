#include "../headerfiles/AliadoCerca.h"

Status AliadoCerca::run(Enemigo *e)
{   
   e->setCombate(false);

   for(size_t i=0;i<enemigosB.size();i++)
   {
	   	if( e->see(enemigosB[i]) )
	   	{
	   		board->setEnemBActual(enemigosB[i]); 		// Indicamos que enemigo estamos viendo a la blackboard
	   		return BH_SUCCESS;
	   	}
   }


   board->setEnemBActual(nullptr); 		// Indicamos que enemigo estamos viendo a la blackboard
   return BH_FAILURE;

}

void AliadoCerca::onInitialize(Blackboard *b)
{
	  board = b;
	  enemigosB = board->getEnemB();
}

AliadoCerca::~AliadoCerca()
{
    board = nullptr;
    enemigoNode = nullptr;
}