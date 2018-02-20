#include "../headerfiles/TGestorDeRecursos.h"

TGestorDeRecursos::TGestorDeRecursos(){

}
TGestorDeRecursos::~TGestorDeRecursos(){

}
TRecurso* TGestorDeRecursos::getRecurso(char* nombre){
	TRecurso *rec=buscarRecurso(nombre);
	if(rec==NULL){
		rec = new TRecurso();
		rec->cargarFichero(nombre);
		rec->setNombre(nombre);
		recursos.push_back(rec);
	}	
	return rec;
}
TRecurso* TGestorDeRecursos::buscarRecurso(char* nombre){
	TRecurso *rec;
	for(int i=0;i<recursos.size();i++){
		if(recursos[i]->getNombre()==nombre){
			rec=recursos[i];
		}
	}
	return rec;
}
