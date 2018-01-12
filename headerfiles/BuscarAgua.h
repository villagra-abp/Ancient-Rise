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

		Objeto* f;
		Blackboard *board;
		f32 frameDeltaTime;		  // Tiempo
		scene::ISceneNode* enemigoNode;
		scene::ISceneNode* fuenteNode;
		sf::Clock reloj; 		  			// Reloj para controlar el tiempo que tarda en beber
	    int contador; 			  			// Para reiniciar el reloj cuando toca
		


};

#endif // BUSCARAGUA_H