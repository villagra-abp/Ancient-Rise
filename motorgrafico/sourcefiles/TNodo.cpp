#include "../headerfiles/TNodo.h"

TNodo::TNodo():entidad(nullptr),padre(nullptr)
{
	encontrado = false;
}

TNodo::~TNodo(){
	entidad = nullptr;
	padre = nullptr;
}

int TNodo::addHijo(TNodo* n){

	n->setPadre(this); 											// Al nodo hijo que añadimos le indicamos que este nodo es su nodo padre
	hijos.push_back(n);

	return hijos.size();
}

int TNodo::remHijo(TNodo* n)
{	
	encontrado = false;
	if(hijos.size()!=0) 										// Comprobamos si tiene algun hijo que borrar
	{
		for(int i=0;i<hijos.size() && !encontrado;i++) 			// Recorremos todos los hijos de este nodo (this)
		{
			if(hijos[i]==n)
			{
				hijosPadre = hijos[i]->getHijos();
				if(hijosPadre.size()!=0) 						// Comprobamos que el hijo de este nodo(this) que queremos borrar, tenga hijos o no para cambiar su puntero padre
				{
					for(int i2=0;i2<hijosPadre.size();i2++)  	// Recorremos para cambiar la direccion a la que apunta el puntero padre de los hijos
					{	
						addHijo(hijosPadre[i2]); 				// Anyadimos un hijo nuevo a este nodo (Habria que anyadirlo al principio del vector no al final)
					}
				}

				hijos.erase(hijos.begin()+i); 					// Borramos el nodo del vector
				encontrado = true;
			}
		}

	}
 return hijos.size();
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
	entidad -> beginDraw ();
	//para cada nodo hijo i
	int i;
	for(i=0;i<hijos.size();i++){
		hijos[i] -> draw ();
	}
	entidad -> endDraw ();
}
