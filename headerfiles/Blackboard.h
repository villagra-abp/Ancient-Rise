#ifndef BLACKBOARD_H
#define BLACKBOARD_H

#include "../headerfiles/Enemigo.h"
#include "../headerfiles/Objeto.h"


/*
Clase para poder almacenar informacion que puedan necesitar los arboles de comportamiento
*/
class Blackboard
{
	public:

		Blackboard();
		
		void setProta(float pX);
		void setTime(const f32 T);
		void setFuente(Objeto* f);
		void setComida(Objeto *c);
		void setAlarma(Objeto* a);


		float getProta();
		f32 getTime();
		Objeto* getFuente();
		Objeto* getComida();
		Objeto* getAlarma();

		virtual ~Blackboard();

	private:
		
		float protaX;
		f32 time;
		Objeto *fuente;
		Objeto *comida;
		Objeto *alarma;
};

#endif // BLACKBOARD_H