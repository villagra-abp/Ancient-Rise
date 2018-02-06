#include "../headerfiles/CheckAlarmaDes.h"
#include <ctime>

Status CheckAlarmaDes::run(Enemigo *e)
{   

	// DATOS DE LA ALARMA 
   a = board->getAlarma();
   core::vector3df alarmaPosition = a->getVector3df(); 
   float alarmaX=alarmaPosition.X;

   // DATOS DEL ENEMIGO
   enemigoNode = e->getNode();
   core::vector3df EnemigoPosition = enemigoNode->getPosition(); 
   float enemigoX=EnemigoPosition.X;


   int distanciaAlarma = alarmaX - enemigoX;  

   if( distanciaAlarma<100 && a->getActivado()!=true )   		// Si alarma cerca y no esta activada
   {
   		return BH_SUCCESS;
   }
   else
   {
   		 return BH_FAILURE;
   }

}


void CheckAlarmaDes::onInitialize(Blackboard *b)
{
	board = b;
}

CheckAlarmaDes::~CheckAlarmaDes()
{
    board = nullptr;
    a = nullptr;
    enemigoNode = nullptr;

    //delete board;
    //delete a;
}