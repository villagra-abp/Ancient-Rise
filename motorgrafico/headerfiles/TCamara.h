#ifndef CAMARA_H
#define CAMARA_H

#include "TEntidad.h"

class TCamara: public TEntidad{
public:
	TCamara();
	virtual ~TCamara();
	void setPerspectiva();
	void setParalela();
	virtual void beginDraw(PilaMat* p) override;
	virtual void endDraw(PilaMat* p) override;



private:	

	bool esPerspectiva;
	float cercano;
	float lejano;

} ;


#endif //CAMARA_H
