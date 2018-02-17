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
	void setPadre(TNodo *p);

	TEntidad * getEntidad();
	TNodo * getPadre();
	vector<TNodo*> getHijos();

	void draw();


private:	

	TEntidad * entidad;
	vector <TNodo*> hijos;
	TNodo * padre;

	bool encontrado; 				// Para saber si hemos encontrado el nodo para borrar
	vector <TNodo*> hijosPadre; 	// Vector con todos los nodos del padre que queremos borrar

} ;


#endif //NODO_H
