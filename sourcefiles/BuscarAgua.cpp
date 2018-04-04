#include "../headerfiles/BuscarAgua.h"



Status BuscarAgua::run(Enemigo *e)
{   
     e->setCombate(false);

    // DATOS DEL ENEMIGO
    Posicion* EnemigoPosition = e->getPosition(); 
    float enemigoX =EnemigoPosition->getPosX();
    float enemigoY =EnemigoPosition->getPosY(); 

    nodos = board->getNodosGrafo();

    /* Buscamos el nodo Inicial mas cercano al enemigo */
    if(inicio1==nullptr && inicio2==nullptr)  // Solo buscaremos el nodo inicio si no lo habiamos encontrado ya
    {
        buscarNodoInicial(e, enemigoX);
    /*    
      if(inicio1!=nullptr)
      {
      posNodo = inicio1->getPosition();
      cout<<"Inicio1: "<<posNodo->getPosX()<<endl;
      }
      if(inicio2!=nullptr)
      {
      posNodoI = inicio2->getPosition();
      cout<<"Inicio2: "<<posNodoI->getPosX()<<endl;
      }
      
      cout<<"InicioBueno :"<<inicioBueno->getPosition()->getPosX()<<endl;
      */
    }
    
    
    /* BUSCAR FUENTE MAS CERCANA */
      buscarFuenteCercana(enemigoX);
      
    
   // posNodo = f[pos]->getVector3df();
     //cout<<"FUente cercana :"<<posNodo->getPosX()<<endl;

     /* Buscamos el nodo mas cercano a la fuente elegida para ir */
    if(fin==nullptr)        // Solo si no lo habiamos encontrado ya
    {
       fuenteX = f[pos]->getVector3df()->getPosX();
       fuenteY = f[pos]->getVector3df()->getPosY();
       for(int i=0; i<nodos.size();i++)
       {    
           posNodo = nodos[i]->getPosition();
           //cout<<"Y fuente "<<fuenteY<<endl;
           if(fuenteY==posNodo->getPosY())        // Solo si el nodo esta a la misma altura que la pos de la fuente
           {
                if(fin==nullptr)
                {
                    fin = nodos[i];
                }
                else        // Comprobamos si no hay un nodo mas cercano a la fuente
                {
                    fin = calcularNodoMasCercano(fin, nodos[i], fuenteX);
                }

                //cout<<"Posible fin "<<fin->getPosition()->getPosX()<<endl;
           }
       }

      //posNodo = fin->getPosition();
     //cout<<"Fin: "<<posNodo->getPosX()<<endl;
    }


     /* Calculamos el camino mas corto entre el nodo Inicial (inicioBueno) y el nodo Final (fin) */
    if(caminoCorto.size()==0)           // Para calcular el camino solo 1 vez y no siempre
    {
        //cout<<"Tam camino antes:"<<caminoCorto.size()<<endl;
        g = new Grafo();
        caminoCorto = g->pathfindDijkstra(inicioBueno, fin);
        //cout<<"Tam camino despues:"<<caminoCorto.size()<<endl;
    }

    /* Nos acercamos al nodo Inicio del camino */
    posNodoI = inicioBueno->getPosition();
    float distNodoI = posNodoI->getPosX() - enemigoX;
    //cout<<distNodoI<<endl;
    //cout<<enemigoX<<endl;
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
            fin = caminoCorto[iC]->getNodoFin();

            if(caminoCorto[iC]->getComportamiento()==NORMAL)         // Movimiento normal del enemigo
            {   
                posNodoI = fin->getPosition();
                distNodoF = posNodoI->getPosX() - enemigoX;

                //cout<<"DIstNodoF "<<distNodoF<<endl;
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
      //cout<<"DistanFuente "<<distanciaFuente<<endl;
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
                      /* RELOJ BEBER AGUA */
                     startClock();                             // INICIAMOS EL RELOJ (O RESEATEAMOS)

                     int time = reloj.getElapsedTime().asSeconds();  // OBTENEMOS SU DURACION EN SEGUNDOS

                     f[pos]->setActivando(true);                         // ENEMIGO BEBIENDO

                     if(time>4)     // BEBIENDO
                     {
                         e->setSed(100.f);       // RECUPERAMOS SED
                         e->setVuelta(true);     // Indicamos que estamos volviendo a la patrulla
                         f[pos]->setActivando(false);
                         contador  = 0;
                         /* Inicializamos todo otra vez para que la proxima vez que ocurra funcione todo bien */
                         llegadoFin = false;
                         llegadoInicio = false;
                         inicio1 = nullptr;
                         inicio2 = nullptr;
                         fin = nullptr;
                         caminoCorto.clear();
                         inicioBueno = nullptr;

                         //cout<<"BEBIENDO LOCO"<<endl;
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
void BuscarAgua::recorrerNodos(Enemigo* e, uint8_t v, float posX)
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

       for (int i = 1; i < f.size(); i++){
          
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

void BuscarAgua::onInitialize(Blackboard *b)
{
   /* INfo fuente */
   f = b->getFuente();
   fuentePosition = nullptr;

   board = b;
   contador = 0;

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


BuscarAgua::~BuscarAgua()
{
   board = nullptr;
   inicio2 = nullptr;
   inicio1 = nullptr;
   inicioBueno = nullptr;
   fin = nullptr;
   posNodo = nullptr;
   posNodoI = nullptr;

    for(int i = 0 ; i < f.size(); i++){
      f[i] = nullptr;
    }

    f.clear();

    for(int i=0; i<caminoCorto.size();i++)
    {
        caminoCorto[i] = nullptr;
    }
    caminoCorto.clear();

    for(int i=0; i<nodos.size();i++)
    {
        nodos[i] = nullptr;
    }
    nodos.clear();

    delete g;
}