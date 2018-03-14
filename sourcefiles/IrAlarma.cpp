#include "../headerfiles/IrAlarma.h"

Status IrAlarma::run(Enemigo *e)
{   
    // DATOS  ENEMIGO
   enemigoNode = e->getNode();
   Posicion* EnemigoPosition = e->getPosition(); 
   float enemigoX=EnemigoPosition->getPosX();

  // Habra que ampliar el bucle para contemplar todas las distancias hacia las alarmas que esten sonando
  // y acudir a la mas cercana
  
   for (int i = 0; i < a.size(); i++){
      alarmaPosition = a[i]->getVector3df();
      alarmaX=alarmaPosition->getPosX();

      distanciaAlarma = alarmaX - enemigoX;

      if( abs(distanciaAlarma)<100 && a[i]->getActivado() ) {  // Si alarma dentro de RANGO DE ESCUCHA y esta activada 
        i = a.size();
      }
   }
   
   e->setCombate(false);

   if (distanciaAlarma<0) // AVANZAMOS HACIA LA IZQUIERDA
    {

        e->getBody()->SetLinearVelocity(-(e->getVelocidad2d()));               // Velocidad Normal
        e->getBody()->ApplyForceToCenter(b2Vec2(-150.f,0.f),true);             // Fuerza para correr

        e->setLastFacedDir(false);                                    // INDICAMOS QUE EL ENEMIGO ESTA MIRANDO A LA IZQUIERDA 
    }
    else{
           if(distanciaAlarma>0) // AVANZAMOS HACIA LA DERECHA
           {

                e->getBody()->SetLinearVelocity(e->getVelocidad2d());
                e->getBody()->ApplyForceToCenter(b2Vec2(150.f,0.f),true);             // Fuerza para correr
                
                e->setLastFacedDir(true);                                // INDICAMOS QUE EL ENEMIGO ESTA MIRANDO A LA DERECHA
           }
          
       }

    if(distanciaAlarma==0)
    {
    }
    
return BH_SUCCESS;

}


void IrAlarma::onInitialize(Blackboard *b)
{
  board = b;
  a = board->getAlarma();
  alarmaX = 0.0;
  distanciaAlarma = 0;
}

IrAlarma::~IrAlarma()
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
