#include "../headerfiles/ComprobarVida.h"
#include <ctime>


Status ComprobarVida::run(Enemigo *e)
{
	// Falta Ver como hacer para hacer distintas cosas en funcion del tipo de enemigo

    if(e->getSalud()<=30)
    {
        
        return BH_SUCCESS;
    }
    else
    {
        return BH_FAILURE;
    }
}


void ComprobarVida::onInitialize(Blackboard *b)
{
	board = b;
}

ComprobarVida::~ComprobarVida()
{
    board = nullptr;
}