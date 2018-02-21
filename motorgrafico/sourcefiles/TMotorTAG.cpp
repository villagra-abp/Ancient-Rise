#include "../headerfiles/TMotorTAG.h"

TMotorTAG::TMotorTAG() : escena(nullptr)
{

}
TMotorTAG::~TMotorTAG(){
	delete escena;
	escena = nullptr;
}

TNodo* TMotorTAG::crearNodo(TNodo *padre, TEntidad *ent){
	TNodo* nodo = new TNodo();
	
	if(ent!=nullptr){
		nodo->setEntidad(ent);
		if(ent->getTipo()==camara)
			regCam.push_back(nodo);
		else if(ent->getTipo()==luz)
			regLuz.push_back(nodo);
	}

	if(padre!=nullptr)
		padre->addHijoBack(nodo);
	else
		escena = nodo;

	return nodo;
}
TTransf* TMotorTAG::crearTransf(){
	TTransf* transf = new TTransf();

	return transf;
}
TCamara* TMotorTAG::crearCamara(){
	TCamara* camara = new TCamara();

	return camara;
}
TLuz* TMotorTAG::crearLuz(){
	TLuz* luz = new TLuz();

	return luz;
}
TMalla* TMotorTAG::crearMalla(char *fichero){
	TMalla* malla =  new TMalla();

	return malla;
}
void TMotorTAG::draw(){
	//Obtener puntero camara activa del Registro de camaras

	mCamara = generateMatrix(regCam[i]);
	mVista = glm::inverse(mCamara);

	//Obtener puntero luces activas del Registro de luces

	//Iniciar secuencia draw del arbol
	escena->draw();
}

glm::mat4 TMotorTAG::generateMatrix(TNodo *nodo){
	//Obtendra la Matriz Modelo de un Nodo dado mediante
	//mediante un recorrido inverso de padre a padre.
}