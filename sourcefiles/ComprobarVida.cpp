#include "../headerfiles/ComprobarVida.h"
#include "../headerfiles/EnemigoBasico.h"
#include <ctime> 

Status ComprobarVida::run(Enemigo *e)
{
	//Comprobamos que clase de enemigo es
    switch(e->getClaseEnemigo())
    {
        case(1):  /* Enemigo Basico */
        {
            if(e->getSalud()<30)              // Vida por debajo de 30
            {
                return BH_SUCCESS;
            }
            else
            {
                return BH_FAILURE;
            }

            break;
        }

        case(2): /* Enemigo Avanzado */
        {
            if(e->getSalud()<20 && e->see(board->getProtagonista()))
            {
                return BH_SUCCESS;
            }
            else
            {
                return BH_FAILURE;
            }
            break;
        }

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