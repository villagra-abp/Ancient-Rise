#include "../headerfiles/Atacar.h"

Status Atacar::run(Enemigo *e)
{   
    checkVelocidad(e);

    p = board->getProtagonista();
    protaX = p->getPosition()->getPosX();
    protaY = p->getPosition()->getPosY();

	// DATOS ENEMIGO
    Posicion* EnemigoPosition = e->getPosition(); 
    enemigoX=EnemigoPosition->getPosX();
    enemigoY=EnemigoPosition->getPosY();

    int distanciaProta = protaX - enemigoX;  // Calculamos la distancia hasta el prota en X
    int distProtaY = protaY - enemigoY;

    // Comprobamos el tipo de arma que utiliza
    if(e->getTipo()==1)     // Cuerpo a cuerpo, cerca
    {
        separacionAtaque = 13;
    }
    else  // A distancia, ataque desde mas lejos
    {
        separacionAtaque = 80;
    }

    /* Comprobamos la distancia a la que tiene que estar para atacar */
    if(abs(distanciaProta)<separacionAtaque && distProtaY<10 && distProtaY>-10)       //ATACANDO
    {
        //cout<<"Atacando"<<endl;
        e->setVelocidad(e->getVelNormal()-10);             // Para que no gaste energia cuando llegue
        e->setVuelta(true);
        reset();                                        // Reseteamos los valores para el pathfinding

        if(e->getOrden()==1)                            // Ya hemos ejecutado la orden de atacarle mandado por el Elite, la eliminamos
        {
            e->setOrden(0);
        }
        e->setCombate(true);                            // COMBATIENDO


        if(e->getTipo()==1)                             // Mele
        {
             /* RELOJ POS COMBATE */
            startClock(1);                                        // INICIAMOS EL RELOJ (O RESEATEAMOS) DE POS_COMBATE
            int time = relojPos.getElapsedTime().asSeconds();     // OBTENEMOS SU DURACION EN SEGUNDOS

            if(time>2)
            {
                pos_combate = rand() % 3 + 1;
                e->setPosCombate(pos_combate);
                contPos = 0;
            }

            /* RELOJ ATAQUE MELE */
            startClock(3);
            int time2 = relojAtq.getElapsedTime().asSeconds();
            
            if(time2>1.5)
            {  
                if(p->getCombate()!=true || p->getPosCombate()!=pos_combate)        // Si el prota no esta en modo combate o no esta en la pos_combate donde ataca el enemigo, le quita vida
                {
                    p->quitarVida(10.f);
                }
                contAtq=0;
            }

        }
        else // A Distancia
        {   
            //cout<<"A distancia"<<endl;
            startClock(2);
            int time = relojRec.getElapsedTime().asSeconds();  // OBTENEMOS SU DURACION EN SEGUNDOS

             if(time>3)
            {  
                e->setDisparo(true);                        // Para saber si hay que crear un proyectil nuevo
                contRec = 0;
                return BH_SUCCESS;
            }

            e->setDisparo(false);  
        }
           
    }
    else        // PERSIGUIENDO
    {
        //cout<<"PERSIGUIENDO"<<endl;
        e->setVuelta(true);        // Para el recorrido de vuelta a la patrulla
        e->setCombate(false);
        contRec = 0;              // Para resetear el reloj de recargar proyectil y que tarde siempre lo mismo en recargar

        /* Buscamos el nodo Inicial mas cercano al enemigo */
        if(primera==true)
        {   
            primera = false;
            buscarNodoInicial(e, enemigoX);
        }
        
        /* Buscamos el nodo mas cercano al prota  */
        for(size_t i=0; i<nodos.size();i++)
        {    
            posNodo = nodos[i]->getPosition();
            if(board->getProtagonista()->getPosition()->getPosY()>=posNodo->getPosY()-10 && board->getProtagonista()->getPosition()->getPosY()<=posNodo->getPosY()+10)        
            {
                if(fin==nullptr)
                {
                    fin = nodos[i];
                }
                else        // Comprobamos si no hay un nodo mas cercano al enemigo
                {
                    fin = calcularNodoMasCercano(fin, nodos[i], protaX);
                }
            }
        }

        if(inicioBueno!=nullptr && fin!=nullptr)
        {  
            g=new Grafo();
            caminoCorto = g->pathfindDijkstra(inicioBueno, fin);
            delete g;

            /* Nos acercamos al nodo Inicio del camino */
            posNodoI = inicioBueno->getPosition();
            float distNodoI = posNodoI->getPosX() - enemigoX;

            if(llegadoInicio==false)        // Solo lo haremos si no habiamos llegado ya al nodo Inicio del camino
            {
                if (distNodoI<-1.0f) // AVANZAMOS HACIA LA IZQUIERDA
                {
                        movimientoDireccion(e,false);                                    
                 }
                 else{
                        if(distNodoI>1.0f) // AVANZAMOS HACIA LA DERECHA
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
                   reset();
                }
            }
        }
        else
        {
            //cout<<"No se ha podido encontrar el camino mas corto al protagonista"<<endl;
        }

        
    }
    return BH_SUCCESS;
    
}

