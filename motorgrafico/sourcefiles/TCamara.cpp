#include "../headerfiles/TCamara.h"

//Clase para guardar los datos de las camaras. Original.

TCamara::TCamara(){
	setPerspectiva(45.0f, 4.0f / 3.0f, 0.1f, 100.f);
}
TCamara::~TCamara(){

}
void TCamara::setPerspectiva(float fovy, float aspect, float near, float far){
	mProyeccion = glm::perspective(fovy, aspect, near, far);
}
void TCamara::setParalela(float left, float right, float bottom, float top, float near, float far){
	mProyeccion = glm::ortho(left, right, bottom, top, near, far);
}


bool TCamara::getActive(){
	return active;
}

glm::mat4 TCamara::getProyectionMatrix(){
	return mProyeccion;
}


void TCamara::setActive(bool flag){
	active = flag;
}

