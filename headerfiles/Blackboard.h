#ifndef BLACKBOARD_H
#define BLACKBOARD_H

#include "../headerfiles/EnemigoBasico.h"
#include "../headerfiles/Protagonista.h"
#include "../headerfiles/Objeto.h"

class NodoGrafo;


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
		void setProtagonista(Protagonista* p);
		void setNodosGrafo(vector<NodoGrafo*> n);


		float getProta();
		f32 getTime();
		vector<Objeto*> getFuente();
		vector<Objeto*> getComida();
		vector<Objeto*> getAlarma();
		vector<EnemigoBasico*> getEnemB();
		EnemigoBasico* getEnemBActual();
		Protagonista* getProtagonista();
		vector<NodoGrafo*> getNodosGrafo();

		virtual ~Blackboard();

	private:
		
		float protaX;
		f32 time;
		
		/* OBJETOS DEL JUEGO */
		vecObjetos fuentes;
		vecObjetos comidas;
		vecObjetos alarmas;

		/* ENEMIGOS BASICOS */
		vector<EnemigoBasico*> enemigosB;
		EnemigoBasico* enemBActual;

		/* NODOS PATHFINDING */
		vector<NodoGrafo*> nodos;


		Protagonista *prota;

};

#endif // BLACKBOARD_H