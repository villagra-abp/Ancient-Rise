#include "../headerfiles/TTransf.h"

TTransformacion::TTransformacion(){

}
TTransformacion::~TTransformacion(){

}
void identidad(){

}
//void cargar(TMatriz4x4 matriz){

//}
void transponer(){

}
void trasladar(float x,float y,float z){

}
void rotar(float x,float y,float z,float w){

}

void TTransformacion::beginDraw(PilaMat* p){
	//Apilar matriz actual
	glm::mat4 mact = p->getMactual();
	p->apila(mact);
	//Multiplicar la matriz de la transformación a la matriz actual
	p->setMactual(mact * matriz);
}
void TTransformacion::endDraw(PilaMat* p){
	//Desapilar matriz y ponerla como actual
	p->setMactual(p->desapila());
}
