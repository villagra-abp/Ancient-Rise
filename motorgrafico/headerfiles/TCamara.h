#ifndef CAMARA_H
#define CAMARA_H

#include "TEntidad.h"

class TCamara: public TEntidad{
public:
	TCamara();
	virtual ~TCamara();
	void setPerspectiva();
	void setParalela();
	virtual void beginDraw() override;
	virtual void endDraw() override;
	virtual tEnt getTipo() override{ return camara};


private:	

	bool esPerspectiva;
	float cercano;
	float lejano;

} ;


#endif //CAMARA_H
