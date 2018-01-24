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
		typedef vector<Objeto*> vecObjetos;

		Blackboard();
		
		void setProta(float pX);
		void setTime(const f32 T);
		void setFuente(Objeto* f);
		void setComida(Objeto *c);
		void setAlarma(Objeto* a);


		float getProta();
		f32 getTime();
		vector<Objeto*> getFuente();
		vector<Objeto*> getComida();
		vector<Objeto*> getAlarma();

		virtual ~Blackboard();

	private:
		
		float protaX;
		f32 time;
		vecObjetos fuentes;
		vecObjetos comidas;
		vecObjetos alarmas;
};

#endif // BLACKBOARD_H