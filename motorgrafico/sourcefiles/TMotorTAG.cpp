#include "../headerfiles/TMotorTAG.h"

TMotorTAG::TMotorTAG() : escena(nullptr)
{

}
TMotorTAG::~TMotorTAG(){

}

TNodo* TMotorTAG::crearNodo(TNodo *padre, TEntidad *ent){
	TNodo* nodo = new TNodo();
	
	if(ent!=nullptr)
		nodo->setEntidad(ent);

	if(padre!=nullptr)
		padre->addHijoBack(nodo);

	return nodo;
}
TTransf* TMotorTAG::crearTransf(){
	TTransf* transf = new TTransf();
}
TCamara* TMotorTAG::crearCamara(){

}
TLuz* TMotorTAG::crearLuz(){

}
TMalla* TMotorTAG::crearMalla(char *fichero){

}
void TMotorTAG::draw(){

}

void TMotorTAG::recInverso(TNodo *nodo){

}