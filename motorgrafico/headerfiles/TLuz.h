#ifndef LUZ_H
#define LUZ_H

#include "TEntidad.h"

using namespace std;

class TLuz: public TEntidad{
public:
	TLuz();
	virtual ~TLuz();
	//void setIntensidad(TColor c);
	//TColor getIntensidad();
	virtual void beginDraw(glm::mat4 view, glm::mat4 projection) override;
	virtual void endDraw() override;
	virtual tEnt getTipo() override{ return luz; }


private:	

	//TColor intensidad;

} ;


#endif //LUZ_H
