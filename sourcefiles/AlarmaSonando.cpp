#include "../headerfiles/AlarmaSonando.h"


Status AlarmaSonando::run(Enemigo *e)
{   
    // DATOS  ENEMIGO
   enemigoNode = e->getNode();
   Posicion* EnemigoPosition = e->getPosition(); 
   float enemigoX=EnemigoPosition->getPosX();

   //Busca alarmas sonando dentro del rango de escucha
   //Se puede ampoliar para ir a la alarma mas cercana y no a la primera que escuche

   e->setCombate(false);

   bool avalible = false; 
   for (size_t i = 0; i < a.size(); i++){
      
      alarmaPosition = a[i]->getVector3df();
      alarmaX=alarmaPosition->getPosX();
      distanciaAlarma = alarmaX - enemigoX;

      if( abs(distanciaAlarma)<200  && a[i]->getActivado() ) // Alarma cerca (RANGO DE ESCUCHA) y activada
      { /* 
        if(abs(distanciaAlarma)<20) // Si ya estamos al lado de la alarma no hay que ir hacia ella
        {
          cout<<"Cerca"<<endl;
          return BH_FAILURE;
        }*/
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

    for(size_t i = 0 ; i < a.size(); i++){
      a[i] = nullptr;
    }

    a.clear();
}
