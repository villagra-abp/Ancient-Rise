#include "../headerfiles/AlarmaSonando.h"
#include <ctime>

Status AlarmaSonando::run(Enemigo *e)
{   
	// Datos Alarma
	a = board->getAlarma();
  core::vector3df alarmaPosition = a->getVector3df(); 
  float alarmaX=alarmaPosition.X;

   	// DATOS  ENEMIGO
   enemigoNode = e->getNode();
   core::vector3df EnemigoPosition = enemigoNode->getPosition(); 
   float enemigoX=EnemigoPosition.X;


   int distanciaAlarma = alarmaX - enemigoX;

   if( distanciaAlarma<50  && a->getActivado()!=false )    	// Alarma cerca y activada
   {
   		return BH_SUCCESS;
   }
   else
   {
   		return BH_FAILURE;
   }
}


void AlarmaSonando::onInitialize(Blackboard *b)
{
	board = b;
}

AlarmaSonando::~AlarmaSonando()
{
    board = nullptr;
    a = nullptr;
    enemigoNode = nullptr;

    //delete board;
    //delete a;
}