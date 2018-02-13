#ifndef ESCENA_H
#define ESCENA_H

#include "TNodo.h"

using namespace std;

class TEscena: public TNodo{
public:
	TEscena();
	virtual ~TEscena();


private:	

	TEntidad * entidad;
	vector <TNodo*> hijos;
	TNodo * padre;

} ;


#endif //ESCENA_H
