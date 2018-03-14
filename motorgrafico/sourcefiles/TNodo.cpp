#include "../headerfiles/TNodo.h"

TNodo::TNodo():entidad(nullptr),padre(nullptr),padreBorrar(nullptr)
{
	encontrado = false;
}

TNodo::~TNodo(){
	remHijos();
	padre->remHijo(this);
	delete entidad;
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
/* Funcion para borrar un hijo del nodo y todos los nodos hijos de ese nodo que queremos borrar, asi hasta que no queden hijos en la rama
	Devuelve el numero de hijos restante
 */
int TNodo::remHijoAll(TNodo* n)
{	
	encontrado = false;
	if(hijos.size()!=0)													//Comprueba que haya hijos que borrar
	{
		for(int i=0;i<hijos.size() && encontrado == false; i++)			//Recorre el array de hijos buscando el nodo a borrar
		{
			if(hijos[i]==n)												//Comprueba el hijo de esta iteracion
			{
				delete hijos[i];										//Borramos el hijo y todos sus hijos
				
				encontrado = true;
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

// Funcion que cambia el padre del nodo por el padre dado por parametros
void TNodo::changePadre(TNodo* nPadre, TNodo* hijo){
	encontrado = false;

	if(hijos.size()!= 0){ //Comprobamos si hay hijos

		for(int i = 0; i<hijos.size() && !encontrado; i++){  	//Buscamos la posicion del nodo a cambiar en el vector hijos
			if(hijos[i] == hijo){								//Una vez encontrado, cambiamos padre del nodo y lo borramos del vector hijos
				hijos.erase(hijos.begin() + i);
				nPadre->addHijoBack(hijo);

				encontrado = true;
			}
		}
	}
}

//Funcion para borrar todos los hijos del nodo
void TNodo::remHijos(){
	if(hijos.size() != 0){ //Comprobamos que haya hijos

		for(int i = 0; i<hijos.size(); i++){					//Recorremos los hijos uno a uno para ir borrandolos

			delete hijos[i];

		}
	} 
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
