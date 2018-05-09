#ifndef MALLA_H
#define MALLA_H

#include "TEntidad.h"
#include "TGestorRecursos.h"

class TMalla: public TEntidad{
public:
	TMalla();
	TMalla(bool billboard);
	virtual ~TMalla();
	void cargarMalla(string name);
	void setMaterial(string name);
	virtual void beginDraw(TDatosEntidad *datos) override;
	virtual void endDraw() override;
	virtual tEnt getTipo() override{ return malla; }
	void isVisible(bool flag);


private:	

	TRecursoMaterial *material;
	TRecursoMalla *mesh;
	TGestorRecursos *gestor;
	bool visible, billboard;

} ;

#endif //MALLA_H
