#include "../headerfiles/TTransf.h"

TTransformacion::TTransformacion(){
	//Por defecto asignamos matriz identidad a la transformacion
	matriz = glm::mat4(1.0f); 
}
TTransformacion::~TTransformacion(){

}
void TTransformacion::identidad(){
	matriz = glm::mat4(1.0f);
}
void TTransformacion::cargar(glm::mat4 mat){
	matriz = mat;
}
void TTransformacion::transponer(){
	matriz = glm::transpose(matriz);
}
void TTransformacion::trasladar(float x,float y,float z){
	matriz = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));
}
void TTransformacion::rotar(float x,float y,float z,float w){
	matriz = glm::rotate(glm::mat4(1.0f), w, glm::vec3(x, y, z));
}

void TTransformacion::beginDraw(){
	//Apilar matriz actual
	pila->apila(mmodelo);
	//Multiplicar la matriz de la transformacion a la matriz modelo actual
	mmodelo = mmodelo * matriz;

	/*std::cout << "Transd Original: " << std::endl;
	std::cout << glm::to_string(matriz) << std::endl;
	std::cout << "Matriz Modelo: " << std::endl;
	std::cout << glm::to_string(mmodelo) << std::endl; */
}
void TTransformacion::endDraw(){
	//Desapilar matriz y ponerla como actual
	mmodelo = pila->desapila();

	/*std::cout << "Desapilada: " << std::endl;
	std::cout << glm::to_string(mmodelo) << std::endl; */
}
