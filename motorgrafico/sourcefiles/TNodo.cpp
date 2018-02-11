#include "../headerfiles/TNodo.h"

TNodo::TNodo():entidad(nullptr),padre(nullptr)
{
	encontrado = false;
}

TNodo::~TNodo(){

}

int TNodo::addHijo(TNodo* n){

	n->setPadre(this); 			// Al nodo hijo que añadimos le indicamos que este nodo es su nodo padre
	hijos.push_back(n);

	return hijos.size();
}

int TNodo::remHijo(TNodo* n)
{	
	// PREGUNTAR SI HAY QUE HACERLO ASI O BORRAR TODO LOS HIJOS DEL NODO QUE BORRAMOS
	encontrado = false;
	if(hijos.size()!=0) 							// Comprobamos si tiene algun hijo que borrar
	{
		for(int i=0;i<hijos.size() && !encontrado;i++)
		{
			if(hijos[i]==n)
			{
				hijosPadre = hijos[i]->getHijos();
				if(hijosPadre.size()!=0)
				{
					for(int i2=0;i2<hijosPadre.size();i2++) 		
					{
						hijosPadre[i2]->setPadre(this); 		// Indicamos a todos los hijos del nodo que queremos borrar, que su nodo padre ahora es este nodo
					}
				}

				hijos.erase(hijos.begin()+i); 					// Borramos el nodo del vector
				encontrado = true;
			}
		}

	}
 return hijos.size();
}

bool TNodo::setEntidad(TEntidad* ent){
	entidad=ent;
	return true;
}
/* Para indicar cual es el nodo padre del nodo actual*/
void TNodo::setPadre(TNodo *p)
{
	padre = p;
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
void TNodo::draw(){

entidad -> beginDraw ();
//para cada nodo hijo i
int i;
for(i=0;i<hijos.size();i++){
	hijos[i] -> draw ();
}
entidad -> endDraw ();

}
