#include "../headerfiles/DetectarProta.h"


Status DetectarProta::run(Enemigo *e)
{
    if(e->getVisto())   // SI PROTA AVISTADO
     {
        return BH_SUCCESS;
     }
     else              // PROTA NO AVISTADO
     { 
     	return BH_FAILURE;
     }
	
}
void DetectarProta::onInitialize(Blackboard *b)
{
	board = b;
}

DetectarProta::~DetectarProta()
{
    board = nullptr;
}