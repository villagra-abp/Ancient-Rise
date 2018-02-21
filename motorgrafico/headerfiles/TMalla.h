#ifndef MALLA_H
#define MALLA_H

#include "TEntidad.h"

class TMalla: public TEntidad{
public:
	TMalla();
	virtual ~TMalla();
	//void cargarMalla(TFichero);
	virtual void beginDraw() override;
	virtual void endDraw() override;
	virtual tEnt getTipo() override{ return malla};


private:	

	//TRecursoMalla *malla;

} ;

#endif //MALLA_H
