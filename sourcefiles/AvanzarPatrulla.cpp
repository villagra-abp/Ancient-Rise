#include "../headerfiles/AvanzarPatrulla.h"





Status AvanzarPatrulla::run()
{
    
    protaPosition = board->getProta();
    frameDeltaTime = board->getTime();
    VELOCIDAD_ENEMIGO = board->getVel();

    scene::ISceneNode* enemigoNode = enemigo->getNode();

    core::vector3df EnemigoPosition = enemigoNode->getPosition(); // VOLVEMOS A OBTENER EL VECTOR DE POSICION DEL ENEMIGO POR SI HA CAMBIADO

    float enemigoX=EnemigoPosition.X;
    float posPatrullaX = pos[contadorPatrulla]->getPosX();

    int distanciaNodoX= posPatrullaX - enemigoX;     // DISTANCIA EN X AL NODO DE LA PATRULLA


    if(distanciaNodoX==0) // SI ESTAMOS EN UNO DE LOS NODOS DE LA PATRULLA BUSCAMOS EL SIGUIENTE NODO
    {
        
        if(contadorPatrulla==pos.size()-1) // Si llegamos al final reiniciamos
        {
            contadorPatrulla=0;

                    
        }
        else {
                contadorPatrulla++;
                    

            }
    }
    else{  // AUN NO HEMOS LLEGADO A NINGUN NODO DE LA PATRULLA

            if (distanciaNodoX<0) // AVANZAMOS HACIA LA IZQUIERDA
            {
                EnemigoPosition.X-= VELOCIDAD_ENEMIGO * frameDeltaTime*3;

                enemigo->setPosition(EnemigoPosition); // CAMBIAMOS LA POSICION

            }
            else{
                if(distanciaNodoX>0) // AVANZAMOS HACIA LA DERECHA
                {

                    EnemigoPosition.X+= VELOCIDAD_ENEMIGO * frameDeltaTime*3;

                    enemigo->setPosition(EnemigoPosition);
                }
            }
         }
         
   
   return BH_SUCCESS;
   

}

void AvanzarPatrulla::onInitialize(Blackboard *b)
{
    contadorPatrulla=0;
    enemigo = b->getEnem();
    pos = b->getPos();
    board = b;
}


AvanzarPatrulla::~AvanzarPatrulla()
{
    
}