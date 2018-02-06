#ifndef CAMARA_H
#define CAMARA_H

#include <iostream>
#include <vector>
#include <math.h>
#include "../headerfiles/TEntidad.h"

using namespace std;

class TCamara: public TEntidad{
public:
	TCamara();
	virtual ~TCamara();
	void setPerspectiva();
	void setParalela();
	virtual void beginDraw() override;
	virtual void endDraw() override;



private:	

	bool esPerspectiva;
	float cercano;
	float lejano;

} ;


#endif //CAMARA_H