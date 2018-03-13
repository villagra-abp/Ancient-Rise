#ifndef MALLA_H
#define MALLA_H

#include "TEntidad.h"
#include "TGestorRecursos.h"

class TMalla: public TEntidad{
public:
	TMalla();
	virtual ~TMalla();
	void cargarMalla(string name);
	virtual void beginDraw() override;
	virtual void endDraw() override;
	virtual string getTipo() override{ return "malla"; }


private:	

	TRecursoMalla *malla;
	TGestorRecursos* gestor;

} ;

#endif //MALLA_H
