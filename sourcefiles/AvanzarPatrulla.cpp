#include "../headerfiles/AvanzarPatrulla.h"



Status AvanzarPatrulla::run(Enemigo *e)
{
    pos = e->getPosicion();

    enemigoX = e->getPosition()->getPosX();
    enemigoY = e->getPosition()->getPosY();

    float posPatrullaX = pos[contadorPatrulla]->getPosX();

    int distanciaNodoX= posPatrullaX - enemigoX;     // DISTANCIA EN X AL NODO DE LA PATRULLA

    e->setCombate(false);

    if(e->getInterrumpido()==true)      // Si han interrumpido al enemigo durante su camino de vuelta, lo vuelve a calcular desde donde se encuentre
    {
        reset(e);
        e->setInterrumpido(false);
    }

    if(e->getVuelta()==false)       // Ya se encuentra en la patrulla
    {
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
    else        // VOLVIENDO A LA PATRULLA
    {
        nodos = board->getNodosGrafo();

        /* Buscamos el nodo Inicial mas cercano al enemigo */
        if(inicio1==nullptr && inicio2==nullptr)  // Solo buscaremos el nodo inicio si no lo habiamos encontrado ya
        {
            buscarNodoInicial(e, enemigoX);
        }  

        if(fin==nullptr)
        {
            buscarNodoFinal(e);
        }

        /* Calculamos el camino mas corto entre el nodo Inicial (inicioBueno) y el nodo Final que sera en la pos de la patrulla en la que nos quedamos */
        if(caminoCorto.size()==0)           // Para calcular el camino solo 1 vez y no siempre
        {
            g = new Grafo();
            caminoCorto = g->pathfindDijkstra(inicioBueno, fin);
            delete g;
        }

        /* Nos acercamos al nodo Inicio del camino */
        posNodoI = inicioBueno->getPosition();
        float distNodoI = posNodoI->getPosX() - enemigoX;

        if(llegadoInicio==false)        // Solo lo haremos si no habiamos llegado ya al nodo Inicio del camino
        {
            if(distNodoI<-1.0f)
             {
                    movimientoDireccion(e,false);                             
             }
             else{
                    if(distNodoI>1.0f) 
                    {
                        movimientoDireccion(e,true);                                  
                    }
                    else // Si hemos llegado al nodo Inicio
                    {
                        llegadoInicio = true;
                    }
                }
        }

        /* Realizamos el recorrido a lo largo del camino corto calculado */
        if(llegadoFin==false && llegadoInicio==true && caminoCorto.size()!=0)
        {
            if(iC<caminoCorto.size())
            {
                checkComportamiento(e);       // Comprobamos que comportamiento tiene que ejecutar el enemigo
            }

            if(iC==caminoCorto.size())
            {
               llegadoFin = true;
               iC = 0;

               e->setVuelta(false);
               reset(e);
            }
        }

        if(caminoCorto.size()==0)       // Solo si no calculamos el camino corto por estar al lado
        {
            if (distanciaNodoX<-3.0f) // AVANZAMOS HACIA LA IZQUIERDA
             {
                  e->getBody()->SetLinearVelocity(-(e->getVelocidad2d()));               // Velocidad Normal
                  e->setLastFacedDir(false);                                             
             }
             else{
                    if(distanciaNodoX>3.0f) // AVANZAMOS HACIA LA DERECHA
                    {
                      e->getBody()->SetLinearVelocity(e->getVelocidad2d());
                      e->setLastFacedDir(true);                                    
                    }
                    else // Si hemos llegado
                    {
                        e->setVuelta(false);        // Indicamos que la vuelta ya ha terminado
                        reset(e);
                    }
                }
        }
        
   }

   return BH_SUCCESS;
}

/* Metodo para buscar el nodo inicial visible del grafo mas cercano desde la pos del enemigo, siempre y cuando no lo hayamos encontrado ya antes */
void AvanzarPatrulla::buscarNodoInicial(Enemigo *e, float posX)
{
    recorrerNodos(e,1, posX);

    if(e->getLastFaceDir()==true)                      // Comprobamos a donde esta mirando el enemigo y hacemos que mire al lado contrario
    {   
        e->setLastFacedDir(false);
    } 
    else
    {   
        e->setLastFacedDir(true);
    }

    e->actualizarVistos();                               // Como hemos cambiado la direccion de la vista, actualizamos los gameobjects que puede ver

    recorrerNodos(e,2, posX);

    if(inicio1==nullptr && inicio2==nullptr)
    {
        cout<<"Error. El enemigo no ha visto ningun nodo de Inicio"<<endl;
    }

    if(inicio1!=nullptr && inicio2!=nullptr)            // Si encontramos nodos en ambas direcciones, comparamos para ver quien es el que esta mas cerca
    {
        inicioBueno = calcularNodoMasCercano(inicio1, inicio2, posX);
    }
    else
    {
        if(inicio1!=nullptr)
        {
            inicioBueno = inicio1;
        }
       else
       {
            inicioBueno = inicio2;
       }
    }   
}

void AvanzarPatrulla::buscarNodoFinal(Enemigo* e)
{
    
    for(int i=0; i<nodos.size(); i++)
    {
        if(pos[contadorPatrulla]->getPosY() == nodos[i]->getPosition()->getPosY() && pos[contadorPatrulla]->getPosX() == nodos[i]->getPosition()->getPosX())
        {
            fin = nodos[i];
        }
    }
}

/* Funcion para recorrer todos los nodos del grafo y comprobar si el enemigo puede ver alguno */
void AvanzarPatrulla::recorrerNodos(Enemigo* e, uint8_t v, float posX)
{

    for(int i=0; i<nodos.size();i++)
    {
        if(e->see(nodos[i]))            // Comprobamos si el enemigo ve al nodo
        {   
            if(v==1)
            {
                if(inicio1==nullptr)         
                {    
                    inicio1 = nodos[i];
                }
                else        // Si ya habia un nodo inciio guardado entonces hay que comprobar cual esta mas cerca
                {
                    inicio1=calcularNodoMasCercano(inicio1, nodos[i], posX);
                }
            }
            else
            {
                //cout<<"segunda"<<endl;
                if(inicio2==nullptr)
                {   
                    inicio2= nodos[i];
                }
                else
                {
                    inicio2=calcularNodoMasCercano(inicio2, nodos[i], posX);
                }
            }
        }
    }
}

/* Funcion para calcular que nodo visible del grafo esta mas cerca del enemigo */
NodoGrafo* AvanzarPatrulla::calcularNodoMasCercano(NodoGrafo* i, NodoGrafo* i2, float posX)
{
    posNodo = i2->getPosition();                            // Pos del nuevo nodo encontrado
    posNodoI = i->getPosition();                           // Pos del nodo que ya habiamos almacenado antes

    float nodoIX = posNodoI->getPosX();
    float nodoX = posNodo->getPosX();

    /* Calculamos las distancias de los nodos al enemigo */
    float distanciaNodoI = nodoIX - posX;
    float distanciaNodo = nodoX - posX;

    if(abs(distanciaNodoI)>abs(distanciaNodo))          // Comprobamos que nodo esta mas cerca, si el que ya habiamos guardado o el nuevo que hemos visto
    {
        i = i2;                                   // Si el nuevo nodo esta mas cerca, lo almacenamos
    }

    return i;
}

/* FUncion para especificar la velocidad y direccion de movimiento del enemigo */
void AvanzarPatrulla::movimientoDireccion(Enemigo *e, bool d)
{
    if(d==false)   // Izquierda
    {
      e->getBody()->SetLinearVelocity(-(e->getVelocidad2d()));               // Velocidad Normal
      e->getBody()->ApplyForceToCenter(b2Vec2(-300.f,0.f),true);             // Fuerza para correr

      e->setLastFacedDir(d); 
    }
    else  // Derecha
    {
        e->getBody()->SetLinearVelocity(e->getVelocidad2d());
        e->getBody()->ApplyForceToCenter(b2Vec2(300.f,0.f),true);          

        e->setLastFacedDir(d);   
    }
}

void AvanzarPatrulla::startClock()
{
    if(contadorReloj==0)
    {
        reloj.restart();
        contadorReloj = contadorReloj +1;
    }
}

/* Funcion para que el enemigo sepa que comportamiento tiene que hacer durante el pathfinding */
void AvanzarPatrulla::checkComportamiento(Enemigo *e)
{
    fin = caminoCorto[iC]->getNodoFin();

    tipo = caminoCorto[iC]->getComportamiento();

    switch(tipo)
    {
       case NORMAL:
       {
         posNodoI = fin->getPosition();
         distNodoF = posNodoI->getPosX() - enemigoX;

          if (distNodoF<-1.0f) 
          {
              movimientoDireccion(e,false);                                   
          }
          else{
                if(distNodoF>1.0f) 
                {
                    movimientoDireccion(e,true);                                    
                }
                else
                {
                    iC++;
                }
              }

         break;
       }

       case SALTO:
       {
          posNodoI = fin->getPosition();
          distNodoF = posNodoI->getPosX() - enemigoX;
          distNodoFY = posNodoI->getPosY() - enemigoY;
            
          if(distNodoFY>1.0f)
          {
            e->setSaltando(true);
            e->getBody()->ApplyForceToCenter(b2Vec2(0.f,3000.f),true);
          }
          else
         {
            e->setSaltando(false);
         }

          if(e->getSaltando()!=true)
          {
            if(distNodoF<-1.0f) // AVANZAMOS HACIA LA IZQUIERDA
            {
              e->getBody()->SetLinearVelocity(-(e->getVelocidad2d()));               // Velocidad Normal
              e->setLastFacedDir(false);                                    
            }
            else{
                  if(distNodoF>1.0f) // AVANZAMOS HACIA LA DERECHA
                  {

                    e->getBody()->SetLinearVelocity(e->getVelocidad2d());
                    e->setLastFacedDir(true);                                    
                  }
                  else // Si hemos llegado al nodo Fin
                  {
                    iC++;
                  }
                }
          }

        break;
       }

       case BAJADA:
       {
         posNodoI = fin->getPosition();
        distNodoF = posNodoI->getPosX() - enemigoX;
        distNodoFY = posNodoI->getPosY() - enemigoY;

          if (distNodoF<-3.0f) 
          {
            e->getBody()->SetLinearVelocity(-(e->getVelocidad2d()));
            bajada = false;                                   
          }
          else{
                if(distNodoF>3.0f) 
                {
                  e->getBody()->SetLinearVelocity(e->getVelocidad2d());
                  bajada = false;                                    
                }
                else
                {
                  bajada = true;
                }
              }

              if(bajada == true)
              {
                if(distNodoFY<-1.0f)
                {
                  e->getBody()->ApplyForceToCenter(b2Vec2(0.f,-3000.f),true);
                }
                else
                {
                  iC++;
                }
              }
        break;
       }

    }
}

void AvanzarPatrulla::reset(Enemigo *e)
{
    /* Inicializamos todo otra vez para que la proxima vez que ocurra funcione todo bien */
    llegadoFin = false;
    llegadoInicio = false;
    inicio1 = nullptr;
    inicio2 = nullptr;
    fin = nullptr;
    caminoCorto.clear();
    inicioBueno = nullptr;
    bajada = false;

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

    bajada = false;

     /* Pathfinding */
   inicio1 = nullptr;
   inicio2 = nullptr;
   inicioBueno = nullptr;
   fin = nullptr;
   posNodo = nullptr;
   posNodoI = nullptr;
   g = new Grafo();
   iC = 0;
}


AvanzarPatrulla::~AvanzarPatrulla()
{
    board  = nullptr;

    for(int cont=0; cont<pos.size();cont++)
    {
        pos[cont] = nullptr;
    }

    pos.clear();

    delete g;
}