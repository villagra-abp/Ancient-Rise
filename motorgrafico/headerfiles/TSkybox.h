#ifndef TSKYBOX_H
#define TSKYBOX_H

#include "TEntidad.h"
#include "TRecursoSkybox.h"
#include "TGestorRecursos.h"

class TSkybox : public TEntidad{
public:
	TSkybox();
	TSkybox(vector<string> path);
	virtual ~TSkybox();
	void cargarSkybox(vector<string> path);						//Se le pasa un vector con la ruta para 6 texturas
	void beginDraw(TDatosEntidad *datos) override;
	void endDraw() override;
	virtual tEnt getTipo() override {return sky ;}
private:
	TRecursoSkybox *skybox;
//	TGestorRecursos *gestor;
};

#endif //TSKYBOX_H