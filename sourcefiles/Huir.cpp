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

    /* Buscamos el nodo mas cercano al enemigo y al lado contrario del prota */
    if(fin==nullptr)        // Solo si no lo habiamos encontrado ya
    {
       for(int i=0; i<nodos.size();i++)
       {    
           posNodo = nodos[i]->getPosition();
           if(enemigoY==posNodo->getPosY())        // Solo si el nodo esta a la misma altura que la pos de la fuente
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

     /* RELOJ HUIR */
    startClock();                                   // INICIAMOS EL RELOJ (O RESEATEAMOS)

    int time = reloj.getElapsedTime().asSeconds();  // OBTENEMOS SU DURACION EN SEGUNDOS

    //cout<<time<<endl;
    
    if(time>=4)
    {
        contador = 0;                               // RESETEAMOS EL CONTADOR
        return BH_SUCCESS;
    }
    else
    {
        if(e->getLastFaceDir()==true)   // Visto Prota a la derecha, enemigo huye hacia la izquierda
        {
            //e->setLastFacedDir(false);                                     // AHORA ESTA MIRANDO A LA IZQUIERDA

             e->getBody()->SetLinearVelocity(-(e->getVelocidad2d()));               // Velocidad Normal
             e->getBody()->ApplyForceToCenter(b2Vec2(-300.f,0.f),true);             // Fuerza para correr

        }
        else{   // Visto a la izquierda, se mueve hacia la derecha

                 //e->setLastFacedDir(true); 

                 e->getBody()->SetLinearVelocity(e->getVelocidad2d());
                 e->getBody()->ApplyForceToCenter(b2Vec2(300.f,0.f),true);             // Fuerza para correr
        }
    }

   return BH_RUNNING;
}

/* Metodo para buscar el nodo inicial visible del grafo mas cercano desde la pos del enemigo, siempre y cuando no lo hayamos encontrado ya antes */
void Huir::buscarNodoInicial(Enemigo *e, float posX)
{

    if(e->see(board->getProtagonista()))
    {
        e->changeLastFaceDir();
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
}

Huir::~Huir()
{
    board = nullptr;

}