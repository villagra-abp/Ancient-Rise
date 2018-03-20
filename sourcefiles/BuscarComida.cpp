#include "../headerfiles/BuscarComida.h"



Status BuscarComida::run(Enemigo *e)
{
     e->setCombate(false);

    // DATOS DEL ENEMIGO
    Posicion* EnemigoPosition = e->getPosition(); 
    float enemigoX=EnemigoPosition->getPosX();

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
                    comidaPosition = c[pos]->getVector3df();
                    comidaX = comidaPosition->getPosX();
                    comidaY = comidaPosition->getPosX();
                    fin = calcularNodoMasCercano(fin, nodos[i], comidaX);
                }
           }
       }
    }

    /* Calculamos el camino mas corto entre el nodo Inicial (inicioBueno) y el nodo Final (fin) */
    if(caminoCorto.size()==0)           // Para calcular el camino solo 1 vez y no siempre
    {
        caminoCorto = g->pathfindDijkstra(inicioBueno, fin);
    }

    /* Nos acercamos al nodo Inicio del camino */
    posNodoI = inicioBueno->getPosition();
    float distNodoI = posNodoI->getPosX() - enemigoX;
    
    if(llegadoInicio==false)        // Solo lo haremos si no habiamos llegado ya al nodo Inicio del camino
    {
        if (distNodoI<-1.0f) // AVANZAMOS HACIA LA IZQUIERDA
         {

                e->getBody()->SetLinearVelocity(-(e->getVelocidad2d()));               // Velocidad Normal
                e->getBody()->ApplyForceToCenter(b2Vec2(-300.f,0.f),true);             // Fuerza para correr

                e->setLastFacedDir(false);                                    
         }
         else{
                if(distNodoI>1.0f) // AVANZAMOS HACIA LA DERECHA
                {

                    e->getBody()->SetLinearVelocity(e->getVelocidad2d());
                    e->getBody()->ApplyForceToCenter(b2Vec2(300.f,0.f),true);             // Fuerza para correr

                    e->setLastFacedDir(true);                                    
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
        for(int i=0; i<caminoCorto.size();i++)
        {
            fin = caminoCorto[i]->getNodoFin();

            if(caminoCorto[i]->getComportamiento()==NORMAL)         // Movimiento normal del enemigo
            {   
                posNodoI = fin->getPosition();
                float distNodoF = posNodoI->getPosX() - enemigoX;

                if (distNodoF<-1.0f) // AVANZAMOS HACIA LA IZQUIERDA
                 {

                        e->getBody()->SetLinearVelocity(-(e->getVelocidad2d()));               // Velocidad Normal
                        e->getBody()->ApplyForceToCenter(b2Vec2(-300.f,0.f),true);             // Fuerza para correr

                        e->setLastFacedDir(false);                                    
                 }
                 else{
                        if(distNodoF>1.0f) // AVANZAMOS HACIA LA DERECHA
                        {

                            e->getBody()->SetLinearVelocity(e->getVelocidad2d());
                            e->getBody()->ApplyForceToCenter(b2Vec2(300.f,0.f),true);             // Fuerza para correr

                            e->setLastFacedDir(true);                                    
                        }
                        else // Si hemos llegado al nodo Inicio
                        {
                            llegadoFin = true;
                        }
                    }

            }
        }
    }

    // Hemos llegado al ultimo nodo del camino calculado o hemos llegado al inicio y ademas no hay camino corto, puesto que ya estamos en el nodo mas cercano al objetivo
    if((llegadoFin==true) || (llegadoInicio==true && caminoCorto.size()==0))
    {

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
                         llegadoInicio = true;
                         inicio1 = nullptr;
                         inicio2 = nullptr;
                         fin = nullptr;
                         caminoCorto.clear();
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
        //cout<<"izquierda"<<endl;
        e->setLastFacedDir(false);
    } 
    else
    {   //cout<<"derecha"<<endl;
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
            //posNodoI = nodos[i]->getPosition();
           // cout<<"visto nodo:"<<posNodoI.X<<endl;

            if(v==1)
            {
                //cout<<"primera"<<endl;
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
          comidaX=comidaPosition->getPosX();
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

void BuscarComida::onInitialize(Blackboard *b)
{
   c = b->getComida();
   board = b;

   inicio1 = nullptr;
   inicio2 = nullptr;
   inicioBueno = nullptr;
   fin = nullptr;

   g = new Grafo();
}


BuscarComida::~BuscarComida()
{
    board = nullptr;
    comidaNode = nullptr;

    for(int i = 0 ; i < c.size(); i++){
      c[i] = nullptr;
    }
    c.clear();

    for(int i=0; i<caminoCorto.size();i++)
    {
        caminoCorto[i] = nullptr;
    }
    caminoCorto.clear();

    //delete board;
    //delete c;
}
