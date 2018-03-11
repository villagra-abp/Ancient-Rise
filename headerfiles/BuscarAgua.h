#ifndef BUSCARAGUA_H
#define BUSCARAGUA_H

#include "../headerfiles/Task.h"


// Tarea (Accion) para buscar agua cuando el enemigo tiene sed
class BuscarAgua : public Task
{
	public:

		virtual Status run(Enemigo *e) override;   	
		virtual void onInitialize(Blackboard *b) override;
		virtual ~BuscarAgua();
		void startClock();


	private:

		vector<Objeto*> f;
		Blackboard *board;
		f32 frameDeltaTime;		  // Tiempo
		void* enemigoNode;
		scene::ISceneNode* fuenteNode;
		sf::Clock reloj; 		  			// Reloj para controlar el tiempo que tarda en beber
	    int contador; 			  			// Para reiniciar el reloj cuando toca
		
	    //DATOS DE LA FUENTE
	    Posicion* fuentePosition;
	    float fuenteX;
	    int distanciaFuente;
	    int distanciaFaux;

};

#endif // BUSCARAGUA_H
