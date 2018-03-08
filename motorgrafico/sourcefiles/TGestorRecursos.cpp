#include "../headerfiles/TGestorRecursos.h"

static TGestorRecursos* instance = NULL;

TGestorRecursos* TGestorRecursos::getInstance(){
	if(instance == NULL)
		instance = new TGestorRecursos();

	return instance;
}


TGestorRecursos::TGestorRecursos(){

}

TGestorRecursos::~TGestorRecursos(){

}


TRecurso* TGestorRecursos::buscarRecurso(string nombre){
	TRecurso *rec = NULL;
	for(int i=0;i<recursos.size();i++){
		if(recursos[i]->getNombre()==nombre){
			rec=recursos[i];
		}
	}
	return rec;
}