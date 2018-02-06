#include "../headerfiles/AlarmaSonando.h"


Status AlarmaSonando::run(Enemigo *e)
{   
    // DATOS  ENEMIGO
   enemigoNode = e->getNode();
   core::vector3df EnemigoPosition = enemigoNode->getPosition(); 
   float enemigoX=EnemigoPosition.X;

   //Busca alarmas sonando dentro del rango de escucha
   //Se puede ampoliar para ir a la alarma mas cercana y no a la primera que escuche

   e->setCombate(false);

   bool avalible = false; 
   for (int i = 0; i < a.size(); i++){
      
      alarmaPosition = a[i]->getVector3df();
      alarmaX=alarmaPosition.X;
      distanciaAlarma = alarmaX - enemigoX;

      if( abs(distanciaAlarma)<100  && a[i]->getActivado() ) {  // Alarma cerca (RANGO DE ESCUCHA) y activada
        return BH_SUCCESS;
      }
   }
  
    return BH_FAILURE;
}


void AlarmaSonando::onInitialize(Blackboard *b)
{
  board = b;
  a = board->getAlarma();
  alarmaX = 0.0;
  distanciaAlarma = 0;
}

AlarmaSonando::~AlarmaSonando()
{
    board = nullptr;
    enemigoNode = nullptr;

    for(int i = 0 ; i < a.size(); i++){
      a[i] = nullptr;
      delete a[i];  //No se si es necesario
    }

    a.clear();
    
    //delete board;
    //delete a;
}