#ifndef TGESTORRECURSOS_H
#define TGESTORRECURSOS_H

#include <iostream>
#include <vector>
#include <math.h>

#include "TRecurso.h"
#include "TRecursoMalla.h"
#include "TRecursoMaterial.h"
#include "Shader.h"

class TGestorRecursos{
public:
	static TGestorRecursos* getInstance();
	virtual ~TGestorRecursos();

	template <class Tipo>
	TRecurso* getRecurso(string nombre_fichero){

		Tipo* r = dynamic_cast<Tipo*>(buscarRecurso(nombre_fichero));

		if(r == NULL){
			r = new Tipo();

			r->cargarFichero(nombre_fichero);
			r->setNombre(nombre_fichero);
			recursos.push_back(r);
		}

		return r;
	}
//	TRecurso *getRecursoMat(string nombre);
//	TRecurso *getRecursoT(string nombre);
	TRecurso* buscarRecurso(string nombre);

	Shader* getShader();

private:
	TGestorRecursos();

	vector<TRecurso*> recursos;
	Shader* shader;
	int nivel;

};


#endif //TGESTORRECURSOS_H