/* Metodo para buscar el nodo inicial visible del grafo mas cercano desde la pos del enemigo, siempre y cuando no lo hayamos encontrado ya antes */
void Atacar::buscarNodoInicial(Enemigo *e, float posX)
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
        //cout<<"Error. El enemigo no ha visto ningun nodo de Inicio"<<endl;
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
void Atacar::recorrerNodos(Enemigo* e, uint8_t v, float posX)
{

    for(size_t i=0; i<nodos.size();i++)
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
NodoGrafo* Atacar::calcularNodoMasCercano(NodoGrafo* i, NodoGrafo* i2, float posX)
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


/*
 Funcion para iniciar el reloj correspondienteen funcion del entero que pasamos
*/
void Atacar::startClock(int t)
{
    switch(t)
    {
        case 1: // Reloj tiempo cambiar pos_combate
        {
             if(contPos==0)
            {
                relojPos.restart();
                contPos = contPos +1;
            }
            break;
        }

        case 2: //Reloj tiempo recarga disparo proyectil
        {
            if(contRec==0)
            {
                relojRec.restart();
                contRec = contRec +1;
            }
            break;
        }

        case 3: // Reloj tiempo atacar protagonista
        {
            if(contAtq==0)
            {
                relojAtq.restart();
                contAtq = contAtq+1;
            }
            break;
        }

    }   
}

/* FUncion para especificar la velocidad y direccion de movimiento del enemigo */
void Atacar::movimientoDireccion(Enemigo *e, bool d)
{
    if(d==false)   // Izquierda
    {
      e->getBody()->SetLinearVelocity(-(e->getVelocidad2d()));               // Obtenemogs la velocidad de movimiento del enemigo

      e->setLastFacedDir(d); 
    }
    else  // Derecha
    {
        e->getBody()->SetLinearVelocity(e->getVelocidad2d());    

        e->setLastFacedDir(d);   
    }
}

/* Funcion para que el enemigo sepa que comportamiento tiene que hacer durante el pathfinding */
void Atacar::checkComportamiento(Enemigo *e)
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
        //cout<<"Salto"<<endl;
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
            e->getBody()->ApplyForceToCenter(b2Vec2(0.f,550000.f),true);
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
void Atacar::checkVelocidad(Enemigo *e)
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


void Atacar::reset()
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
    primera = true;
}

void Atacar::onInitialize(Blackboard *b)
{
   board = b;
   nodos = board->getNodosGrafo();
   separacionAtaque = 10;
   p = board->getProtagonista();
   p = nullptr;

   inicio1 = nullptr;
   inicio2 = nullptr;
   inicioBueno = nullptr;
   fin = nullptr;
   contador = 0;

   primera = true;

}

Atacar::~Atacar()
{
    board = nullptr;

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
