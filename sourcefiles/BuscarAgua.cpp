#include "../headerfiles/BuscarAgua.h"



Status BuscarAgua::run(Enemigo *e)
{
    // DATOS DEL ENEMIGO
	enemigoNode = e->getNode();
    core::vector3df EnemigoPosition = enemigoNode->getPosition(); 
    float enemigoX=EnemigoPosition.X;

    // DATOS DE LA FUENTE
    fuenteNode = f->getObjeto();
    core::vector3df fuentePosition = fuenteNode->getPosition(); 
    float fuenteX=fuentePosition.X;

    int distanciaFuente = fuenteX - enemigoX;  // Calculamos la distancia hasta la fuente

    frameDeltaTime = board->getTime();

    e->setVelocidad(25.f);

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
    f = nullptr;
    enemigoNode = nullptr;
    fuenteNode = nullptr;

    //delete board;
    //delete f;
}