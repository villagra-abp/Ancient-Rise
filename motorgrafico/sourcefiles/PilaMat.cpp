#include "../headerfiles/PilaMat.h"

PilaMat::PilaMat(){

	// Matriz identidad como matriz acutal, sera la primera
	// en ser apilada.
	mactual=glm::mat4(1.0);
}
PilaMat::~PilaMat(){
	for(int i = 0; i<mipila.size(); i++){
		mipila.pop();
	}
	//delete mactual; 
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
glm::mat4 PilaMat::getMactual(){
	return mactual;
}
void PilaMat::setMactual(glm::mat4 mat){
	mactual = mat;
}