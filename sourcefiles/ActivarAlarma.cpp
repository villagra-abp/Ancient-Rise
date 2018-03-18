#include "../headerfiles/ActivarAlarma.h"

Status ActivarAlarma::run(Enemigo *e)
{   
   e->setCombate(false);

   nodos = board->getNodosGrafo();

   // DATOS DEL ENEMIGO
   Posicion* EnemigoPosition = e->getPosition(); 
   float enemigoX=EnemigoPosition->getPosX();

   checkAlarmDes(e);

    /* Buscamos el nodo Inicial mas cercano al enemigo */
    if(inicio1==nullptr && inicio2==nullptr)  // Solo buscaremos el nodo inicio si no lo habiamos encontrado ya
    {
        buscarNodoInicial(e, enemigoX);
    }

    /* Buscamos el nodo mas cercano a la alarma */
    if(fin==nullptr)        // Solo si no lo habiamos encontrado ya
    {
       for(int i=0; i<nodos.size();i++)
       {    
           posNodo = nodos[i]->getPosition();
           if(alarmaY==posNodo->getPosY())        // Solo si el nodo esta a la misma altura que la pos de la fuente
           {
                if(fin==nullptr)
                {
                    fin = nodos[i];
                }
                else        // Comprobamos si no hay un nodo mas cercano a la fuente
                {
                    fin = calcularNodoMasCercano(fin, nodos[i], alarmaX);
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
        distanciaAlarma = alarmaX - enemigoX;  

        if (distanciaAlarma<0) // AVANZAMOS HACIA LA IZQUIERDA
        {

          e->getBody()->SetLinearVelocity(-(e->getVelocidad2d()));               // Velocidad Normal
          e->getBody()->ApplyForceToCenter(b2Vec2(-300.f,0.f),true);             // Fuerza para correr

          e->setLastFacedDir(false);                        // MIRANDO HACIA LA IZQUIERDA
  
        }
        else{
              if(distanciaAlarma>0) // AVANZAMOS HACIA LA DERECHA
              {

                 e->getBody()->SetLinearVelocity(e->getVelocidad2d());
                 e->getBody()->ApplyForceToCenter(b2Vec2(300.f,0.f),true);             // Fuerza para correr

                 e->setLastFacedDir(true);                // // MIRANDO HACIA LA DERECHA
              }
              else
              {
                   /* RELOJ ACTIVACION ALARMA */
                  startClock();                                 // INICIAMOS EL RELOJ (O RESEATEAMOS)

                  int duration = reloj.getElapsedTime().asSeconds();  // OBTENEMOS SU DURACION EN SEGUNDOS

                  if(duration > 2)        // TIEMPO QUE TARDA EN ACTIVARLA
                  {
                      a[pos]->setActivado(true);     
                      a[pos]->setActivando(false);
                      contador = 0; // Para resetear el reloj

                      /* Inicializamos todo otra vez para que la proxima vez que ocurra funcione todo bien */
                      llegadoFin = false;
                      llegadoInicio = true;
                      inicio1 = nullptr;
                      inicio2 = nullptr;
                      fin = nullptr;
                      caminoCorto.clear();

                      return BH_SUCCESS;
                    }
                }
          
          }
        
        a[pos]->setActivando(true);     // Activando alarma

    }

  return BH_RUNNING;        // Hasta que no active la alarma no habra terminado
}


/* Para comprobar si hay una alarma cerca, desactivada y no hay nadie que vaya a activarla ya */
void ActivarAlarma::checkAlarmDes(Enemigo* e)
{
  for (int i = 0; i < a.size(); i++){
      if( e->see(a[i]) && a[i]->getActivado()!=true && a[i]->getActivando()!=true ) 
      {  
        alarmaPosition = a[i]->getVector3df();
        alarmaX=alarmaPosition->getPosX();
        alarmaY = alarmaPosition->getPosY();

        pos = i;
        i = a.size();
      }
   }

}

/* Metodo para buscar el nodo inicial visible del grafo mas cercano desde la pos del enemigo, siempre y cuando no lo hayamos encontrado ya antes */
void ActivarAlarma::buscarNodoInicial(Enemigo *e, float posX)
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
void ActivarAlarma::recorrerNodos(Enemigo* e, uint8_t v, float posX)
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
NodoGrafo* ActivarAlarma::calcularNodoMasCercano(NodoGrafo* i, NodoGrafo* i2, float posX)
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

void ActivarAlarma::startClock()
{
    if(contador==0)
    {
        reloj.restart();
        contador = contador +1;
    }
}

void ActivarAlarma::onInitialize(Blackboard *b)
{
    board = b;
    a = board->getAlarma();
    
    contador = 0;
    alarmaX = 0.0;
    distanciaAlarma = 0;
    pos = 0;

    inicio1 = nullptr;
    inicio2 = nullptr;
    inicioBueno = nullptr;
    fin = nullptr;

    g = new Grafo();
}

ActivarAlarma::~ActivarAlarma()
{
    board = nullptr;

    for(int i = 0 ; i < a.size(); i++){
      a[i] = nullptr;
      delete a[i];  //No se si es necesario
    }

    a.clear();

    delete g;

   // delete board;
    //delete a;
}
