#include "../headerfiles/BuscarAgua.h"



Status BuscarAgua::run(Enemigo *e)
{   
    // DATOS DEL ENEMIGO
	enemigoNode = e->getNode();
    core::vector3df EnemigoPosition = enemigoNode->getPosition(); 
    float enemigoX=EnemigoPosition.X;

    //BUSCAR FUENTE MAS CERCANA
    fuentePosition = f[0]->getVector3df();
    fuenteX = fuentePosition.X;
    distanciaFuente = fuenteX - enemigoX;  // Calculamos la distancia hasta la fuente

       for (int i = 1; i < f.size(); i++){
          
          fuentePosition = f[i]->getVector3df();
          fuenteX=fuentePosition.X;

          distanciaFaux = fuenteX - enemigoX;

          if( abs(distanciaFaux) < abs(distanciaFuente)) {
            distanciaFuente = distanciaFaux;
          }
       }
    

    frameDeltaTime = board->getTime();

    e->setVelocidad(25.f);
    e->setCombate(false);

    if (distanciaFuente<0) // AVANZAMOS HACIA LA IZQUIERDA
     {

            EnemigoPosition.X-= e->getVelocidad() * frameDeltaTime*3;

            e->setPosition(EnemigoPosition); // CAMBIAMOS LA POSICION

            e->setLastFacedDir(false);                                   
     }
     else{
            if(distanciaFuente>0) // AVANZAMOS HACIA LA DERECHA
            {

                EnemigoPosition.X+= e->getVelocidad() * frameDeltaTime*3;

                e->setPosition(EnemigoPosition);

                e->setLastFacedDir(true);                                    
            }
            else // Si hemos llegado
            {
                 /* RELOJ BEBER AGUA */
                 this->startClock();                             // INICIAMOS EL RELOJ (O RESEATEAMOS)

                 int time = reloj.getElapsedTime().asSeconds();  // OBTENEMOS SU DURACION EN SEGUNDOS

                 if(time>4)     // BEBIENDO
                 {
                     e->setSed(100.f);       // RECUPERAMOS SED
                     contador  = 0;
                 }
            }
        }

    return BH_SUCCESS;

}

void BuscarAgua::startClock()
{
    if(contador==0)
    {
        reloj.restart();
        contador = contador +1;
    }
}

void BuscarAgua::onInitialize(Blackboard *b)
{
   f = b->getFuente();
   board = b;
   contador = 0;
}


BuscarAgua::~BuscarAgua()
{
    board = nullptr;
    enemigoNode = nullptr;
    fuenteNode = nullptr;

    for(int i = 0 ; i < f.size(); i++){
      f[i] = nullptr;
      delete f[i];  //No se si es necesario
    }

    f.clear();

    //delete board;
    //delete f;
}