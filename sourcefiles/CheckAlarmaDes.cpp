#include "../headerfiles/CheckAlarmaDes.h"
#include <ctime>

Status CheckAlarmaDes::run(Enemigo *e)
{     

  // Habra que ampliar el bucle para contemplar todas las distancias hacia las alarmasa y acudir a la mas cercana
  // A no ser que sepamos con seguridad que nunca se podran ver dos alarmas a la vez. 
   for (size_t i = 0; i < a.size(); i++){
      if( e->see(a[i]) && a[i]->getActivado()!=true && a[i]->getActivando()!=true ) {  // Si alarma a la vista y no esta activada
        e->setAlarmaActivar(a[i]);
        return BH_SUCCESS;
      }
      /*else    // Miramos al lado contrario para buscar una alarma
      {
        e->changeLastFaceDir();
        e->actualizarVistos();

        if( e->see(a[i]) && a[i]->getActivado()!=true && a[i]->getActivando()!=true ) {  
        e->setAlarmaActivar(a[i]);
        return BH_SUCCESS;
        }
      }
      */
   }

   return BH_FAILURE;


}


void CheckAlarmaDes::onInitialize(Blackboard *b)
{
  board = b;
  a = board->getAlarma();
}

CheckAlarmaDes::~CheckAlarmaDes()
{
    board = nullptr;

    for(size_t i = 0 ; i < a.size(); i++){
      a[i] = nullptr;
    }
    a.clear();
}