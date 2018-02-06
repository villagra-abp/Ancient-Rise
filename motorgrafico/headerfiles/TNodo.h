#ifndef NODO_H
#define NODO_H

#include <iostream>
#include <vector>
#include <math.h>
#include "../headerfiles/TEntidad.h"

using namespace std;

class TNodo{
public:
	TNodo();
	virtual ~TNodo();
	int addHijo(TNodo* n);
	int remHijo(TNodo* n);
	bool setEntidad(TEntidad* ent);
	TEntidad * getEntidad();
	TNodo * getPadre();
	void draw();


private:	

	TEntidad * entidad;
	vector <TNodo*> hijos;

	TNodo * padre;

} ;


#endif //NODO_H
