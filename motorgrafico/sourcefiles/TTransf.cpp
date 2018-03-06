#include "../headerfiles/TTransf.h"

TTransf::TTransf(){
	//Por defecto asignamos matriz identidad a la transformacion
	matriz = glm::mat4(1.0f); 
}
TTransf::~TTransf(){

}
void TTransf::identidad(){
	matriz = glm::mat4(1.0f);
}
void TTransf::cargar(glm::mat4 mat){
	matriz = mat;
}
void TTransf::transponer(){
	matriz = glm::transpose(matriz);
}
void TTransf::trasladar(float x,float y,float z){
	matriz = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));
}
void TTransf::rotar(float x,float y,float z,float w){
	matriz = glm::rotate(glm::mat4(1.0f), w, glm::vec3(x, y, z));
}
void TTransf::escalar(float x, float y, float z){
	matriz = glm::scale(glm::mat4(1.0f), glm::vec3(x, y, z));
}
void TTransf::invertir(){
	matriz = glm::inverse(matriz);
}
glm::mat4 TTransf::getMatriz(){
	return matriz;
}

void TTransf::beginDraw(){
	//Apilar matriz actual
	pila->apila(mmodelo);
	//Multiplicar la matriz de la transformacion a la matriz modelo actual
	mmodelo = mmodelo * matriz;

	/*std::cout << "Transf Original: " << std::endl;
	std::cout << glm::to_string(matriz) << std::endl;
	std::cout << "Matriz Modelo: " << std::endl;
	std::cout << glm::to_string(mmodelo) << std::endl;*/ 
}
void TTransf::endDraw(){
	//Desapilar matriz y ponerla como actual
	mmodelo = pila->desapila();

	/*std::cout << "Desapilada: " << std::endl;
	std::cout << glm::to_string(mmodelo) << std::endl;*/ 
}
