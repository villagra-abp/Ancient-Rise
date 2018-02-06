#ifndef BLACKBOARD_H
#define BLACKBOARD_H

#include "../headerfiles/EnemigoBasico.h"
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
		void setFuente(vector<Objeto*> f);
		void setComida(vector<Objeto*> c);
		void setAlarma(vector<Objeto*>a);
		void setEnemB(EnemigoBasico *e);
		void setEnemBActual(EnemigoBasico *e);


		float getProta();
		f32 getTime();
		vector<Objeto*> getFuente();
		vector<Objeto*> getComida();
		vector<Objeto*> getAlarma();
		vector<EnemigoBasico*> getEnemB();
		EnemigoBasico* getEnemBActual();

		virtual ~Blackboard();

	private:
		
		float protaX;
		f32 time;
		vecObjetos fuentes;
		vecObjetos comidas;
		vecObjetos alarmas;
		vector<EnemigoBasico*> enemigosB;
		EnemigoBasico* enemBActual;

};

#endif // BLACKBOARD_H