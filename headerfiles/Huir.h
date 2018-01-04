#ifndef HUIR_H
#define HUIR_H

#include "../headerfiles/Task.h"

// Tarea (Accion) para que el enemigo huya
class Huir : public Task
{
	public:
		
		virtual Status run(Enemigo *e) override;   
		virtual void onInitialize(Blackboard *b) override;
		virtual ~Huir();


	private:
		
		Blackboard *board;
	    f32 frameDeltaTime;		  // Tiempo

	
		
};

#endif // HUIR_H