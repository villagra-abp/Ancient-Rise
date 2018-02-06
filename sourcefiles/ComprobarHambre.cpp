#include "../headerfiles/ComprobarHambre.h"



Status ComprobarHambre::run(Enemigo *e)
{

	if(e->getHambre()<=35)
	{
		return BH_SUCCESS;
	}
	else
	{
		return BH_FAILURE;
	}
}


void ComprobarHambre::onInitialize(Blackboard *b)
{
  
}


ComprobarHambre::~ComprobarHambre()
{
    
}