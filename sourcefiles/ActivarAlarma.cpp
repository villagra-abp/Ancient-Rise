#include "../headerfiles/ActivarAlarma.h"

Status ActivarAlarma::run(Enemigo *e)
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

   frameDeltaTime = board->getTime();

   e->setVelocidad(25.f);

   /* COMPROBAMOS LA DISTANCIA A LA QUE ESTA LA ALARMA Y AVANZAMOS HACIA ELLA */
   
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
    	   /* RELOJ ACTIVACION ALARMA */
        this->startClock();                                 // INICIAMOS EL RELOJ (O RESEATEAMOS)

        int duration = reloj.getElapsedTime().asSeconds();  // OBTENEMOS SU DURACION EN SEGUNDOS

        //cout<<duration<<endl;

    	if(duration > 2)        // TIEMPO QUE TARDA EN ACTIVARLA
    	{
    		a->setActivado(true);
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
    contador = 0;
}

ActivarAlarma::~ActivarAlarma()
{
    board = nullptr;
    a = nullptr;
    enemigoNode = nullptr;

   // delete board;
    //delete a;
}