#ifndef PROYECTIL_H
#define PROYECTIL_H

#include "../headerfiles/GameObject.h"
#include "../headerfiles/Enemigo.h"
#include "../headerfiles/Blackboard.h"

// Proyectil para que puedan usar los enemigos a distancia
class Proyectil : public GameObject
{
	public:
		
		Proyectil(Enemigo *e);
		void destroyProyectil();
		void update(Enemigo *e, Blackboard *b);
		void disparoProyectil(Enemigo *e, Blackboard *b);

		bool getEnTrayectoria();

		void setEnTrayectoria(bool b);
		void setPosition(Posicion* v);

		virtual ~Proyectil();


		virtual Posicion* getPosition() const override{ return proyectilPos; }

	private:
		
		void *proyectil;

		Posicion* proyectilPos;
	    Posicion* enemigoPosition;
	    Posicion* tam;
	    Fachada* fachada;

	    bool enTrayectoria;
		
		
};

#endif // PROYECTIL_H
