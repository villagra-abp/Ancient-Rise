#include "../headerfiles/TMalla.h"

TMalla::TMalla(){
	gestor = TGestorRecursos::getInstance();
	visible = true;
}
TMalla::~TMalla(){

}

void TMalla::cargarMalla(string path){
	mesh = dynamic_cast<TRecursoMalla*>(gestor->getRecurso<TRecursoMalla>(path));
}

void TMalla::beginDraw(glm::mat4 view, glm::mat4 projection){
	if(visible){
		mesh->draw(*gestor->getShader(), mmodelo, view, projection); // (...) //Dibujado del recurso de malla OpenGL
	}
}
void TMalla::endDraw(){
}

void TMalla::isVisible(bool flag){
	visible = flag;
}
