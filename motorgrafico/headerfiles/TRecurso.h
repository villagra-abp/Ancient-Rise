#ifndef RECURSO_H
#define RECURSO_H

#include <iostream>
#include <unistd.h>

using namespace std;

class TRecurso{
public:
	virtual ~TRecurso() = default;
	virtual string getNombre() = 0;
	virtual void setNombre(string nombre) = 0;
	virtual void cargarFichero(string nombre) = 0;


private:	

	string nombre;

} ;

#endif //RECURSO_H