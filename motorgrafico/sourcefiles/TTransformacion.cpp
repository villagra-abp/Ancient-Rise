#include "../headerfiles/TTransformacion.h"

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

void TTransformacion::beginDraw(){
	//Apilar matriz actual
	//Multiplicar la matriz de la transformación a la matriz actual
}
void TTransformacion::endDraw(){
	//Desapilar matriz y ponerla como actual
}
