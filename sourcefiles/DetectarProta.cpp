#include "../headerfiles/DetectarProta.h"


Status DetectarProta::run(Enemigo *e)
{
    if(e->getVisto())   // SI PROTA AVISTADO
     {
        if(e->getLastFaceDir()==true)               // COMPROBAMOS ULTIMA DIRECCION A LA QUE ESTABA MIRANDO EL ENEMIGO               
        {
            e->setUltDirecVisto(true);              // Visto Prota a la derecha
        }
        else
        {
            e->setUltDirecVisto(false);             // Visto Prota a la izquierda
        }
        
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