#ifndef ATACAR_H
#define ATACAR_H

#include "../headerfiles/Task.h"

// Tarea (Accion) para atacar al protagonista
class Atacar : public Task
{
	public:
		
		virtual Status run(Enemigo *e) override;   
		virtual void onInitialize(Blackboard *b) override;
		virtual ~Atacar();


	private:
		
		Blackboard *board;
	    f32 frameDeltaTime;		  // Tiempo
	    scene::ISceneNode* enemigoNode;
	    int separacionAtaque; 				// Separacion que tiene que haber entre el enemigo y el prota en funcion de si utiliza un arma 
	    									// a distancia o cuerpo a cuerpo
	
		
};

#endif // ATACAR_H