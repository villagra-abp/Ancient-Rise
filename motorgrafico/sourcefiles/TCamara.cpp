#include "../headerfiles/TCamara.h"

TCamara::TCamara(){
	
}
TCamara::~TCamara(){

}
void TCamara::setPerspectiva(float fovy, float aspect, float near, float far){
	mProyeccion = glm::perspective(fovy, aspect, near, far);
}
void TCamara::setParalela(float left, float right, float bottom, float top, float near, float far){
	mProyeccion = glm::ortho(left, right, bottom, top, near, far);
}
void TCamara::endDraw(){
}
void TCamara::beginDraw(){
}



