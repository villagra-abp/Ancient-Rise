#include "../headerfiles/TMalla.h"

TMalla::TMalla(){
	gestor = TGestorRecursos::getInstance();
	visible = true;
}
TMalla::~TMalla(){

}

void TMalla::cargarMalla(string name){
	malla = dynamic_cast<TRecursoMalla*>(gestor->getRecurso<TRecursoMalla>(name));
}

void TMalla::beginDraw(){
	if(visible)
		malla->draw(*gestor->getShader()); // (...) //Dibujado del recurso de malla OpenGL
}
void TMalla::endDraw(){
}

void TMalla::isVisible(bool flag){
	visible = flag;
}
