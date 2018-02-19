#ifndef TRANSF_H
#define TRANSF_H

#include "TEntidad.h"

class TTransf: public TEntidad{
public:
	TTransf();
	virtual ~TTransf();
	void identidad();
	void cargar(glm::mat4 matriz);

	//Transformaciones
	void transponer();
	void trasladar(float x,float y,float z);
	void rotar(float x,float y,float z,float w);
	void escalar(float x, float y, float z);
	void invertir();

	//Draw
	virtual void beginDraw() override;
	virtual void endDraw() override;
	


private:	

	glm::mat4 matriz;

} ;


#endif //TRANSF_H
