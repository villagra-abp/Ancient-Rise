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
	virtual tEnt getTipo() override{ return luz; }


private:	


		int MaxLuces;
		glGetIntegerv(GL_MAX_LIGHTS, &MaxLuces); 

		float SpotExpo=50;
		//v4PosicionLuz1=(0,0,0,0);

		glEnable(GL_LIGHTING);//activa la iluminación en la escena

		//si se activa deja de funcionar glColor3f, solo se tendran en cuenta los materiales 

		glEnable(GL_LIGHT0);  //activa la primera luz del vector

		//PARA DEFINIR PROPIEDADES
		//void glLightf(int light, int property, float param) //se utiliza cuando los parametros son escalares
		//void glLightfv(int light, int property, float* param) //se utiliza cuando los parametros son vectores
		
		void glLightf(GL_LIGHT0, GL_POSITION, SpotExpo);
		//void glLightfv(int light, int property, float* param) //se utiliza cuando los parametros son vectores
		
		//PROPIEDADES CON PARAMETROS ESCALARES
		//GL_SPOT_EXPONENT //valores entre [0, 128]. n=0 luz uniformemente distribuida, a mas valor mas "enfocada"
		//GL_SPOT_CUTOFF // especifica el ángulo de apertura de la luz. Se le pueden dar valores en el rango [0, 90], así como el valor especial 180
		//GL_CONSTANT_ATTENUATION, GL_LINEAR_ATTENUATION, GL_QUADRATIC_ATTENUATION



		//PROPIEDADES CON PARAMETROS VECTORIALES
		//GL_AMBIENT // El parámetro corresponde a un vector de 4 flotantes (RGBA) que especifica el color de la luz ambiente que emite la fuente. Por defecto, vale (0, 0, 0, 1), es decir, no emite luz ambiente. 
		//GL_DIFFUSE // El parámetro es el RGBA que especifica el color de la luz difusa que emite la fuente. Por defecto, vale (0, 0, 0, 1), excepto cuando la fuente es GL_LIGHT0, que vale (1, 1, 1, 1). 
		//GL_SPECULAR // Por defecto, vale (0, 0,0, 1), ), excepto cuando la fuente es GL_LIGHT0, que vale (1, 1, 1, 1). 
		//GL_POSITION //vector de 4 flotantes (x, y, z, w), especifica la pos, Si w es 0.0, es una luz direccional
		//GL_SPOT_DIRECTION //vector 3 flotantes(x,y,z), especifica la direccion de la luz, sólo tiene sentido cuando GL_SPOT_CUTOFF no es 180, que es su valor por defecto. Por defecto, la dirección es (0, 0, -1). 

		

	//TColor intensidad; //Es un vec3 con R, G, B.


} ;


#endif //LUZ_H
