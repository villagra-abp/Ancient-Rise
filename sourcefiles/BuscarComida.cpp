#include "../headerfiles/BuscarComida.h"



Status BuscarComida::run(Enemigo *e)
{
     e->setCombate(false);

    // DATOS DEL ENEMIGO
    Posicion* EnemigoPosition = e->getPosition(); 
    float enemigoX=EnemigoPosition->getPosX();
    float enemigoY = EnemigoPosition->getPosY();

    nodos = board->getNodosGrafo();

    /* Buscamos el nodo Inicial mas cercano al enemigo */
    if(inicio1==nullptr && inicio2==nullptr)  // Solo buscaremos el nodo inicio si no lo habiamos encontrado ya
    {
        buscarNodoInicial(e, enemigoX);
    }

    /* BUSCAR COMIDA MAS CERCANA */
    buscarComidaCercana(enemigoX);

    /* Buscamos el nodo mas cercano a la comida elegida para ir */
    if(fin==nullptr)        // Solo si no lo habiamos encontrado ya
    {
       comidaX = c[pos]->getVector3df()->getPosX();
       comidaY = c[pos]->getVector3df()->getPosY();
       for(int i=0; i<nodos.size();i++)
       {    
           posNodo = nodos[i]->getPosition();
           if(comidaY==posNodo->getPosY())        // Solo si el nodo esta a la misma altura que la pos de la comida
           {
                if(fin==nullptr)
                {
                    fin = nodos[i];
                }
                else        // Comprobamos si no hay un nodo mas cercano a la fuente
                {
                    fin = calcularNodoMasCercano(fin, nodos[i], comidaX);
                }
           }
       }
    }

    /* Calculamos el camino mas corto entre el nodo Inicial (inicioBueno) y el nodo Final (fin) */
    if(caminoCorto.size()==0)           // Para calcular el camino solo 1 vez y no siempre
    { 
        g = new Grafo();
        caminoCorto = g->pathfindDijkstra(inicioBueno, fin);
       
    }

    /* Nos acercamos al nodo Inicio del camino */
    posNodoI = inicioBueno->getPosition();
    distNodoI = posNodoI->getPosX() - enemigoX;
    
    if(llegadoInicio==false)        // Solo lo haremos si no habiamos llegado ya al nodo Inicio del camino
    {
        if (distNodoI<-5.0f) // AVANZAMOS HACIA LA IZQUIERDA
         {
            movimientoDireccion(e,false);                                      
         }
         else{
                if(distNodoI>5.0f) // AVANZAMOS HACIA LA DERECHA
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
            fin = caminoCorto[iC]->getNodoFin();

            if(caminoCorto[iC]->getComportamiento()==NORMAL)         // Movimiento normal del enemigo
            {   
                posNodoI = fin->getPosition();
                distNodoF = posNodoI->getPosX() - enemigoX;
              
                if (distNodoF<-5.0f) 
                 {
                     movimientoDireccion(e,false);                             
                 }
                 else{
                        if(distNodoF>5.0f) 
                        {
                            movimientoDireccion(e,true);                                   
                        }
                        else
                        {
                          iC++;
                        }
                    }
            }
            else
            {
                if(caminoCorto[iC]->getComportamiento()==SALTO)         // SALTO
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

                }
            }
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
      
        if (distanciaComida<4.0f) // AVANZAMOS HACIA LA IZQUIERDA
         {
             e->getBody()->SetLinearVelocity(-(e->getVelocidad2d()));               // Velocidad Normal
             e->setLastFacedDir(false);                
         }
         else{
                if(distanciaComida>4.0f) // AVANZAMOS HACIA LA DERECHA
                {
                   e->getBody()->SetLinearVelocity(e->getVelocidad2d());
                   e->setLastFacedDir(true); 
                }
                else // Si hemos llegado
                {
                     /* RELOJ COMER */
                     startClock();                             // INICIAMOS EL RELOJ (O RESEATEAMOS)

                     int time = reloj.getElapsedTime().asSeconds();  // OBTENEMOS SU DURACION EN SEGUNDOS

                      c[pos]->setActivando(true);

                     if(time>2)     // COMIENDO
                     {
                         e->setHambre(100.f);       // RECUPERAMOS HAMBRE
                         c[pos]->setActivando(false);
                         contador  = 0;

                          /* Inicializamos todo otra vez para que la proxima vez que ocurra funcione todo bien */
                         llegadoFin = false;
                         llegadoInicio = false;
                         inicio1 = nullptr;
                         inicio2 = nullptr;
                         fin = nullptr;
                         caminoCorto.clear();
                         inicioBueno = nullptr;

                         //cout<<"COMIENDO LOCO"<<endl;
                     }
                }
            }
    }

    return BH_SUCCESS;

}

/* Metodo para buscar el nodo inicial visible del grafo mas cercano desde la pos del enemigo, siempre y cuando no lo hayamos encontrado ya antes */
void BuscarComida::buscarNodoInicial(Enemigo *e, float posX)
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
void BuscarComida::recorrerNodos(Enemigo* e, uint8_t v, float posX)
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
NodoGrafo* BuscarComida::calcularNodoMasCercano(NodoGrafo* i, NodoGrafo* i2, float posX)
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

void BuscarComida::buscarComidaCercana(float posEnemX)
{
    comidaPosition = c[0]->getVector3df();
    comidaX = comidaPosition->getPosX();
    distanciaComida = comidaX - posEnemX;  // Calculamos la distancia hasta la comida
    pos = 0;

       for (int i = 1; i < c.size(); i++){
          
          comidaPosition = c[i]->getVector3df();
          comidaX= comidaPosition->getPosX();
          comidaY = comidaPosition->getPosY();

          distanciaCaux = comidaX - posEnemX;

          if( abs(distanciaCaux) < abs(distanciaComida)) {
            distanciaComida = distanciaCaux;
            pos = i;
          }
       }

}

void BuscarComida::startClock()
{
    if(contador==0)
    {
        reloj.restart();
        contador = contador +1;
    }
}

/* FUncion para especificar la velocidad y direccion de movimiento del enemigo */
void BuscarComida::movimientoDireccion(Enemigo *e, bool d)
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

void BuscarComida::onInitialize(Blackboard *b)
{
   c = b->getComida();
   board = b;

   inicio1 = nullptr;
   inicio2 = nullptr;
   inicioBueno = nullptr;
   fin = nullptr;
   posNodo = nullptr;
   posNodoI = nullptr;
   iC = 0;

   g = new Grafo();
}


BuscarComida::~BuscarComida()
{
    board = nullptr;

    for(int i = 0 ; i < c.size(); i++){
      c[i] = nullptr;
    }
    c.clear();

    for(int i=0; i<caminoCorto.size();i++)
    {
        caminoCorto[i] = nullptr;
    }
    caminoCorto.clear();

    delete g;
}
