#include "../headerfiles/TMalla.h"

TMalla::TMalla(){
	gestor = TGestorRecursos::getInstance();
}
TMalla::~TMalla(){

}

void TMalla::cargarMalla(string name){
	malla = dynamic_cast<TRecursoMalla*>(gestor->getRecurso<TRecursoMalla>(name));
}

void TMalla::beginDraw(){
	malla->draw(*gestor->getShader()); // (...) //Dibujado del recurso de malla OpenGL
}
void TMalla::endDraw(){
}

