#include "../headerfiles/DetectarProta.h"


Status DetectarProta::run(Enemigo *e)
{
	protaPosition = board->getProta();

	scene::ISceneNode* enemigoNode = e->getNode();

    core::vector3df EnemigoPosition = enemigoNode->getPosition(); // VOLVEMOS A OBTENER EL VECTOR DE POSICION DEL ENEMIGO POR SI HA CAMBIADO

    float enemigoX=EnemigoPosition.X;

    int distanciaProtaX = protaPosition - enemigoX;      // DISTANCIA EN X AL PROTAGONISTA

    if(e->getVisto())   // SI PROTA AVISTADO
     {
        //e->setAvistadoProta(true);

        return BH_SUCCESS;
     }
     else
     {
        //e->setAvistadoProta(false);
        
     	return BH_FAILURE;
     }



	
}


void DetectarProta::onInitialize(Blackboard *b)
{
	board = b;
}

DetectarProta::~DetectarProta()
{
    
}