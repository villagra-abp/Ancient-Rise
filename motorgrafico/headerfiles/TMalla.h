#ifndef MALLA_H
#define MALLA_H

#include "TEntidad.h"

class TMalla: public TEntidad{
public:
	TMalla();
	virtual ~TMalla();
	//void cargarMalla(TFichero);
	virtual void beginDraw(PilaMat* p) override;
	virtual void endDraw(PilaMat* p) override;


private:	

	//TRecursoMalla *malla;

} ;

#endif //MALLA_H
