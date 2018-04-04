#ifndef ALIADOCERCA_H
#define ALIADOCERCA_H

#include "../headerfiles/Task.h"

// Tarea (Condicion) para ver si el Enemigo Elite tiene algun aliado (Enemigo Basico) cerca
class AliadoCerca : public Task
{
	public:
		
		virtual Status run(Enemigo *e) override;   
		virtual void onInitialize(Blackboard *b) override;
		virtual ~AliadoCerca();


	private:
		
		Blackboard *board;
	    void* enemigoNode;
	    vector<EnemigoBasico*> enemigosB;
	    vec3 enemBPosition;
	    
	
		
};

#endif // ALIADOCERCA_H
