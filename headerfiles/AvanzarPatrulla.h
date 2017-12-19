#ifndef AVANZARPATRULLA_H
#define AVANZARPATRULLA_H

#include "../headerfiles/Task.h"
#include "../headerfiles/Blackboard.h"



// Tarea (Accion) para realizar la accion de patrullar del enemigo
class AvanzarPatrulla : public Task
{
	public:
		
		virtual Status run() override;   			// Hasta que no ponga el override y se declare los metodos abstractos, la clase no deja de ser abstracta al igual que la de su padre
		virtual void onInitialize(Blackboard *b) override;
		virtual ~AvanzarPatrulla();


	private:

		int contadorPatrulla;     // PARA SABER LA POSICION EN LA QUE SE ENCUENTRA EN LA PATRULLA
		Enemigo *enemigo;		  // Objeto enemigo
		vector<Posicion*> pos;	  // Vector con las posiciones de la patrulla
		float protaPosition;	  
		f32 frameDeltaTime;		  // Tiempo
		f32 VELOCIDAD_ENEMIGO;	  // Su velocidad
		Blackboard *board;		  // Blackboard con los datos necesarios

	
		
};

#endif // AVANZARPATRULLA_H