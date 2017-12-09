#ifndef DECORATOR_H
#define DECORATOR_H

#include <iostream>
#include <vector>
#include "../headerfiles/Task.h"


using namespace std;

/*
Es un tipo de tarea que solo tiene un unico hijo tarea y modifica su comportamiento de alguna manera
Esta clase, es una clase base que proporciona todas las funcionalidades comunes para implemnetar un 
decorador eficientemente
*/
class Decorator: public Task
{
	public:

		Decorator(Task* child);

		


	protected:
		Task* m_pChild;
		
		
};

#endif // DECORATOR_H