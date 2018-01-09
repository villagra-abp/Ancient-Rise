#include "../headerfiles/ComprobarSed.h"



Status ComprobarSed::run(Enemigo *e)
{

	if(e->getSed()<=45)
	{
		return BH_SUCCESS;
	}
	else
	{
		return BH_FAILURE;
	}
}


void ComprobarSed::onInitialize(Blackboard *b)
{
  
}


ComprobarSed::~ComprobarSed()
{
    
}