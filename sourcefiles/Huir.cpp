#include "../headerfiles/Huir.h"

Status Huir::run(Enemigo *e)
{   
    e->setCombate(false);

    Posicion* EnemigoPosition = e->getPosition(); 
    float enemigoX=EnemigoPosition->getPosX();
    float enemigoY=EnemigoPosition->getPosY();

    nodos = board->getNodosGrafo();

    /* Buscamos el nodo Inicial mas cercano al enemigo */
    if(inicio1==nullptr && inicio2==nullptr)  // Solo buscaremos el nodo inicio si no lo habiamos encontrado ya
    {
        buscarNodoInicial(e, enemigoX);
    }

    if(inicio1!=nullptr)
    {
        inicioBueno = inicio1;
    }
    else
    {
        inicioBueno = inicio2;
    }

    /* Buscamos el nodo mas cercano al enemigo y al lado contrario del prota */
    if(fin==nullptr)        // Solo si no lo habiamos encontrado ya
    {
        calcularNodoFinal(inicioBueno);
        //inicioAnterior = inicioBueno;
        //cout<<"InicioAnt: "<<inicioAnterior->getPosition()->getPosX()<<endl;
    }
    /*
    cout<<"InicioBueno"<<inicioBueno->getPosition()->getPosX()<<endl;
    cout<<"FIn : "<<fin->getPosition()->getPosX()<<endl;
    */
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
    if(llegadoInicio==true && caminoCorto.size()!=0)
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
                            llegadoInicio = false;
                            inicio1 = nullptr;
                            inicio2 = nullptr;
                            posNodo = nullptr;
                            posNodoI = nullptr;
                            inicioBueno = nullptr;
                            fin = nullptr;

                            return BH_SUCCESS;
                        }
                    }

            }
        }                  
    }
    
   return BH_RUNNING;
}

/* Metodo para buscar el nodo inicial visible del grafo mas cercano desde la pos del enemigo, siempre y cuando no lo hayamos encontrado ya antes */
void Huir::buscarNodoInicial(Enemigo *e, float posX)
{

    if(e->see(board->getProtagonista()))
    {
        /*
        if(e->getLastFaceDir()==true)
        {
            cout<<"ANtes derecha"<<endl;
        }
        else
        {
            cout<<" Antes izqd"<<endl;
        }
        */
        e->changeLastFaceDir();
      /*  if(e->getLastFaceDir()==true)
        {
            cout<<"derecha"<<endl;
        }
        else
        {
            cout<<"izqd"<<endl;
        }
        */
        e->actualizarVistos();                 // Como hemos cambiado la direccion de la vista, actualizamos los gameobjects que puede ver
    }

    recorrerNodos(e,1, posX);

    if(inicio1==nullptr)                       // Solamente si no hemos encontrado un nodo en la direccion contrario al prota, buscamos uno en el otro lado
    {
        e->changeLastFaceDir();
        e->actualizarVistos();

        recorrerNodos(e,2, posX);

        if(inicio2==nullptr)
        {
            cout<<"Error. El enemigo no ha visto ningun nodo de Inicio"<<endl;
        }
    }
    
}

/* Funcion para recorrer todos los nodos del grafo y comprobar si el enemigo puede ver alguno */
void Huir::recorrerNodos(Enemigo* e, uint8_t v, float posX)
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
NodoGrafo* Huir::calcularNodoMasCercano(NodoGrafo* i, NodoGrafo* i2, float posX)
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

void Huir::calcularNodoFinal(NodoGrafo* n)
{
   for(int i=0; i<nodos.size();i++)
    {    
        if(n->getNombre()!=nodos[i]->getNombre() && n->getPosition()->getPosY()==nodos[i]->getPosition()->getPosY() )        
        {

            if(inicioAnterior!=nullptr)
            {
                if(nodos[i]->getNombre()!=inicioAnterior->getNombre()) // Solo cogeremos el nodo final del camino si no habiamos ido ya antes para evitar bucles
                {
                    if(fin==nullptr)
                    {
                        fin = nodos[i];
                    }
                    else        // Comprobamos si no hay un nodo mas cercano a la fuente
                    {
                        fin = calcularNodoMasCercano(fin, nodos[i], n->getPosition()->getPosX());
                    }
                }
            } 
            else
            {
                if(fin==nullptr)
                {
                    fin = nodos[i];
                }
                else        // Comprobamos si no hay un nodo mas cercano a la fuente
                {
                    fin = calcularNodoMasCercano(fin, nodos[i], n->getPosition()->getPosX());
                }
            } 

        }
    }

    if(fin==nullptr)     // SI no hemos encontrado nodo final por culpa del inicioAnterior porque no habia mas nodos disponibles entocnes lo cogemos igualmente
    {
        for(int i=0; i<nodos.size();i++)
        { 
            if(n->getNombre()!=nodos[i]->getNombre() && n->getPosition()->getPosY()==nodos[i]->getPosition()->getPosY() )        
            {
                if(fin==nullptr)
                {
                    fin = nodos[i];
                }
                else        // Comprobamos si no hay un nodo mas cercano a la fuente
                {
                    fin = calcularNodoMasCercano(fin, nodos[i], n->getPosition()->getPosX());
                }
            }
        }
    }   

}

void Huir::startClock()
{
    if(contador==0)
    {
        reloj.restart();
        contador = contador +1;
    }
}

void Huir::onInitialize(Blackboard *b)
{
	board = b;
    contador = 0;
    inicio1 = nullptr;
    inicio2 = nullptr;
    posNodo = nullptr;
    posNodoI = nullptr;
    inicioBueno = nullptr;
    inicioAnterior = nullptr;

    g = new Grafo();
}

Huir::~Huir()
{
    board = nullptr;
    delete g;

}