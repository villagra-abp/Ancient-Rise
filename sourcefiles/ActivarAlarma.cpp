#include "../headerfiles/ActivarAlarma.h"

Status ActivarAlarma::run(Enemigo *e)
{   
   // DATOS DEL ENEMIGO
   enemigoNode = e->getNode();
   core::vector3df EnemigoPosition = enemigoNode->getPosition(); 
   float enemigoX=EnemigoPosition.X;

   //SELECCIONA LA ALARMA A ACTIVAR
   
   for (int i = 0; i < a.size(); i++){
      if( e->see(a[i]) && a[i]->getActivado()!=true ) {  // Si alarma a la vista y no esta activada
        
        alarmaPosition = a[i]->getVector3df();
        alarmaX=alarmaPosition.X;

        pos = i;
        i = a.size();
      }
   }

   distanciaAlarma = alarmaX - enemigoX;  

   frameDeltaTime = board->getTime();

   e->setVelocidad(25.f);
   e->setCombate(false);

   // COMPROBAMOS LA DISTANCIA A LA QUE ESTA LA ALARMA Y AVANZAMOS HACIA ELLA 
   
   if (distanciaAlarma<0) // AVANZAMOS HACIA LA IZQUIERDA
    {

        EnemigoPosition.X-= e->getVelocidad() * frameDeltaTime;

        e->setPosition(EnemigoPosition);

        e->setLastFacedDir(false);                        // MIRANDO HACIA LA IZQUIERDA
  
    }
    else{
           if(distanciaAlarma>0) // AVANZAMOS HACIA LA DERECHA
           {

               EnemigoPosition.X+= e->getVelocidad() * frameDeltaTime;

               e->setPosition(EnemigoPosition);

               e->setLastFacedDir(true);                // // MIRANDO HACIA LA DERECHA
           }
          
       }

    if(distanciaAlarma == 0) 		// Si hemos llegado inciamos la activacion
    {
    	   // RELOJ ACTIVACION ALARMA
        this->startClock();                                 // INICIAMOS EL RELOJ (O RESEATEAMOS)

        int duration = reloj.getElapsedTime().asSeconds();  // OBTENEMOS SU DURACION EN SEGUNDOS

        //cout<<duration<<endl;

    	if(duration > 2)        // TIEMPO QUE TARDA EN ACTIVARLA
    	{
    		a[pos]->setActivado(true);
        contador = 0; // Para resetear el reloj

    		return BH_SUCCESS;
    	}
    }
     
  return BH_RUNNING;        // Hasta que no active la alarma no habra terminado
}

void ActivarAlarma::startClock()
{
    if(contador==0)
    {
        reloj.restart();
        contador = contador +1;
    }
}

void ActivarAlarma::onInitialize(Blackboard *b)
{
	  board = b;
    a = board->getAlarma();
    
    contador = 0;
    alarmaX = 0.0;
    distanciaAlarma = 0;
    pos = 0;
}

ActivarAlarma::~ActivarAlarma()
{
    board = nullptr;
    enemigoNode = nullptr;

    for(int i = 0 ; i < a.size(); i++){
      a[i] = nullptr;
      delete a[i];  //No se si es necesario
    }

    a.clear();

   // delete board;
    //delete a;
}