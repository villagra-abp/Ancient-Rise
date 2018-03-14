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
	int addHijoBack(TNodo* n);
	int addHijo(TNodo* n, int pos);
	TNodo* remHijo(TNodo* n);
	int remHijoAll(TNodo* n);
	TNodo* remHijoChange(TNodo* n1, TNodo* n2);
	void changePadre(TNodo* nPadre, TNodo* hijo);
	void remHijos();


	bool setEntidad(TEntidad* ent);
	void setPadre(TNodo *p);
	void setIdent(int i);

	TEntidad * getEntidad();
	TNodo * getPadre();
	vector<TNodo*> getHijos();
	int getIdent();

	void draw();


private:	

	int identificador;
	TEntidad * entidad;
	vector <TNodo*> hijos;
	TNodo * padre;

	/* Variables para Metodos de Borrado de Nodos */
	bool encontrado; 					// Para saber si hemos encontrado el nodo para borrar
	vector <TNodo*> hijosPadre; 		// Vector con todos los nodos del padre que queremos borrar
	vector <TNodo*> nodosBorrar;
	TNodo *padreBorrar;

} ;


#endif //NODO_H
