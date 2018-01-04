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


	private:

		Objeto* f;
		Blackboard *board;
		f32 frameDeltaTime;		  // Tiempo
		


};

#endif // BUSCARAGUA_H