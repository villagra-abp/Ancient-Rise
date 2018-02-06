#include "../headerfiles/TNodo.h"

TNodo::TNodo(){
}

TNodo::~TNodo(){

}
int TNodo::addHijo(TNodo* n){

	hijos.push_back(n);

	return hijos.size();
}
int TNodo::remHijo(TNodo* n)
{
	int pos = 0;
	if(hijos.size()!=0)
	{
		for(int i=0;i<hijos.size();i++)
		{
			if(hijos[i]==n)
			{
				pos = i;   // ALmacenamos la pos que queremos borrar
			}
		}

		hijos.erase(hijos.begin()+pos);
	}

	return hijos.size();
}
bool TNodo::setEntidad(TEntidad* ent){
	entidad=ent;
	return true;
}
TEntidad * TNodo::getEntidad(){
	return entidad;
}
TNodo * TNodo::getPadre(){
	return padre;
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
