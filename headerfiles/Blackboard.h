#ifndef BLACKBOARD_H
#define BLACKBOARD_H

#include "../headerfiles/EnemigoBasico.h"
#include "../headerfiles/Protagonista.h"
#include "../headerfiles/Objeto.h"

class NodoGrafo;
class Alarma;

/*
Clase para poder almacenar informacion que puedan necesitar los arboles de comportamiento
*/
class Blackboard
{
	public:
		typedef vector<Objeto*> vecObjetos;
		

		Blackboard();
		void borrarEnemB();
		
		void setProta(float pX);
		void setTime(const glm::f32 T);
		void setFuente(vector<Objeto*> f);
		void setAlarma(vector<Alarma*>a);
		void setEnemB(vector<EnemigoBasico*> e);
		void setEnemBActual(EnemigoBasico *e);
		void setProtagonista(Protagonista* p);
		void setNodosGrafo(vector<NodoGrafo*> n);


		float getProta();
		glm::f32 getTime();
		vector<Objeto*> getFuente();
		vector<Alarma*> getAlarma();
		vector<EnemigoBasico*> getEnemB();
		EnemigoBasico* getEnemBActual();
		Protagonista* getProtagonista();
		vector<NodoGrafo*> getNodosGrafo();

		virtual ~Blackboard();

	private:
		
		float protaX;
		glm::f32 time;
		
		/* OBJETOS DEL JUEGO */
		vecObjetos fuentes;
		vector<Alarma*> alarmas;

		/* ENEMIGOS BASICOS */
		vector<EnemigoBasico*> enemigosB;
		EnemigoBasico* enemBActual;

		/* NODOS PATHFINDING */
		vector<NodoGrafo*> nodos;


		Protagonista *prota;

};

#endif // BLACKBOARD_H
