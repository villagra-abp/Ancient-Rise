#ifndef BLACKBOARD_H
#define BLACKBOARD_H

#include "../headerfiles/Enemigo.h"
#include "../headerfiles/Objeto.h"


/*
Clase para poder almacenar informacion que puedan necesitar los arboles 
*/
class Blackboard
{
	public:

		Blackboard();
		
		void setProta(float pX);
		void setTime(const f32 T);
		void setFuente(Objeto* f);

		float getProta();
		f32 getTime();
		Objeto* getFuente();

		virtual ~Blackboard();

	private:
		
		float protaX;
		f32 time;
		Objeto *o;
};

#endif // BLACKBOARD_H