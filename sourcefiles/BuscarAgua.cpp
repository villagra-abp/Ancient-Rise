#include "../headerfiles/BuscarAgua.h"



Status BuscarAgua::run(Enemigo *e)
{   
    // DATOS DEL ENEMIGO
    enemigoNode = e->getNode();
    Posicion* EnemigoPosition = e->getPosition(); 
    float enemigoX=EnemigoPosition->getPosX();

    //BUSCAR FUENTE MAS CERCANA
    fuentePosition = f[0]->getVector3df();
    fuenteX = fuentePosition->getPosX();
    distanciaFuente = fuenteX - enemigoX;  // Calculamos la distancia hasta la fuente
    int pos = 0;

       for (int i = 1; i < f.size(); i++){
          
          fuentePosition = f[i]->getVector3df();
          fuenteX=fuentePosition->getPosX();

          distanciaFaux = fuenteX - enemigoX;

          if( abs(distanciaFaux) < abs(distanciaFuente)) {
            distanciaFuente = distanciaFaux;
            pos = i;
          }
       }
    
    e->setCombate(false);

    if (distanciaFuente<0) // AVANZAMOS HACIA LA IZQUIERDA
     {

            e->getBody()->SetLinearVelocity(-(e->getVelocidad2d()));               // Velocidad Normal
            e->getBody()->ApplyForceToCenter(b2Vec2(-300.f,0.f),true);             // Fuerza para correr

            e->setLastFacedDir(false);                                    
     }
     else{
            if(distanciaFuente>0) // AVANZAMOS HACIA LA DERECHA
            {

                e->getBody()->SetLinearVelocity(e->getVelocidad2d());
                e->getBody()->ApplyForceToCenter(b2Vec2(300.f,0.f),true);             // Fuerza para correr

                e->setLastFacedDir(true);                                    
            }
            else // Si hemos llegado
            {
                  /* RELOJ BEBER AGUA */
                 this->startClock();                             // INICIAMOS EL RELOJ (O RESEATEAMOS)

                 int time = reloj.getElapsedTime().asSeconds();  // OBTENEMOS SU DURACION EN SEGUNDOS

                 f[pos]->setActivando(true);                         // ENEMIGO BEBIENDO

                 if(time>4)     // BEBIENDO
                 {
                     e->setSed(100.f);       // RECUPERAMOS SED
                     f[pos]->setActivando(false);
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