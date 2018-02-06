#include "../headerfiles/CheckOrden.h"

Status CheckOrden::run(Enemigo *e)
{   
   if(e->getOrden()!=0) 		// Solo entramos si el enemigo basico ha recibido una orden de algun superior
   {
   	 return BH_SUCCESS;
   }
   else
   {
   	 return BH_FAILURE;
   }

}

void CheckOrden::onInitialize(Blackboard *b)
{
	  board = b;
	  
}

CheckOrden::~CheckOrden()
{
    board = nullptr;
}