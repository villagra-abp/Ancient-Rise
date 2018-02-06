#ifndef COMPOSITE_H
#define COMPOSITE_H

#include "../headerfiles/Task.h"



// Clase para poder crear las tareas compuestas ( Selectors, Sequences)
class Composite: public Task
{
	public:

		void addChildren(Task *child);
		


	protected:
		typedef vector<Task*> Tasks;
		Tasks children; // VECTOR CON TODOS LOS HIJOS QUE TIENE ESTA TAREA 
		
};

#endif // COMPOSITE_H