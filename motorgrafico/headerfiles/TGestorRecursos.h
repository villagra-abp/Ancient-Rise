#ifndef TGESTORRECURSOS_H
#define TGESTORRECURSOS_H

#include <iostream>
#include <vector>
#include <math.h>

#include "TRecurso.h"
#include "TRecursoMalla.h"

class TGestorRecursos{
public:
	static TGestorRecursos* getInstance();
	virtual ~TGestorRecursos();

	template <class Tipo>
	TRecurso* getRecurso(string nombre_fichero){

		Tipo* r = dynamic_cast<Tipo*>(buscarRecurso(nombre_fichero));

		if(r == NULL){
			r = new Tipo();
			cout<<"jiji"<<endl;
			r->cargarFichero(nombre_fichero);
			r->setNombre(nombre_fichero);
			recursos.push_back(r);
		}

		return r;
	}
//	TRecurso *getRecursoMat(string nombre);
//	TRecurso *getRecursoT(string nombre);
	TRecurso* buscarRecurso(string nombre);


private:
	TGestorRecursos();

	vector<TRecurso*> recursos;

};


#endif //TGESTORRECURSOS_H