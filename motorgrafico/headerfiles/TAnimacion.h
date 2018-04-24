#ifndef TANIMACION_H
#define TANIMACION_H


#include <ctime> //time.h
#include "TEntidad.h"
#include "TRecursoAnimacion.h"
#include "TGestorRecurso.h"

class TAnimacion : public TEntidad{
public:
	TAnimacion();
	virtual ~TAnimacion();

	void cargarAnimacion(string path);
	void beginDraw(TDatosEntidad *datos) override;
	void endDraw() override;
	tEnt getTipo() override{ return anim;}
	int getFrame();

	bool isVisible(bool flag);

private:
	float time;									//Progreso de la animacion en segundos
	float duracion;								//Duracion total de la animacion en segundos
	float dMalla;								//Duracion de cada malla en segundos
	time_t now, antes;

	float getTime();
	bool visible;

	TRecursoAnimacion* animacion;
	TGestorRecurso* gestor;
};

#endif //TANIMACION_H