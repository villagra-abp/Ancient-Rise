#ifndef TRECURSOANIMACION_H
#define TRECURSOANIMACION_H

#include "TRecurso.h"
#include "TRecursoMalla.h"

class TRecursoAnimacion : public TRecurso{
	public:
	TRecursoAnimacion(){}
	virtual ~TRecursoAnimacion();

    void draw(glm::mat4 mmodelo, TDatosEntidad *datos, int frame);	
    void addMalla(TRecursoMalla* malla);

	string getNombre() override {return nombre;}
	float getDuracion();
	void setNombre(string nombre) override;
	//virtual void cargarFichero(string nombre) = 0;


private:	

	float duracion, dMalla;

	string nombre;
	vector<TRecursoMalla*> mallas;
}

#endif //TRECURSOANIMACION_H