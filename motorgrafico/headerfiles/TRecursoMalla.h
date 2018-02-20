#ifndef RECURSOMALLA_H
#define RECURSOMALLA_H

#include "TRecurso.h"

class TRecursoMalla: public TRecurso{
public:
	TRecursoMalla();
	virtual ~TRecursoMalla();
	bool CargarFichero(char * nombre);
	void Draw();
	


private:	

	float* vertices,normales,texturas;
	float* VertTri,NormTri,TextTri;
	long NumTri;

} ;

#endif //RECURSOMALLA_H