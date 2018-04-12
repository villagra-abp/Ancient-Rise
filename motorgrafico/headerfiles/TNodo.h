#ifndef NODO_H
#define NODO_H

#include <iostream>
#include <vector>
#include <math.h>
#include <glm/glm.hpp>

#include "TEntidad.h"
#include "TLuz.h"
#include "TTransf.h"

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
	int getIdent();
	vector<TNodo*> getHijos();
	glm::mat4 getMatrix();
	TNodo * getPadre();
	glm::vec3 getPosicion();

	void draw(glm::mat4 view, glm::mat4 projection,TNodo* camara, vector<TNodo*> luces);


private:	

	int identificador;
	TEntidad * entidad;
	vector <TNodo*> hijos;
	TNodo * padre;

	/* Variables para Metodos de Borrado de Nodos */
	bool encontrado; 					// Para saber si hemos encontrado el nodo para borrar
	vector <TNodo*> hijosPadre; 		// Vector con todos los nodos del padre que queremos borrar
//	vector <TNodo*> nodosBorrar;
//	TNodo *padreBorrar;

} ;


#endif //NODO_H
