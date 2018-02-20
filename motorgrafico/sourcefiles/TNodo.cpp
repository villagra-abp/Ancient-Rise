#include "../headerfiles/TNodo.h"

TNodo::TNodo():entidad(nullptr),padre(nullptr),padreBorrar(nullptr)
{
	encontrado = false;
}

TNodo::~TNodo(){
	entidad = nullptr;
	padre = nullptr;
}
/* Anyade un nodo al final del vector de hijos del nodo */
int TNodo::addHijoBack(TNodo* n){

	n->setPadre(this); 											// Al nodo hijo que añadimos le indicamos que este nodo es su nodo padre
	hijos.push_back(n);

	return hijos.size();
}
/* Funcion para anyadir un nodo en el vector de hijos en la pos que le indicamos por parametro */
int TNodo::addHijo(TNodo* n, int pos)
{
	n->setPadre(this); 											// Al nodo hijo que añadimos le indicamos que este nodo es su nodo padre
	hijos.insert(hijos.begin()+pos, n); 						// Metemos el nodo en la posicion indicada

	return hijos.size();
}

/* Funcion para borrar un hijo del nodo. En el caso que sea un nodo hoja solo lo borra del vector. 
	Si se trata de un nodo rama, lo que hace es borrarlo y a sus hijos se le cambia el puntero del padre al padre del nodo borrado */
TNodo* TNodo::remHijo(TNodo* n)
{	
	encontrado = false;
	if(hijos.size()!=0) 										// Comprobamos si tiene algun hijo que borrar
	{
		for(int i=0;i<hijos.size() && !encontrado;i++) 			// Recorremos todos los hijos de este nodo (this)
		{
			if(hijos[i]==n)
			{
				hijosPadre = hijos[i]->getHijos(); 				// Obtenemos los hijos del nodo que queremos borrar
				hijos.erase(hijos.begin()+i); 					// Borramos el nodo del vector
				encontrado = true;

				if(hijosPadre.size()!=0) 						// Comprobamos que el hijo de este nodo(this) que queremos borrar, tenga hijos o no para cambiar su puntero padre
				{
					for(int i2=0;i2<hijosPadre.size();i2++)  	// Recorremos para cambiar la direccion a la que apunta el puntero padre de los hijos
					{	
						addHijo(hijosPadre[i2], i); 			// Anyadimos un hijo nuevo a este nodo en la pos del vector donde se encontraba el nodo que borramos
					}
				}
			}
		}

	}

	if(encontrado == true) 										// Si hemos encontrado el nodo que queriamos borrar en el vector, eliminamos el nodo
	{
		delete n;
		n = nullptr;
	}

 return n;
}
/* Funcion para borrar un hijo del nodo y todos los nodos hijos de ese nodo que queremos borrar, asi hasta que no queden hijos en la rama */
int TNodo::remHijoAll(TNodo* n)
{	
	encontrado = false;
	if(hijos.size()!=0)
	{
		for(int i=0;i<hijos.size(); i++)
		{
			if(hijos[i]==n)
			{
				//nodosBorrar.push_back(hijos[i]);
				hijosPadre = hijos[i]->getHijos();

				if(hijosPadre.size()!=0)
				{/*
					for(int i2=0; hijosPadre.size(); i2++)
					{
						hijos[i]->remHijoAll(hijosPadre[i2]);
					}
					*/
				}
			}
		}
	}

	if(nodosBorrar.size()!=0)
	{
		while(nodosBorrar.size()!=0)
		{
			for(int i3=nodosBorrar.size();i3>0;i3--)
			{
				padreBorrar = nodosBorrar[i3]->getPadre();
				padreBorrar->remHijo(nodosBorrar[i3]);
			}
		}
	}

	return hijos.size();
}
/* Funcion que le pasamos dos nodos : n1 que es el nodo hijo que queremos borrar y n2 que sera el nuevo nodo padre de los nodos hijos del nodo borrado */
TNodo* TNodo::remHijoChange(TNodo* n1, TNodo* n2)
{
	encontrado = false;
	if(hijos.size()!=0) 										// Comprobamos si tiene algun hijo que borrar
	{
		for(int i=0;i<hijos.size() && !encontrado;i++) 			// Recorremos todos los hijos de este nodo (this)
		{
			if(hijos[i]==n1)
			{
				hijosPadre = hijos[i]->getHijos(); 				// Obtenemos los hijos del nodo que queremos borrar
				hijos.erase(hijos.begin()+i); 					// Borramos el nodo del vector
				encontrado = true;

				if(hijosPadre.size()!=0) 						
				{
					for(int i2=0;i2<hijosPadre.size();i2++)  	
					{	
						n2->addHijoBack(hijosPadre[i2]); 		// Indicamos que n2 es el nodo padre de los hijos del nodo borrado
					}
				}
			}
		}

	}

	if(encontrado == true) 										// Si hemos encontrado el nodo que queriamos borrar en el vector, eliminamos el nodo
	{
		delete n1;
		n1 = nullptr;
	}

	return n1;
}


/* Getters y setters */ 
bool TNodo::setEntidad(TEntidad* ent){
	entidad=ent;
	return true;
}
/* Para indicar cual es el nodo padre del nodo actual*/
void TNodo::setPadre(TNodo *p)
{
	padre = p;
}

void TNodo::setIdent(int i)
{
	identificador = i;
}


TEntidad * TNodo::getEntidad(){
	return entidad;
}
TNodo * TNodo::getPadre(){
	return padre;
}

vector<TNodo*> TNodo::getHijos()
{
	return hijos;
}

int TNodo::getIdent()
{
	return identificador;
}


void TNodo::draw()
{

	if(entidad!=nullptr)
		entidad -> beginDraw();

	//para cada nodo hijo i
	for(int i=0; i<hijos.size(); i++){
		hijos[i]->draw();
	}

	if(entidad!=nullptr)
		entidad -> endDraw();
}
