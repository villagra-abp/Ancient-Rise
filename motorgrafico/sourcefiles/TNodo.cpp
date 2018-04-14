#include "../headerfiles/TNodo.h"

TNodo::TNodo():entidad(nullptr),padre(nullptr)
{
	encontrado = false;
}

TNodo::~TNodo(){
	remHijos();												//Borramos primero los hijos del nodo

	if(padre != nullptr)
		padre->remHijo(this);								//Quitamos el nodo del vector hijos de su padre

	if(entidad != nullptr)
		delete entidad;										//Borramos la entidad
	
	entidad = nullptr;										//Puntero entidad apunta a null
	padre = nullptr;										//Puntero a padre apunta a null
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
/*
	if(encontrado == true) 										// Si hemos encontrado el nodo que queriamos borrar en el vector, eliminamos el nodo
	{
		delete n;
		n = nullptr;
	}
*/
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

glm::mat4 TNodo::getMatrix(){
	
	glm::mat4 mResultado = glm::mat4(1.0);
	vector<glm::mat4> mObtenidas;
	TNodo *nodoActual = getPadre();
	TTransf *entActual = nullptr;

	while(nodoActual->getPadre() != nullptr){
		if(nodoActual->getEntidad()->getTipo() == 0){
			entActual = dynamic_cast<TTransf*>(nodoActual->getEntidad());
			mObtenidas.push_back(entActual->getMatriz());
		}		
		nodoActual = nodoActual->getPadre();
	}
	
	if(mObtenidas.size()>0){
		for(int i = mObtenidas.size(); i > 0; i--){
			mResultado *= mObtenidas[i-1];
		}
	}

	return mResultado;
}

glm::vec3 TNodo::getPosicion(){
	glm::vec3 posicion;

	posicion = getMatrix() * glm::vec4(0,0,0,1.0f);

	return posicion;
}


void TNodo::draw(glm::mat4 view, glm::mat4 projection,TNodo* camara, vector<TNodo*> luces)
{
	vector<float> intensidad;
	vector<glm::vec4> color;
	glm::vec3 camaraPosicion;
	vector<glm::vec3> luzPosicion;

	
	camaraPosicion = camara->getPosicion();

	for(int i = 0; i < luces.size(); i++){
		luzPosicion.push_back(luces[i]->getPosicion());
		intensidad.push_back(dynamic_cast<TLuz*>(luces[0]->getEntidad())->getIntensidad());
		color.push_back(dynamic_cast<TLuz*>(luces[0]->getEntidad())->getColor());
	}

	

	if(entidad!=nullptr){
		entidad -> beginDraw(view, projection, intensidad, color, luzPosicion, camaraPosicion);
	}
	//para cada nodo hijo i
	for(int i=0; i<hijos.size(); i++){
		hijos[i]->draw(view, projection, camara, luces);
	}

	if(entidad!=nullptr)
		entidad -> endDraw();
}
