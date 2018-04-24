#include "../headerfiles/NodoGrafo.h"

NodoGrafo::NodoGrafo(int n, glm::f32 x, glm::f32 y):path(nullptr)
{	
	GameObject::setTipo(NODOGRAFO);
	id = n;
	cost_so_far = 0; 			// Inicialmente no tendra coste asociado ya que se calcula durante el algoritmo
	nodoPosition = new Posicion(x,y,0);
/*
	Fachada* fachada=fachada->getInstance();
	objeto = fachada->addMalla(x,y,0.f,"resources/manzana.obj");
    //std::cout<<pos.getPosX()<<endl;
	if (objeto)
	{
        Posicion escala(0.3f,0.3f,0.3f);
		fachada->setScala(objeto,&escala);
		
        //fachada->setMaterial(objeto,"resources/desactivada.jpeg");
        
	}
*/
	//nodoPosition.X = x;			//
	//nodoPosition.Y = y; 		// Estos valores no variaran nunca
}

/* Funcion para insertar una arista saliente en este nodo e indicar cual es el nodo final de la arista */
void NodoGrafo::insertAristaS(Arista *s, NodoGrafo *final)
{
	aristasSal.push_back(s);

	s->setNodoI(this); 	// Indicamos que este nodo es el nodo inicial de la arista

	final->insertAristaE(s);
}

/* Funcion para insertar una arista entrante en este nodo */
void NodoGrafo::insertAristaE(Arista *e)
{
	aristasEnt.push_back(e);

	e->setNodoF(this); 	// Indicamos que este nodo es el nodo final de la arista
}


vector<Arista*> NodoGrafo::getAristasS()
{
	return aristasSal;
}

vector<Arista*> NodoGrafo::getAristasE()
{
	return aristasEnt;
}
double NodoGrafo::getCostSoFar()
{
	return cost_so_far;
}

int NodoGrafo::getNombre()
{
	return id;
}

Arista* NodoGrafo::getAristaPath()
{
	return path;
}


void NodoGrafo::setCostSoFar(double c)
{
	cost_so_far = c;
}

void NodoGrafo::setAristaPath(Arista* a)
{
	path = a;
}

NodoGrafo::~NodoGrafo()
{
	path = nullptr;
	delete nodoPosition;
}
