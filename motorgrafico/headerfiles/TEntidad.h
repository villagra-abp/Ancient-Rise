#ifndef ENTIDAD_H
#define ENTIDAD_H

#include <iostream>
#include <vector>
#include <math.h>

#include <GL/glut.h>

using namespace std;

class TEntidad{
public:
	TEntidad();
	virtual ~TEntidad();
	virtual void beginDraw()=0;
	virtual void endDraw()=0;


private:	

	

} ;


#endif //ENTIDAD_H
