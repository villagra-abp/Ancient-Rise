#include "../headerfiles/BuscarComida.h"



Status BuscarComida::run(Enemigo *e)
{
    // DATOS DEL ENEMIGO
    enemigoNode = e->getNode();
    Posicion* EnemigoPosition = e->getPosition(); 
    float enemigoX=EnemigoPosition->getPosX();

    //BUSCAR COMIDA MAS CERCANA
    comidaPosition = c[0]->getVector3df();
    comidaX = comidaPosition->getPosX();
    distanciaComida = comidaX - enemigoX;  // Calculamos la distancia hasta la fuente
    int pos = 0;

       for (int i = 1; i < c.size(); i++){
          
          comidaPosition = c[i]->getVector3df();
          comidaX=comidaPosition->getPosX();

          distanciaCaux = comidaX - enemigoX;

          if( abs(distanciaCaux) < abs(distanciaComida)) {
            distanciaComida = distanciaCaux;
            pos = i;
          }
       }

    e->setCombate(false);

    if (distanciaComida<0) // AVANZAMOS HACIA LA IZQUIERDA
     {
         e->getBody()->SetLinearVelocity(-(e->getVelocidad2d()));               // Velocidad Normal
        e->getBody()->ApplyForceToCenter(b2Vec2(-300.f,0.f),true);             // Fuerza para correr

        e->setLastFacedDir(false); 
     }
     else{
            if(distanciaComida>0) // AVANZAMOS HACIA LA DERECHA
            {
                e->getBody()->SetLinearVelocity(e->getVelocidad2d());
                e->getBody()->ApplyForceToCenter(b2Vec2(300.f,0.f),true);             // Fuerza para correr

                e->setLastFacedDir(true);   
            }
            else // Si hemos llegado
            {
                 /* RELOJ COMER */
                 this->startClock();                             // INICIAMOS EL RELOJ (O RESEATEAMOS)

                 int time = reloj.getElapsedTime().asSeconds();  // OBTENEMOS SU DURACION EN SEGUNDOS

                  c[pos]->setActivando(true);

                 if(time>2)     // COMIENDO
                 {
                     e->setHambre(100.f);       // RECUPERAMOS HAMBRE
                     c[pos]->setActivando(true);
                     contador  = 0;
                 }
            }
        }

    return BH_SUCCESS;

}

void BuscarComida::startClock()
{
    if(contador==0)
    {
        reloj.restart();
        contador = contador +1;
    }
}

void BuscarComida::onInitialize(Blackboard *b)
{
   c = b->getComida();
   board = b;
}


BuscarComida::~BuscarComida()
{
    board = nullptr;
    enemigoNode = nullptr;
    comidaNode = nullptr;

    for(int i = 0 ; i < c.size(); i++){
      c[i] = nullptr;
      delete c[i];  //No se si es necesario
    }

    c.clear();

    //delete board;
    //delete c;
}
