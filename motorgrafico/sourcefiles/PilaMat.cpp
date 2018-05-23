#include "../headerfiles/PilaMat.h"

//Clase para gestionar la pila de matrices

PilaMat::PilaMat(){

	// Matriz identidad como matriz acutal, sera la primera
	// en ser apilada.
	mipila.push(glm::mat4(1.0f));
}
PilaMat::~PilaMat(){
	for(int i = 0; i<mipila.size(); i++){
		mipila.pop();
	} 
}
void PilaMat::apila(glm::mat4 mat){
	mipila.push(mat);
}
glm::mat4 PilaMat::desapila(){
	glm::mat4 mat = mipila.top();
	mipila.pop();

	return mat;
}
glm::mat4 PilaMat::consulta(){
	return mipila.top();
}