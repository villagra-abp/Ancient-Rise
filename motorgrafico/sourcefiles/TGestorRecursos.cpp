#include "../headerfiles/TGestorRecursos.h"

static TGestorRecursos* instance = NULL;

TGestorRecursos* TGestorRecursos::getInstance(){
	if(instance == NULL)
		instance = new TGestorRecursos();

	return instance;
}


TGestorRecursos::TGestorRecursos(){
	shader = new Shader("motorgrafico/shaders/vertex.vs", "motorgrafico/shaders/fragment1.fs");
}

TGestorRecursos::~TGestorRecursos(){

}


TRecurso* TGestorRecursos::buscarRecurso(string path){
	bool flag = false;
	TRecurso *rec = NULL;

	for(int i=0;i<recursos.size() && !flag;i++){
		if(recursos[i]->getNombre()==path){
			flag = true;
			rec = recursos[i];
		}
	}
	return rec;
}



Shader* TGestorRecursos::getShader(){
	return shader;
}