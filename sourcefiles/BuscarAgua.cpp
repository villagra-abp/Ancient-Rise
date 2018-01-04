#include "../headerfiles/BuscarAgua.h"



Status BuscarAgua::run(Enemigo *e)
{
    
	frameDeltaTime = board->getTime();

    e->setVelocidad(25.f);

	scene::ISceneNode* enemigoNode = e->getNode();

    core::vector3df EnemigoPosition = enemigoNode->getPosition(); 

    float enemigoX=EnemigoPosition.X;

    scene::ISceneNode* fuenteNode = f->getObjeto();

    core::vector3df fuentePosition = fuenteNode->getPosition(); 

    float fuenteX=fuentePosition.X;

    int distanciaFuente = fuenteX - enemigoX;  // Calculamos la distancia hasta la fuente

    if (distanciaFuente<0) // AVANZAMOS HACIA LA IZQUIERDA
     {

                EnemigoPosition.X-= e->getVelocidad() * frameDeltaTime*3;

                e->setPosition(EnemigoPosition); // CAMBIAMOS LA POSICION
     }
     else{
            if(distanciaFuente>0) // AVANZAMOS HACIA LA DERECHA
            {

                EnemigoPosition.X+= e->getVelocidad() * frameDeltaTime*3;

                e->setPosition(EnemigoPosition);
            }
            else // Si hemos llegado
            {
                e->setSed(100.f);
            }
        }

    return BH_SUCCESS;

}


void BuscarAgua::onInitialize(Blackboard *b)
{
   f = b->getFuente();
   board = b;
}


BuscarAgua::~BuscarAgua()
{
    
}