#ifndef COMPROBARHAMBRE_H
#define COMPROBARHAMBRE_H

#include "../headerfiles/Task.h"


// Tarea (condicion) para saber si el enemigo tiene hambre o no
class ComprobarHambre : public Task
{
	public:

		virtual Status run(Enemigo *e) override;   	
		virtual void onInitialize(Blackboard *b) override;
		virtual ~ComprobarHambre();


	private:


};

#endif // COMPROBARHAMBRE_H