#include "../headerfiles/Atacar.h"

Status Atacar::run(Enemigo *e)
{   
	float posProta = board->getProta();

	// DATOS ENEMIGO
    Posicion* EnemigoPosition = e->getPosition(); 
    float enemigoX=EnemigoPosition->getPosX();

    int distanciaProta = posProta - enemigoX;  // Calculamos la distancia hasta el prota

    // Comprobamos el tipo de arma que utiliza
    if(e->getTipo()==1)     // Cuerpo a cuerpo, cerca
    {
        separacionAtaque = 25;
    }
    else  // A distancia, ataque desde mas lejos
    {
        separacionAtaque = 60;
    }

    /* Comprobamos la distancia a la que tiene que estar para atacar */
    if(abs(distanciaProta)>separacionAtaque)                                        // PERSIGUIENDO  
    {
        e->setCombate(false);
        contRec = 0;              // Para resetear el reloj de recargar proyectil y que tarde siempre lo mismo en recargar
        nodos = board->getNodosGrafo();

        /* Buscamos el nodo Inicial mas cercano al enemigo */
        buscarNodoInicial(e, enemigoX);
        
       // cout<<"InicioBueno :"<<inicioBueno->getPosition()->getPosX()<<endl;
         /* Buscamos el nodo mas cercano al prota  */
        for(int i=0; i<nodos.size();i++)
        {    
            posNodo = nodos[i]->getPosition();
            if(board->getProtagonista()->getPosition()->getPosY()>=posNodo->getPosY()-5 && board->getProtagonista()->getPosition()->getPosY()<=posNodo->getPosY()+5)        
            {
                if(fin==nullptr)
                {
                    fin = nodos[i];
                }
                else        // Comprobamos si no hay un nodo mas cercano a la fuente
                {
                    fin = calcularNodoMasCercano(fin, nodos[i], posProta);
                }
            }
        }

        //cout<<"Fin :"<<fin->getPosition()->getPosX()<<endl;

        if(inicioBueno!=nullptr && fin!=nullptr)
        {
            vector<Arista*>().swap(caminoCorto); 
            g=new Grafo();
            caminoCorto = g->pathfindDijkstra(inicioBueno, fin);
            cout<<caminoCorto.size()<<endl;
        }
        else
        {
            cout<<"No se ha podido encontrar el camino mas corto al protagonista"<<endl;
        }

        //cout<<"camino : "<<caminoCorto.size()<<endl;

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
            if(contador<caminoCorto.size())
            {
                fin = caminoCorto[contador]->getNodoFin();

                if(caminoCorto[contador]->getComportamiento()==NORMAL)         // Movimiento normal del enemigo
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
                            else // Si hemos llegado al nodo Fin
                            {
                                contador++;
                            }
                        }

                }
            }

            if(contador==caminoCorto.size())
            {
                llegadoFin = true;
                contador = 0;
            }
            
        }

        //cout<<"Contador : "<<contador<<endl;
        // Hemos llegado al ultimo nodo del camino calculado o hemos llegado al inicio y ademas no hay camino corto, puesto que ya estamos en el nodo mas cercano al objetivo
        if((llegadoFin==true) || (llegadoInicio==true && caminoCorto.size()==0))
        {
            if (distanciaProta<0) // AVANZAMOS HACIA LA IZQUIERDA
             {

                    e->getBody()->SetLinearVelocity(-(e->getVelocidad2d()));               // Velocidad Normal
                    e->getBody()->ApplyForceToCenter(b2Vec2(-300.f,0.f),true);             // Fuerza para correr

                    e->setLastFacedDir(false);                                    
             }
             else{
                    if(distanciaProta>0) // AVANZAMOS HACIA LA DERECHA
                    {

                        e->getBody()->SetLinearVelocity(e->getVelocidad2d());
                        e->getBody()->ApplyForceToCenter(b2Vec2(300.f,0.f),true);             // Fuerza para correr

                        e->setLastFacedDir(true);                                    
                    }
                    else // Si hemos llegado
                    {
                             /* Inicializamos todo otra vez para que la proxima vez que ocurra funcione todo bien */
                            /* llegadoFin = false;
                             llegadoInicio = false;
                             inicio1 = nullptr;
                             inicio2 = nullptr;
                             fin = nullptr;
                             caminoCorto.clear();
                             */
                    }
                }
        }

    }
    else        // ATACANDO
    {
        if(e->getOrden()==1)        // Ya hemos ejecutado la orden de atacarle mandado por el Elite, la eliminamos
        {
            e->setOrden(0);
        }
        e->setCombate(true);    // COMBATIENDO


        if(e->getTipo()==1)  // Mele
        {
            int pos_combate = rand() % 3 + 1;
             /* RELOJ POS COMBATE */
            startClock(1);                                        // INICIAMOS EL RELOJ (O RESEATEAMOS) DE POS_COMBATE
            int time = relojPos.getElapsedTime().asSeconds();     // OBTENEMOS SU DURACION EN SEGUNDOS

            if(time>3)
            {
                e->setPosCombate(pos_combate);
                contPos = 0;
            }

            /* RELOJ ATAQUE MELE */
            startClock(3);
            int time2 = relojAtq.getElapsedTime().asSeconds();
    
            if(time2>1)
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
    return BH_SUCCESS;
    
}

/* Metodo para buscar el nodo inicial visible del grafo mas cercano desde la pos del enemigo, siempre y cuando no lo hayamos encontrado ya antes */
void Atacar::buscarNodoInicial(Enemigo *e, float posX)
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
void Atacar::recorrerNodos(Enemigo* e, uint8_t v, float posX)
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

void Atacar::onInitialize(Blackboard *b)
{
    Fachada* fachada=fachada->getInstance();
    board = b;
    separacionAtaque = 10;
    p = board->getProtagonista();

   inicio1 = nullptr;
   inicio2 = nullptr;
   inicioBueno = nullptr;
   fin = nullptr;

   g = new Grafo();

   contador = 0;

}

Atacar::~Atacar()
{
    board = nullptr;
    delete g;
   
}
