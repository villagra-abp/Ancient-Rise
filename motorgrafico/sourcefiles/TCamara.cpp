#include "../headerfiles/TCamara.h"

TCamara::TCamara(){
	
}
TCamara::~TCamara(){

}
void setPerspectiva(float fovy, float aspect, float near, float far){
	glm::mat4 Proyeccion = glm::perspective(45.0f, 1024.0f / 768.0f, 0.1f, 200.0f);
}
void setParalela(float left, float right, float bottom, float top, float near, float far){
	glm::mat4 Proyeccion = glm::ortho(0.0f, 1024.0f,768.0f,0.0f, 0.1f, 100.0f);
}
void TCamara::endDraw(){
}
void TCamara::beginDraw(){
}



