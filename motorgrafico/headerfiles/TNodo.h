#ifndef NODO_H
#define NODO_H

#include "TEntidad.h"

using namespace std;

class TNodo{
public:
	TNodo();
	virtual ~TNodo();
	int addHijo();
	int remHijo();
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
