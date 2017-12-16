#ifndef DETECTARPROTA_H
#define DETECTARPROTA_H

#include "../headerfiles/Task.h"
#include "../headerfiles/Blackboard.h"


class DetectarProta : public Task
{
	public:
		
		virtual Status run() override;   			// Hasta que no ponga el override y se declare los metodos abstractos, la clase no deja de ser abstracta al igual que la de su padre
		virtual void onInitialize(Blackboard *b) override;
		virtual ~DetectarProta();


	private:
		
		Blackboard *board;
		Enemigo *enemigo;
	    float protaPosition;

	
		
};

#endif // DETECTARPROTA_H