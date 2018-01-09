#include "../headerfiles/AvanzarPatrulla.h"





Status AvanzarPatrulla::run(Enemigo *e)
{
    
    protaPosition = board->getProta();

    pos = e->getPosicion();

    enemigoNode = e->getNode();
    core::vector3df EnemigoPosition = enemigoNode->getPosition(); // VOLVEMOS A OBTENER EL VECTOR DE POSICION DEL ENEMIGO POR SI HA CAMBIADO
    float enemigoX=EnemigoPosition.X;

    float posPatrullaX = pos[contadorPatrulla]->getPosX();

    int distanciaNodoX= posPatrullaX - enemigoX;     // DISTANCIA EN X AL NODO DE LA PATRULLA

    frameDeltaTime = board->getTime();
    e->setVelocidad(e->getVelNormal());                                      // ACTUALIZAMOS LA VELOCIDAD DEL ENEMIGO

    if(distanciaNodoX==0) // SI ESTAMOS EN UNO DE LOS NODOS DE LA PATRULLA BUSCAMOS EL SIGUIENTE NODO
    {
        if(contadorPatrulla==pos.size()-1) // Si llegamos al final reiniciamos
        {
            contadorPatrulla = 0;
                    
        }
        else {
                contadorPatrulla++;
            }
    }
    else{  // AUN NO HEMOS LLEGADO A NINGUN NODO DE LA PATRULLA

            if (distanciaNodoX<0) // AVANZAMOS HACIA LA IZQUIERDA
            {
                EnemigoPosition.X-= e->getVelocidad() * frameDeltaTime*3;

                e->setPosition(EnemigoPosition); // CAMBIAMOS LA POSICION

                //e->getBody()->SetLinearVelocity(-(e->getVelocidad2d()));    // Velocidad Normal

                e->setLastFacedDir(false);                                    // INDICAMOS QUE EL ENEMIGO ESTA MIRANDO A LA IZQUIERDA                           

            }
            else{
                if(distanciaNodoX>0) // AVANZAMOS HACIA LA DERECHA
                {

                    EnemigoPosition.X+= e->getVelocidad() * frameDeltaTime*3;

                    e->setPosition(EnemigoPosition);

                    //e->getBody()->SetLinearVelocity(e->getVelocidad2d());
                    
                    e->setLastFacedDir(true);                                // INDICAMOS QUE EL ENEMIGO ESTA MIRANDO A LA DERECHA  
                }
            }
         }
         
   
   return BH_SUCCESS;
   

}

void AvanzarPatrulla::startClock()
{
    if(contadorReloj==0)
    {
        reloj.restart();
        contadorReloj = contadorReloj +1;
    }
}

void AvanzarPatrulla::onInitialize(Blackboard *b)
{
    contadorPatrulla=0;
    contadorReloj = 0;
    board = b;

    for(int cont=0; cont<pos.size();cont++)
    {
        pos[cont] = nullptr;
    }
}


AvanzarPatrulla::~AvanzarPatrulla()
{
    board  = nullptr;
    enemigoNode = nullptr;

    for(int cont=0; cont<pos.size();cont++)
    {
        pos[cont] = nullptr;
    }

    pos.clear();

}