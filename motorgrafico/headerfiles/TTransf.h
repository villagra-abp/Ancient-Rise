#ifndef TRANSFORMACION_H
#define TRANSFORMACION_H

#include "TEntidad.h"

using namespace std;

class TTransformacion: public TEntidad{
public:
	TTransformacion();
	virtual ~TTransformacion();
	void identidad();
	//void cargar(TMatriz4x4 matriz);
	void transponer();
	void trasladar(float x,float y,float z);
	void rotar(float x,float y,float z,float w);
	void escalar(float x, float y, float z);
	virtual void beginDraw() override;
	virtual void endDraw() override;
	


private:	

	//TMatriz4x4 matriz;

} ;


#endif //TRANSFORMACION_H
