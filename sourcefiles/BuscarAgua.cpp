#include "../headerfiles/BuscarAgua.h"

Status BuscarAgua::run(Enemigo *e)
{   
    e->setCombate(false);

    checkVelocidad(e);

    // DATOS DEL ENEMIGO
    Posicion* EnemigoPosition = e->getPosition(); 
    enemigoX =EnemigoPosition->getPosX();
    enemigoY =EnemigoPosition->getPosY(); 

    /* Buscamos el nodo Inicial mas cercano al enemigo */
    if(inicio1==nullptr && inicio2==nullptr)  // Solo buscaremos el nodo inicio si no lo habiamos encontrado ya
    {
        buscarNodoInicial(e, enemigoX);
       //cout<<"INICIOBUENO "<<inicioBueno->getNombre()<<endl;
    }
       
    /* BUSCAR FUENTE MAS CERCANA */
      buscarFuenteCercana(enemigoX);

     /* Buscamos el nodo mas cercano a la fuente elegida para ir */
    if(fin==nullptr)        // Solo si no lo habiamos encontrado ya
    {
       fuenteX = f[pos]->getVector3df()->getPosX();
       fuenteY = f[pos]->getVector3df()->getPosY();
       for(size_t i=0; i<nodos.size();i++)
       {    
           posNodo = nodos[i]->getPosition();
           if(fuenteY<posNodo->getPosY()+10 && fuenteY>posNodo->getPosY()-10)        // Solo si el nodo esta a la misma altura que la pos de la fuente
           {
                if(fin==nullptr)
                {
                    fin = nodos[i];
                }
                else        // Comprobamos si no hay un nodo mas cercano a la fuente
                {
                    fin = calcularNodoMasCercano(fin, nodos[i], fuenteX);
                }
           }
       }
    }

     /* Calculamos el camino mas corto entre el nodo Inicial (inicioBueno) y el nodo Final (fin) */
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
        }
    }

    // Hemos llegado al ultimo nodo del camino calculado o hemos llegado al inicio y ademas no hay camino corto, puesto que ya estamos en el nodo mas cercano al objetivo
    if((llegadoFin==true) || (llegadoInicio==true && caminoCorto.size()==0))
    {
        if (distanciaFuente<-3.0f) // AVANZAMOS HACIA LA IZQUIERDA
         {
            e->getBody()->SetLinearVelocity(-(e->getVelocidad2d()));               // Velocidad Normal
            e->setLastFacedDir(false);                                             
         }
         else{
                if(distanciaFuente>3.0f) // AVANZAMOS HACIA LA DERECHA
                {
                  e->getBody()->SetLinearVelocity(e->getVelocidad2d());
                  e->setLastFacedDir(true);                                    
                }
                else // Si hemos llegado
                {   
                    e->setVelocidad(e->getVelNormal());             // Para que no gaste energia cuando llegue

                      /* RELOJ BEBER AGUA */
                    startClock();                                       // INICIAMOS EL RELOJ (O RESEATEAMOS)

                    int time = reloj.getElapsedTime().asSeconds();      // OBTENEMOS SU DURACION EN SEGUNDOS

                    f[pos]->setActivando(true);                         // ENEMIGO BEBIENDO

                    if(time>4)     // BEBIENDO
                    {
                    //cout<<"BEBIENDO"<<endl;
                      e->setSed(100.f);                               // RECUPERAMOS SED
                      e->setVuelta(true);                             // Indicamos que estamos volviendo a la patrulla
                      f[pos]->setActivando(false);
                      contador  = 0;
                      reset();
                    }
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

/* Metodo para buscar el nodo inicial visible del grafo mas cercano desde la pos del enemigo, siempre y cuando no lo hayamos encontrado ya antes */
void BuscarAgua::buscarNodoInicial(Enemigo *e, float posX)
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

/* Funcion para recorrer todos los nodos del grafo y comprobar si el enemigo puede ver alguno */
void BuscarAgua::recorrerNodos(Enemigo* e, uint8_t v, float posX)
{
 /* if(e->getLastFaceDir()==true)
  {
    cout<<"DERECHA"<<endl;
  }
  else
  {
    cout<<"IZQUIERDA"<<endl;
  }*/
    for(size_t i=0; i<nodos.size();i++)
    {
        
        if(e->see(nodos[i]))            // Comprobamos si el enemigo ve al nodo
        {   
           //cout<<"Nodo X "<<nodos[i]->getPosition()->getPosX()<<endl;
           //cout<<"Nodo ID "<<nodos[i]->getNombre()<<endl;
           //cout<<"Enemigo X "<<e->getPosition()->getPosX()<<endl;
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
NodoGrafo* BuscarAgua::calcularNodoMasCercano(NodoGrafo* i, NodoGrafo* i2, float posX)
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

void BuscarAgua::buscarFuenteCercana(float posEnemX)
{
    fuentePosition = f[0]->getVector3df();
    fuenteX = fuentePosition->getPosX();

    distanciaFuente = fuenteX - posEnemX;  // Calculamos la distancia hasta la fuente
    pos = 0;

       for (size_t i = 1; i < f.size(); i++){
          
          fuentePosition = f[i]->getVector3df();
          fuenteX=fuentePosition->getPosX();
          fuenteY = fuentePosition->getPosY();

          distanciaFaux = fuenteX - posEnemX;

          if( abs(distanciaFaux) < abs(distanciaFuente)) {
            distanciaFuente = distanciaFaux;
            pos = i;
          }
       }

}
/* FUncion para especificar la velocidad y direccion de movimiento del enemigo */
void BuscarAgua::movimientoDireccion(Enemigo *e, bool d)
{
    if(d==false)   // Izquierda
    {
      e->getBody()->SetLinearVelocity(-(e->getVelocidad2d()));               // Obtenemos la velocidad del enemigo

      e->setLastFacedDir(d); 
    }
    else  // Derecha
    {
        e->getBody()->SetLinearVelocity(e->getVelocidad2d());     

        e->setLastFacedDir(d);   
    }
}

/* Funcion para que el enemigo sepa que comportamiento tiene que hacer durante el pathfinding */
void BuscarAgua::checkComportamiento(Enemigo *e)
{
    fin = caminoCorto[iC]->getNodoFin();

    tipo = caminoCorto[iC]->getComportamiento();

    posNodoI = fin->getPosition();
    distNodoF = posNodoI->getPosX() - enemigoX;
    distNodoFY = posNodoI->getPosY() - enemigoY;

    switch(tipo)
    {
       case NORMAL:
       {
        //cout<<"NORMAL"<<endl;
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
        //cout<<"SALTO"<<endl;
          if(distNodoFY>1.0f)
          {
            e->setSaltando(true);
            e->getBody()->ApplyForceToCenter(b2Vec2(0.f,350000.f),true);
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
        //cout<<"BAJADA"<<endl;
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
                if(distNodoFY<-5.0f)
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

       case SALTO_GRANDE:
       {
        //cout<<"SALTO GRANDE"<<endl;
          if(distNodoFY>1.0f)
          {
            e->setSaltando(true);
            e->getBody()->ApplyForceToCenter(b2Vec2(0.f,500000.f),true);
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

    }
}

/* Funcion para cambiar la velocidad del enemigo en funcion de su energia */
void BuscarAgua::checkVelocidad(Enemigo *e)
{

  if(e->getEnergia()>=0 && e->getRecargandoEnerg()==false)    // SI queda energia que gastar y no se esta recargando
  {
    e->setVelocidad(e->getVelRapida());
  }
  else // Sin energia reduccion de velocidad
  {
    e->setVelocidad(e->getVelNormal());
  }

}

void BuscarAgua::reset()
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

void BuscarAgua::onInitialize(Blackboard *b)
{
   /* INfo fuente */
   f = b->getFuente();

   fuentePosition = nullptr;

   board = b;
   contador = 0;

   /* Pathfinding */
   nodos = board->getNodosGrafo();
   inicio1 = nullptr;
   inicio2 = nullptr;
   inicioBueno = nullptr;
   fin = nullptr;
   posNodo = nullptr;
   posNodoI = nullptr;
   iC = 0;
   bajada = false;

}


BuscarAgua::~BuscarAgua()
{
   board = nullptr;
   inicio2 = nullptr;
   inicio1 = nullptr;
   inicioBueno = nullptr;
   fin = nullptr;
   posNodo = nullptr;
   posNodoI = nullptr;

    for(size_t i = 0 ; i < f.size(); i++){
      f[i] = nullptr;
    }
    f.clear();

    for(size_t i=0; i<caminoCorto.size();i++)
    {
        caminoCorto[i] = nullptr;
    }
    caminoCorto.clear();

    for(size_t i=0; i<nodos.size();i++)
    {
        nodos[i] = nullptr;
    }
    nodos.clear();
}
