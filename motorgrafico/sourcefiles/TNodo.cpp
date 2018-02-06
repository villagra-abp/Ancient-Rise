#include "../headerfiles/TNodo.h"

TNodo::TNodo(){

}
TNodo::~TNodo(){

}
int TNodo::addHijo(){
	return hijos.size();
}
int TNodo::remHijo(){
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

entidad -> beginDraw();
//para cada nodo hijo i
for(int i=0; i<hijos.size(); i++){
	hijos[i] -> draw();
}
entidad -> endDraw();

}
