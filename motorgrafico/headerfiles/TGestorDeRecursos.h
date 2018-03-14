#ifndef GESTORDERECURSOS_H
#define GESTORDERECURSOS_H

#include "../headerfiles/TRecurso.h"

#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

class TGestorDeRecursos{
public:
	TGestorDeRecursos();
	virtual ~TGestorDeRecursos();
	TRecurso* getRecurso(char* nombre);
	TRecurso* buscarRecurso(char* nombre);
	


private:	

	vector <TRecurso*> recursos;

} ;

#endif //GESTORDERECURSOS_H
