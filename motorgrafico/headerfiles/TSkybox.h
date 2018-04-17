#ifndef TSKYBOX_H
#define TSKYBOX_H

#include "TEntidad.h"
#include "TRecursoSkybox.h"
#include "TGestorRecursos.h"

class TSkybox : public TEntidad{
public:
	TSkybox();
	TSkybox(string path);
	virtual ~TSkybox();
	void cargarSkybox(string path);
	void beginDraw(TDatosEntidad *datos) override;
	void endDraw() override;
	tEnt getTipo() override {return skybox ;}
private:
	TRecursoSkybox *skybox;
//	TGestorRecursos *gestor;
}

#endif //TSKYBOX_H