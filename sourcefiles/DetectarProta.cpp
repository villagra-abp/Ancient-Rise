#include "../headerfiles/DetectarProta.h"


Status DetectarProta::run()
{
	protaPosition = board->getProta();

	scene::ISceneNode* enemigoNode = enemigo->getNode();

    core::vector3df EnemigoPosition = enemigoNode->getPosition(); // VOLVEMOS A OBTENER EL VECTOR DE POSICION DEL ENEMIGO POR SI HA CAMBIADO

    float enemigoX=EnemigoPosition.X;

    int distanciaProtaX = protaPosition - enemigoX;      // DISTANCIA EN X AL PROTAGONISTA

    if(abs(distanciaProtaX)<20)   // SI PROTA AVISTADO
     {
     	return BH_SUCCESS;
     }
     else
     {
     	return BH_FAILURE;
     }



	
}


void DetectarProta::onInitialize(Blackboard *b)
{
	enemigo = b->getEnem();
	board = b;
}

DetectarProta::~DetectarProta()
{
    
}