#ifndef COMPROBARSED_H
#define COMPROBARSED_H

#include "../headerfiles/Task.h"


// Tarea (Condicion) para comprobar si el enemigo tiene sed
class ComprobarSed : public Task
{
	public:

		virtual Status run(Enemigo *e) override;   	
		virtual void onInitialize(Blackboard *b) override;
		virtual ~ComprobarSed();


	private:


};

#endif // COMPROBARSED_H