#ifndef TANIMACION_H
#define TANIMACION_H


#include <chrono>
#include "TEntidad.h"
#include "TRecursoAnimacion.h"
#include "TGestorRecursos.h"

using namespace std::chrono;

class TAnimacion : public TEntidad{
public:
	TAnimacion();
	virtual ~TAnimacion() = default;

	void cargarAnimacion(string path);
	void beginDraw(TDatosEntidad *datos) override;
	void endDraw() override;
	tEnt getTipo() override{ return anim;}
	int getFrame();

	void setTime(double tiempo);
	void setTimeZero();

	bool isVisible(bool flag);

private:
	double time;									//Progreso de la animacion en segundos
	double duracion;								//Duracion total de la animacion en segundos
	double dMalla;								//Duracion de cada malla en segundos
	steady_clock::time_point now, antes;

	double getTime();
	bool visible;
	double framerate;
	int fps;

	TRecursoAnimacion* animacion;
	TGestorRecursos* gestor;
};

#endif //TANIMACION_H