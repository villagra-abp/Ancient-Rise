#include "../headerfiles/AvanzarPatrulla.h"





Status AvanzarPatrulla::run(Enemigo *e)
{
    protaPosition = board->getProta();

    pos = e->getPosicion();

    Posicion* EnemigoPosition = e->getPosition(); // VOLVEMOS A OBTENER EL VECTOR DE POSICION DEL ENEMIGO POR SI HA CAMBIADO
    float enemigoX=EnemigoPosition->getPosX();

    nodoPosition = pos[contadorPatrulla]->getPosition();
    float posPatrullaX = nodoPosition->getPosX();

    int distanciaNodoX= posPatrullaX - enemigoX;     // DISTANCIA EN X AL NODO DE LA PATRULLA

    e->setCombate(false);

    if(distanciaNodoX==0) // ESTAMOS EN UN NODO DEL VECTOR DE PATRULLA
    {
        aristSal = pos[contadorPatrulla]->getAristasS();

        if(contadorPatrulla==pos.size()-1) // Si llegamos al final reiniciamos
        {
            recorrerAristas(0);
            contadorPatrulla = 0;
                    
        }
        else {
                recorrerAristas(contadorPatrulla+1);
                contadorPatrulla++;
            }
            
    }
    else{  // AUN NO HEMOS LLEGADO A NINGUN NODO DE LA PATRULLA

            if(tipoComp == NORMAL)          // Si el tramo entre los nodos es un camino normal, se mueve normal
            {
                if (distanciaNodoX<0) // AVANZAMOS HACIA LA IZQUIERDA
                {
                    e->getBody()->SetLinearVelocity(-(e->getVelocidad2d()));    // Velocidad Normal

                    e->setLastFacedDir(false);                                    // INDICAMOS QUE EL ENEMIGO ESTA MIRANDO A LA IZQUIERDA                           

                }
                else{
                    if(distanciaNodoX>0) // AVANZAMOS HACIA LA DERECHA
                    {
                        e->getBody()->SetLinearVelocity(e->getVelocidad2d());
                        
                        e->setLastFacedDir(true);                                // INDICAMOS QUE EL ENEMIGO ESTA MIRANDO A LA DERECHA  
                    }
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
/* FUNCION PARA RECORRER LOS ARISTAS DEL NODO EN EL QUE SE ENCUENTRA EL ENEMIGO
Y OBTENER EL COMPORTAMIENTO DE LA ARISTA CORRESPONDIENTE */
void AvanzarPatrulla::recorrerAristas(int num)
{
    for(int i=0;i<aristSal.size();i++)
    {
        if(aristSal[i]->getNodoInicio()==pos[contadorPatrulla] && aristSal[i]->getNodoFin()==pos[num])  // Buscamos la arista correspondiente al camino que esta recorriendo el enemigo
        {
            tipoComp = aristSal[i]->getComportamiento();
        }
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

    for(int cont=0; cont<aristSal.size();cont++)
    {
        aristSal[cont] = nullptr;
    }

}


AvanzarPatrulla::~AvanzarPatrulla()
{
   board  = nullptr;

    for(int cont=0; cont<pos.size();cont++)
    {
        pos[cont] = nullptr;
    }
    pos.clear();

    for(int cont=0; cont<aristSal.size();cont++)
    {
        aristSal[cont] = nullptr;
    }
    aristSal.clear();;

}
