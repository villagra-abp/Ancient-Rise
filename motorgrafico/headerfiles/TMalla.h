#ifndef MALLA_H
#define MALLA_H

#include "TEntidad.h"

using namespace std;

class TMalla: public TEntidad{
public:
	TMalla();
	virtual ~TMalla();
	//void cargarMalla(TFichero);
	virtual void beginDraw() override;
	virtual void endDraw() override;


private:	

	//TRecursoMalla *malla;

} ;

#endif //MALLA_H
