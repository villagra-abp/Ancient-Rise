#ifndef BLACKBOARD_H
#define BLACKBOARD_H

#include <string>
#include "../headerfiles/Enemigo.h"






class Blackboard
{
	public:

		Blackboard();
		
		void setEnemigo(Enemigo* e);
		void setProta(float pX);
		void setTime(const f32 T);
		void setVel(f32 vel);
		void setPos(vector<Posicion*> pos);


		Enemigo* getEnem();
		float getProta();
		f32 getTime();
		f32 getVel();
		vector<Posicion*> getPos();

		virtual ~Blackboard();

	private:
		float protaX;
		f32 time;
		f32 velocidadEnemigo;
		vector<Posicion*> posPatrulla;
		Enemigo* enemBasico;
};

#endif // BLACKBOARD_H