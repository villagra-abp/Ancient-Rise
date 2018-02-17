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
	virtual void beginDraw() override;
	virtual void endDraw() override;


private:	

	//TColor intensidad;

} ;


#endif //LUZ_H
